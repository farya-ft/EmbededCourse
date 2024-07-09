### Day 9: Advanced Multi-threading and Synchronization
##### 1. Advanced Multi-threading Techniques
In this lesson, we will focus on more advanced multi-threading concepts, including atomic operations, thread-safe data structures, and thread synchronization using condition variables and barriers.

Atomic Operations

Atomic operations are essential for ensuring data integrity in multi-threaded applications without using locks.

Code: Atomic Operations Example

```cpp

#include <iostream>
#include <thread>
#include <atomic>// This includes the atomic operations library, which provides atomic types and operations that ensure safe access to variables shared between threads.
#include <vector>

std::atomic<int> counter(0);

void incrementCounter() { // a function incrementCounter that increments the counter 1000 times.
    for (int i = 0; i < 1000; ++i) {
        ++counter;
    }
}

int main() {
    std::vector<std::thread> threads; //This declares a vector to hold the thread objects.
    for (int i = 0; i < 10; ++i) {//This loop creates 10 threads, each running the incrementCounter function. 
        threads.emplace_back(incrementCounter); //constructs a std::thread object and adds it to the threads vector.
    }
    for (auto& th : threads) { 
        th.join();
    }
    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
```
##### Explanation:

_std::atomic<int> counter(0);

This declares an atomic integer variable named counter and initializes it to 0. The std::atomic type ensures that operations on counter are atomic, meaning they are completed without interference from other threads, preventing race conditions.

_++counter;: Atomic increment operation, ensuring thread-safe updates.
Thread-safe Data Structures

_Standard containers are not thread-safe. Using synchronization mechanisms, you can create thread-safe wrappers.

_for (auto& th : threads) { th.join(); }: This loop waits for all the threads to finish executing. The join method blocks the calling thread (the main thread) until the thread represented by th has finished executing.

### Role of std::atomic<int>
In a multithreaded program, multiple threads may try to read or modify a shared variable simultaneously. Without proper synchronization, this can lead to race conditions where the variable's state becomes unpredictable and incorrect.

The std::atomic<int> type ensures that operations on the counter variable are performed atomically. This means that each increment operation (++counter) is completed entirely before another thread can perform another increment operation. It prevents the classic race condition where multiple threads try to read-modify-write a variable simultaneously, leading to lost updates.

###### In this program:

* ++counter is an atomic operation. The atomic type ensures that the increment operation is done safely even when multiple threads attempt to increment the counter simultaneously.
* This guarantees that the final value of counter is as expected (10,000) when all threads have finished executing.

##### Thread-safe Queue Example

```cpp

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        condition_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this]{ return !queue_.empty(); });
        T value = queue_.front();
        queue_.pop();
        return value;
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

void producer(ThreadSafeQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        queue.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(ThreadSafeQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        int value = queue.pop();
        std::cout << "Consumer popped: " << value << std::endl;
    }
}

int main() {
    ThreadSafeQueue<int> queue;//Creates an instance of ThreadSafeQueue<int>.
    std::thread prod(producer, std::ref(queue));
    std::thread cons(consumer, std::ref(queue));//: Creates a consumer thread that runs the consumer function, passing the queue by reference.
    prod.join();
    cons.join();
    return 0; //Returns 0 from the main function, indicating successful completion of the program.
}
```
##### Explanation:

* #include < queue >: This includes the queue library, which provides the std::queue container for FIFO (First-In-First-Out) data storage.
* #include <  thread>: This includes the thread support library, which is necessary for creating and managing threads.
* #include < mutex>: This includes the mutex library, which provides mutual exclusion to protect shared data.
* #include < condition_variable>: This includes the condition variable library, which allows threads to wait for certain conditions to be met.

##### Methods:
###### void push(T value):

* Acquires a lock on mutex_ using std::lock_guard to ensure that only one thread can modify the queue at a time.
* Adds the value to the queue.
* Notifies one waiting thread (if any) that the condition (non-empty queue) is satisfied using condition_.notify_one().
###### T pop():

* Acquires a lock on mutex_ using std::unique_lock to allow more complex lock management (required by condition_variable).
* Waits until the queue is not empty. The lambda function []{ return !queue_.empty(); } checks the condition, and condition_.wait(lock, ...); suspends the thread until the condition is true.
* Retrieves the value at the front of the queue.
* Removes the value from the queue.
* Returns the retrieved value.

##### Members:
* std::queue<T> queue_: The underlying queue to store data.
* std::mutex mutex_: A mutex to protect access to the queue.
* std::condition_variable condition_: A condition variable to manage the waiting and notification of threads.
---
* void producer(ThreadSafeQueue< int>& queue): This function simulates a producer thread that pushes integers from 0 to 9 into the queue with a delay of 100 milliseconds between each push.
* void consumer(ThreadSafeQueue< int>& queue): This function simulates a consumer thread that pops and prints 10 integers from the queue.
---

std::lock_guard< std::mutex > lock(mutex_);: Locks the mutex for the duration of the block.
condition_.wait(lock, [this]{ return !queue_.empty(); });: Waits until the queue is not empty.
#### Why Use a Queue?
A queue is used in this context to implement a typical producer-consumer scenario, where:

* The producer generates data and puts it into the queue.
* The consumer retrieves data from the queue and processes it.
* The queue ensures that data is processed in the order it was produced (FIFO). Using a thread-safe queue with proper synchronization mechanisms (mutex and condition variable) ensures that:

* Multiple threads can safely interact with the queue without causing race conditions.
* The consumer waits for data to be available in the queue, preventing it from trying to access an empty queue.
* The producer notifies the consumer when new data is available, avoiding unnecessary waiting.

This design allows for efficient and safe communication between threads in concurrent programming.


### Barriers

Barriers synchronize a fixed number of threads, making them wait until all threads have reached the barrier.

##### Barrier Example (Pseudo-code)

```cpp

#include <iostream>
#include <thread>
#include <barrier>
#include <vector>

std::barrier sync_point(3);

void task(int id) {
    std::cout << "Task " << id << " reached barrier" << std::endl;
    sync_point.arrive_and_wait();
    std::cout << "Task " << id << " passed barrier" << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(task, i);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```
##### Explanation:

std::barrier sync_point(3);: Initializes a barrier for 3 threads.
sync_point.arrive_and_wait();: Each thread waits until all threads reach this point.
2. Synchronization Using Condition Variables
Condition variables are used to block one or more threads until a particular condition is met.

#### Condition Variables Example

```cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck);
    std::cout << "Thread " << id << std::endl;
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(print_id, i);
    }

    std::cout << "10 threads ready to race...\n";
    go();

    for (auto &th : threads) th.join();

    return 0;
}
```
##### Explanation:

std::condition_variable cv;: Declares a condition variable.
cv.wait(lck);: Waits for the condition variable to be notified.
cv.notify_all();: Notifies all waiting threads.
3. Real-Time Operating Systems (RTOS) - Advanced Features
In this section, we explore more advanced features of RTOS like task priorities, dynamic memory allocation, and inter-task communication.

Task Priorities

RTOS allows setting different priorities for tasks, ensuring critical tasks get more CPU time.

#### RTOS Task Priorities (Pseudo-code using FreeRTOS)

```cpp

#include <FreeRTOS.h>
#include <task.h>

void vTaskHighPriority(void *pvParameters) {
    while (1) {
        // High priority task actions
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vTaskLowPriority(void *pvParameters) {
    while (1) {
        // Low priority task actions
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

int main() {
    xTaskCreate(vTaskHighPriority, "High Priority Task", 1000, NULL, 2, NULL);
    xTaskCreate(vTaskLowPriority, "Low Priority Task", 1000, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
    return 0;
}
```
Explanation:

xTaskCreate: Creates tasks with different priorities.
vTaskStartScheduler(): Starts the RTOS scheduler.
Inter-Task Communication

RTOS provides mechanisms like message queues, semaphores, and mailboxes for inter-task communication.

#### RTOS Message Queue (Pseudo-code using FreeRTOS)

```cpp

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

QueueHandle_t xQueue;

void vProducerTask(void *pvParameters) {
    int value = 0;
    while (1) {
        xQueueSend(xQueue, &value, portMAX_DELAY);
        value++;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vConsumerTask(void *pvParameters) {
    int value;
    while (1) {
        xQueueReceive(xQueue, &value, portMAX_DELAY);
        // Process value
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

int main() {
    xQueue = xQueueCreate(10, sizeof(int));

    if (xQueue != NULL) {
        xTaskCreate(vProducerTask, "Producer", 1000, NULL, 1, NULL);
        xTaskCreate(vConsumerTask, "Consumer", 1000, NULL, 1, NULL);

        vTaskStartScheduler();
    }

    for (;;);
    return 0;
}
```
##### Explanation:

xQueueCreate: Creates a message queue.
xQueueSend: Sends a message to the queue.
xQueueReceive: Receives a message from the queue.

!!! Daily Challenge:
* Create a thread-safe stack using std::mutex and std::condition_variable.
* Implement an atomic counter using std::atomic and demonstrate its use in a multi-threaded context.
* Write an RTOS application with tasks of different priorities and implement inter-task communication using message queues.
