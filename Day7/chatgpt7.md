## Day 7: Smart Pointers and Advanced Multi-threading
##### 1. Smart Pointers
Smart pointers are a feature in C++ that help manage dynamic memory automatically. 
They prevent memory leaks by ensuring that memory is properly freed when it is no longer needed.

###### Types of Smart Pointers:

* std::unique_ptr: Owns a resource exclusively. No other smart pointer can own the same resource.
* std::shared_ptr: Allows multiple smart pointers to share ownership of a resource.
* std::weak_ptr: A non-owning reference to an object managed by std::shared_ptr.
##### Unique Pointer Example

```cpp
    #include <iostream>
    #include <memory>

    class MyClass {
    public:
        MyClass() {
            std::cout << "MyClass Constructor" << std::endl;
        }
        ~MyClass() {
            std::cout << "MyClass Destructor" << std::endl;
        }
        void display() {
            std::cout << "Displaying MyClass" << std::endl;
        }
    };

    int main() {
        std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();
        ptr1->display();
        
        // Ownership can be transferred
        std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
        if (ptr1 == nullptr) {
            std::cout << "ptr1 is null after transfer" << std::endl;
        }
        ptr2->display();
        
        return 0;
    }
```  
##### output:
```
MyClass Constructor
Displaying MyClass
ptr1 is null after transfer
Displaying MyClass
MyClass Destructor
```

##### Shared Pointer Example

```cpp
    #include <iostream>
    #include <memory>

    class MyClass {
    public:
        MyClass() {
            std::cout << "MyClass Constructor" << std::endl;
        }
        ~MyClass() {
            std::cout << "MyClass Destructor" << std::endl;
        }
        void display() {
            std::cout << "Displaying MyClass" << std::endl;
        }
    };

    int main() {
        std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
        {
            std::shared_ptr<MyClass> ptr2 = ptr1;
            ptr2->display();
            std::cout << "Use count: " << ptr1.use_count() << std::endl;
        }
        std::cout << "Use count after scope: " << ptr1.use_count() << std::endl;
        ptr1->display();
        
        return 0;
    }
```
##### output:
```
MyClass Constructor
Displaying MyClass
Use count: 2
Use count after scope: 1
Displaying MyClass
MyClass Destructor
```
In the provided code, `std::shared_ptr` is used, which is a type of smart pointer that allows multiple pointers to simultaneously point to the same object. One of the important features of `std::shared_ptr` is the `use_count()` function, which returns the number of `shared_ptr` instances that point to the same object. This count is known as the reference count.

### Explanation of `use_count()`

The `use_count()` function returns the number of `std::shared_ptr` instances that are pointing to the managed object. This reference count is used to manage the lifetime of the object; the object will stay alive as long as at least one `std::shared_ptr` is pointing to it. When the reference count drops to zero, the object is automatically destroyed and its memory is freed.

### Explanation of the Code:

In this code:

1. `std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();`:
   - This creates an object of type `MyClass` and initializes a `std::shared_ptr` (`ptr1`) to point to it. At this point, the reference count is 1.

2. `{ std::shared_ptr<MyClass> ptr2 = ptr1; ... }`:
   - A block scope (`{}`) is defined, and inside this block, `ptr2` is initialized to point to the same object as `ptr1`. The reference count is now incremented to 2.

3. `ptr2->display();`:
   - The `display` method of the `MyClass` object is called, which prints "Displaying MyClass".

4. `std::cout << "Use count: " << ptr1.use_count() << std::endl;`:
   - The current reference count (`use_count`) from `ptr1` is printed, showing 2, because both `ptr1` and `ptr2` are pointing to the same object.

5. The block scope ends, and `ptr2` goes out of scope:
   - When `ptr2` goes out of scope, it is destroyed, and the reference count is decremented to 1.

6. `std::cout << "Use count after scope: " << ptr1.use_count() << std::endl;`:
   - The current reference count (`use_count`) from `ptr1` is printed again, showing 1, because only `ptr1` is now pointing to the object.

7. `ptr1->display();`:
   - The `display` method of the `MyClass` object is called again, which prints "Displaying MyClass".

### Conclusion:

The `use_count()` function provides the number of `std::shared_ptr` instances pointing to a particular object and helps manage the object's lifetime automatically. In this code, the reference count is printed before and after the block scope to show how the reference count changes when `shared_ptr` instances are created and destroyed. This feature of `std::shared_ptr` helps in automatic memory management and prevents memory leaks by ensuring that the object is only destroyed when there are no more `shared_ptr` instances pointing to it.

```
در سیستم‌های تعبیه‌شده، از
` std::unique_ptr`
 برای مدیریت حافظه به صورت انحصاری و بدون هزینه اضافی استفاده کنید. از 
`std::shared_ptr`
 هنگامی استفاده کنید که نیاز به اشتراک‌گذاری مالکیت یک شیء بین چندین جزء یا ماژول دارید. 
`std::unique_ptr`
 ساده‌تر و کارآمدتر است و برای منابع محدود مناسب است. 
 `std::shared_ptr`
  برای مواقعی مناسب است که نیاز به مدیریت پیچیده‌تر و اشتراک‌گذاری منابع دارید.
   هر دو به جلوگیری از نشت حافظه و مدیریت خودکار منابع کمک می‌کنند.
```
##### 2. Advanced Multi-threading
Advanced multi-threading techniques can help improve the performance and responsiveness of your applications. These include thread synchronization, thread pooling, and using condition variables.

Mutex and Condition Variable Example

```cpp
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
```  

##### OUTPUT:
```
10 threads ready to race...
Thread 1
Thread 8
Thread 0
Thread 2
Thread 4
Thread 3
Thread 6
Thread 5
Thread 7
Thread 9
```  
##### Explanation:

* std::mutex mtx: A mutex for protecting shared data (ready).
* std::condition_variable cv: A condition variable to synchronize the threads.
* bool ready = false: A flag indicating when the threads should start.

* cv.wait(lck);: Waits for the condition variable to be notified.
* cv.notify_all();: Notifies all waiting threads.


##### Summary:
* This code sets up 10 threads, each of which waits for a signal to start (the ready flag).
* The main thread prints a message, then sets the ready flag to true and notifies all  waiting threads using a condition variable.
* Each thread, upon waking up, prints its ID.
* The main thread waits for all threads to finish using join.
This ensures synchronized and coordinated start of multiple threads, demonstrating basic thread synchronization using mutexes and condition variables.

Condition variables are used in concurrent programming to synchronize access to shared resources and to coordinate the execution of threads. Here’s why and when you might use condition variables:

### Why Use Condition Variables:

1. **Coordination Between Threads:**
   - Condition variables allow one or more threads to wait until they are notified by another thread. This is essential for coordinating actions between threads, ensuring that a particular thread only proceeds when certain conditions are met.

2. **Efficient Waiting:**
   - When a thread waits on a condition variable, it releases the associated mutex and goes to sleep atomically. This avoids busy-waiting, where a thread would otherwise repeatedly check for a condition, wasting CPU cycles.

3. **Signaling State Changes:**
   - They provide a mechanism to signal state changes between threads. For instance, one thread can signal that data is ready for processing, and other threads waiting on this condition can wake up and proceed.

### Example Context:

In the provided code, the condition variable `cv` is used to synchronize the start of multiple threads. Here’s a step-by-step breakdown of how and why the condition variable is used:

### Code Context:

1. **Thread Initialization and Waiting:**
    ```cpp
    void print_id(int id) {
        std::unique_lock<std::mutex> lck(mtx);
        while (!ready) cv.wait(lck);
        std::cout << "Thread " << id << std::endl;
    }
    ```
    - Each thread created in the `main` function runs the `print_id` function.
    - Inside `print_id`, each thread acquires the mutex `mtx` using `std::unique_lock`.
    - Each thread then checks the `ready` flag. If `ready` is `false`, the thread waits on the condition variable `cv`. During this wait, the mutex `mtx` is released, allowing other threads to acquire it if needed.

2. **Notifying Threads to Start:**
    ```cpp
    void go() {
        std::unique_lock<std::mutex> lck(mtx);
        ready = true;
        cv.notify_all();
    }
    ```
    - The `go` function sets the `ready` flag to `true` and then calls `cv.notify_all()`.
    - This notifies all threads waiting on the condition variable `cv` that the condition (i.e., `ready` being `true`) has been met.

3. **Thread Wake-Up:**
    - When notified, each waiting thread reacquires the mutex `mtx` (which was automatically released when the thread went to sleep).
    - The thread then checks the condition `ready`. Since `ready` is now `true`, the thread proceeds to print its ID.

### Summary:

Condition variables are used in this code to efficiently synchronize the start of 10 threads. Without condition variables, threads might have to continuously check the condition in a busy-wait loop, which is inefficient. The condition variable `cv` allows threads to wait efficiently, releasing the CPU for other tasks until they are notified to wake up. This ensures that all threads start processing almost simultaneously once the `ready` flag is set to `true` and `cv.notify_all()` is called.

متغیر شرطی 
(condition variable)
 برای هماهنگی و همگام‌سازی بین نخ‌ها استفاده می‌شود. این متغیر اجازه می‌دهد تا نخ‌ها به‌طور کارآمد منتظر بمانند تا شرایط خاصی توسط نخ دیگری برقرار شود و سپس ادامه دهند. در کد ارائه‌شده، نخ‌ها تا زمانی که متغیر 
 ready
  به 
 true
  تغییر یابد و سیگنال داده شود، منتظر می‌مانند و سپس همزمان به اجرا می‌پردازند. این کار باعث جلوگیری از اتلاف منابع سیستم و بهبود هماهنگی بین نخ‌ها می‌شود.  


#### Thread Pool Example (Pseudo-code)

Both thread pools and condition variables serve different purposes in concurrent programming: thread pools manage threads for task execution, while condition variables synchronize threads based on specific conditions or state changes. Each is essential for different aspects of managing concurrency and ensuring efficient resource utilization in multi-threaded applications.

```cpp
    #include <iostream>
    #include <vector>
    #include <thread>
    #include <queue>
    #include <functional>
    #include <mutex>
    #include <condition_variable>

    class ThreadPool {
    public:
        ThreadPool(size_t threads);
        ~ThreadPool();
        void enqueue(std::function<void()> task);

    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;

        void worker_thread();
    };

    ThreadPool::ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back(&ThreadPool::worker_thread, this);
        }
    }

    ThreadPool::~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    void ThreadPool::enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.push(task);
        }
        condition.notify_one();
    }

    void ThreadPool::worker_thread() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) return;
                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
        }
    }

    void exampleTask(int id) {
        std::cout << "Executing task " << id << std::endl;
    }

    int main() {
        ThreadPool pool(4);
        for (int i = 0; i < 10; ++i) {
            pool.enqueue([i] { exampleTask(i); });
        }
        return 0;
    }
```    
##### Explanation:

ThreadPool(size_t threads);: Constructor that starts the specified number of worker threads.
~ThreadPool();: Destructor that joins all worker threads.
void enqueue(std::function<void()> task);: Enqueues a task for execution.
void worker_thread();: Worker thread function that executes tasks from the queue.
##### 3. Embedded Systems Insight
In embedded systems, using smart pointers can help manage dynamic memory safely, and advanced multi-threading techniques can optimize the performance of real-time tasks.

Embedded Example: Sensor Data Processing with Thread Pool (Pseudo-code)

```cpp

    #include <iostream>
    #include <vector>
    #include <thread>
    #include <queue>
    #include <functional>
    #include <mutex>
    #include <condition_variable>

    class ThreadPool {
    public:
        ThreadPool(size_t threads);
        ~ThreadPool();
        void enqueue(std::function<void()> task);

    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;

        void worker_thread();
    };

    ThreadPool::ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back(&ThreadPool::worker_thread, this);
        }
    }

    ThreadPool::~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    void ThreadPool::enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.push(task);
        }
        condition.notify_one();
    }

    void ThreadPool::worker_thread() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) return;
                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
        }
    }

    class Sensor {
    public:
        void readData() {
            std::cout << "Reading sensor data" << std::endl;
        }
    };

    void processSensorData(int id) {
        Sensor sensor;
        sensor.readData();
        std::cout << "Processing data from sensor " << id << std::endl;
    }

    int main() {
        ThreadPool pool(4);
        for (int i = 0; i < 10; ++i) {
            pool.enqueue([i] { processSensorData(i); });
        }
        return 0;
    }
```    
##### Explanation:

processSensorData: Function to read and process sensor data.
pool.enqueue([i] { processSensorData(i); });: Enqueues sensor data processing tasks.

!!! Daily Challenge:
* Create a SensorManager class that uses std::shared_ptr to manage multiple sensor objects.
* Implement a thread pool in the SensorManager to read and process data from multiple sensors concurrently.
* Add error handling to the SensorManager to manage sensor read errors.