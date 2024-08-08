## Day 5: Templates, Exception Handling, and Multi-threading
#### 1. Templates
Templates allow you to create functions and classes that operate with generic types. This can make your code more flexible and reusable.

>Function Template Example
```cpp

    #include <iostream>

    template <typename T>
    T add(T a, T b) {
        return a + b;
    }

    int main() {
        int intSum = add(5, 3);
        double doubleSum = add(5.5, 3.3);
        std::cout << "Integer Sum: " << intSum << std::endl;
        std::cout << "Double Sum: " << doubleSum << std::endl;
    
    return 0;
    }
```    
***
##### Explanation:

template < typename T >: Declares a template.
T add(T a, T b) { ... }: Defines a function template that works with any type T.
>Class Template Example
```cpp

    #include < iostream >

    template < typename T >
    class Box {
    public:
        Box(T value) : value(value) {}

        T getValue() const {
            return value;
        }

    private:
        T value;
    };

    int main() {
        Box< int > intBox(123);
        Box< double > doubleBox(456.78);
        std::cout << "Integer Box: " << intBox.getValue() << std::endl;
        std::cout << "Double Box: " << doubleBox.getValue() << std::endl;
        return 0;
    }
```
***
##### Explanation:

template < typename T >: Declares a class template.
Box(T value) : value(value) {}: Template constructor.
T getValue() const { ... }: Template member function.
#### 2. Exception Handling
Exception handling allows you to manage errors and exceptional conditions in your program.

>Exception Handling Example
```cpp
    #include < iostream >
    #include < stdexcept >

    int divide(int a, int b) {
        if (b == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }

    int main() {
        try {
            int result = divide(10, 0);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return 0;
    }
```

***
##### Explanation:

throw std::invalid_argument("Division by zero");: Throws an exception if the denominator is zero.
try { ... } catch (const std::invalid_argument &e) { ... }: Catches and handles the exception.
#### 3. Multi-threading
Multi-threading allows you to run multiple threads (smaller units of a process) concurrently. This is especially useful in embedded systems for handling tasks like sensor reading and data processing simultaneously.

>Multi-threading Example Using std::thread
```cpp

    #include <iostream>
    #include <thread>

    // Function to be executed by a thread
    void threadFunction(int threadId) {
     for (int i = 0; i < 5; ++i) {
         std::cout << "Thread " << threadId << " executing" << std::endl;
     }
    }

    int main() {
      std::thread t1(threadFunction, 1);
      std::thread t2(threadFunction, 2);

       t1.join();
       t2.join();

      return 0;
    }
```    
***
##### Explanation:

std::thread t1(threadFunction, 1);: Creates a new thread that runs threadFunction with 1 as an argument and also threadId.
t1.join();: Waits for t1 to finish execution.
#### 4. Embedded Systems Insight with Multi-threading
In embedded systems, multi-threading can be used to manage concurrent tasks such as sensor data acquisition and user interface updates.

>Embedded Example: Multi-threading (Pseudo-code)

```cpp
    #include < iostream >
    #include < thread>
    #include < chrono>

    // Pseudo-code for an embedded environment
    class Sensor {
    public:
        void readSensorData() {
            while (true) {
                // Simulate reading sensor data
                std::cout << "Reading sensor data" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    };

    class Display {
    public:
        void updateDisplay() {
            while (true) {
                // Simulate updating the display
                std::cout << "Updating display" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    };

    int main() {
        Sensor sensor;
        Display display;

        std::thread sensorThread(&Sensor::readSensorData, &sensor);
        std::thread displayThread(&Display::updateDisplay, &display);

        sensorThread.join();
        displayThread.join();

        return 0;
    }
```    
***
##### Explanation:

Explanation of std::this_thread::sleep_for
std::this_thread::sleep_for is a function from the <thread> library that puts the current thread to sleep for the specified duration.
std::chrono::seconds(1) creates a duration object representing 1 second.
###### Why Use sleep_for?
Using sleep_for in a loop is common in embedded systems and other environments where periodic actions are required. In this example:

sensorThread reads sensor data every second.
displayThread updates the display every two seconds.

By pausing the thread, the program can simulate periodic tasks without constantly consuming CPU resources.

std::thread sensorThread(&Sensor::readSensorData, &sensor);: Creates a thread that runs readSensorData on a Sensor object.
std::thread displayThread(&Display::updateDisplay, &display);: Creates a thread that runs updateDisplay on a Display object.
sensorThread.join();: Waits for the sensor thread to finish.
displayThread.join();: Waits for the display thread to finish.

!!! Daily Challenge:
1.Create a template function that finds the maximum of two values.
2.Create a class Task with a pure virtual method execute. Derive two classes, PrintTask and ComputeTask, that implement the execute method. Use multi-threading to run instances of PrintTask and ComputeTask concurrently.
3.Write exception handling for a scenario where a sensor fails to initialize.



 