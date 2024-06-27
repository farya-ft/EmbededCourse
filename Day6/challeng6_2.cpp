
/*To achieve the task of reading sensor data in one thread and logging it in another thread using the Logger class in C++,
 you'll need to utilize threading, synchronization, and a thread-safe queue for passing the sensor data between threads.*/

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>  //Includes the condition variable library for synchronization.
#include <chrono>             //Includes the chrono library for time utilities like sleeping.

using namespace std;
// Thread-safe queue
template <typename T>
class SafeQueue {
private:
    queue<T> queue;
    mutex mtx;                // A mutex to ensure thread-safe access to the queue
    condition_variable cv;   //A condition variable to synchronize threads waiting for the queue to have elements.

public:
    void push(T value) {
        lock_guard<mutex> lock(mtx);  // Locks the mutex to ensure thread-safe access.
        queue.push(value);           //Adds the value to the queue.
        cv.notify_one();            //Notifies one waiting thread that the queue has new elements.
    }

    bool pop(T &value) {                                   //Method to remove and return an element from the queue
        unique_lock<mutex> lock(mtx);                     //Locks the mutex to ensure thread-safe access.
        cv.wait(lock, [this]{ return !queue.empty(); }); // Waits until the queue is not empty. 
        if (!queue.empty()) {
            value = queue.front();                      //Retrieves the front element from the queue
            queue.pop();                               //Removes the front element from the queue.
            return true;                              //Returns true if an element was successfully popped.
        }
        return false;
    }
};

// Logger class
class Logger {                                     //Method to log a message.
public:
    void log(const string &message) {
        lock_guard<mutex> lock(log_mtx);
        cout << "Logged: " << message << endl;
    }

private:
    std::mutex log_mtx;
};

// Simulate reading sensor data
void sensorReadingThread(SafeQueue<string> &queue) {
    int sensorValue = 0;
    while (true) {                                                   // Infinite loop to continuously read sensor data.
        this_thread::sleep_for(chrono::seconds(1));                 // Sleeps for 1 second to simulate delay in sensor reading.
        sensorValue++;
        queue.push("Sensor value: " + to_string(sensorValue));     //Pushes the sensor value to the queue as a string.
    }
}

// Log the sensor data
void loggingThread(SafeQueue<string> &queue, Logger &logger) {
    string data;
    while (true) {
        if (queue.pop(data)) {
            logger.log(data);
        }
    }
}

int main() {
    SafeQueue<string> queue;
    Logger logger;

    thread sensorThread(sensorReadingThread, ref(queue));
    thread logThread(loggingThread, ref(queue), ref(logger));

    sensorThread.join();
    logThread.join();

    return 0;
}
