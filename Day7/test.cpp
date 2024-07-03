#include <iostream>
    #include <thread>
    #include <mutex>
    #include <condition_variable>

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    void print_id(int id) {  //The function to be executed by each thread.
        std::unique_lock<std::mutex> lck(mtx);  //Acquires the mutex to protect the shared variable ready.
        while (!ready) cv.wait(lck); //The thread waits on the condition variable cv until ready becomes true.
        std::cout << "Thread " << id << std::endl; //Once ready is true, the thread prints its ID.
    }

    void go() {
        std::unique_lock<std::mutex> lck(mtx);
        ready = true;
        cv.notify_all(); //Wakes up all waiting threads.
    }

    int main() {
        std::thread threads[10];  //Creates an array of 10 threads.
        for (int i = 0; i < 10; ++i) {
            threads[i] = std::thread(print_id, i);  // Initializes each thread to run the print_id function with its respective ID.
        }

        std::cout << "10 threads ready to race...\n";
        go();  // Calls the go function to set ready to true and notify all threads.

        for (auto &th : threads) th.join(); // Waits for all threads to complete their execution.

        return 0;
    }