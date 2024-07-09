### Day 8: Custom Allocators, Advanced Template Programming, and RTOS
##### 1. Custom Allocators
Custom allocators allow you to control memory allocation and deallocation. This can be useful in embedded systems where memory resources are limited and need to be managed carefully.

تخصیص دهنده های سفارشی به شما این امکان را می دهند که تخصیص حافظه را کنترل کنید. این می تواند در سیستم های جاسازی شده که منابع حافظه محدود هستند و نیاز به مدیریت دقیق دارند مفید باشد.

##### Custom Allocator Example 
این کد یک تخصیص‌دهنده حافظه سفارشی به نام `CustomAllocator` تعریف می‌کند که می‌تواند حافظه را برای انواع مختلف تخصیص و آزاد کند. این تخصیص‌دهنده هنگام تخصیص و آزادسازی حافظه پیام‌هایی را چاپ می‌کند. از این تخصیص‌دهنده می‌توان برای ردیابی و مدیریت بهتر تخصیص حافظه در پروژه‌ها استفاده کرد. این باعث می‌شود که بتوانید بهره‌وری و کارایی تخصیص حافظه را بهبود بخشید و مشکلات احتمالی در تخصیص حافظه را شناسایی کنید. استفاده از تخصیص‌دهنده سفارشی در پروژه‌هایی که نیاز به مدیریت دقیق حافظه دارند توصیه می‌شود.

```cpp

#include <iostream>
#include <memory>

template <typename T>
class CustomAllocator { //The class is templated, meaning it can be used with any data type T.
public:
    using value_type = T; //This defines a type alias value_type for T. This is required for compatibility with the standard allocator interface used by the C++ Standard Library.


    CustomAllocator() = default; //The default constructor is defined and uses the default keyword, which means it will use the compiler-generated default implementation.

    template <typename U> 
    CustomAllocator(const CustomAllocator<U>&) {}

    T* allocate(std::size_t n) {  // the number of objects to allocate
        if (n > std::size_t(-1) / sizeof(T)) //checks for overflow to prevent allocating more memory than is possible.
            throw std::bad_alloc();
        T* p = static_cast<T*>(::operator new(n * sizeof(T)));// allocates memory using the global ::operator new and casts it to the correct type.
        std::cout << "Allocating " << n * sizeof(T) << " bytes" << std::endl;//- prints a message indicating the amount of memory being allocated.
        return p; //Returns a pointer to the allocated memory.
    }

//Deallocate Method 
    void deallocate(T* p, std::size_t) {  //pointer to the memory to deallocate
        std::cout << "Deallocating memory" << std::endl; //prints a message indicating that memory is being deallocated.
        ::operator delete(p);//deallocates memory using the global ::operator delete.
    }
};

template <typename T, typename U>
bool operator==(const CustomAllocator<T>&, const CustomAllocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const CustomAllocator<T>&, const CustomAllocator<U>&) { return false; }

int main() {
    std::vector<int, CustomAllocator<int>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
##### Explanation:

The CustomAllocator class provides custom memory allocation and deallocation functionality with logging to track memory usage. It implements the basic interface required by C++ Standard Library containers, making it usable as a custom allocator for these containers.

allocate: Allocates memory for n objects of type T.
deallocate: Deallocates memory.
std::vector<int, CustomAllocator<int>> vec: Uses CustomAllocator with std::vector.
#### 2. Advanced Template Programming
Advanced template programming techniques can help create more flexible and reusable code.

##### Variadic Templates

Variadic templates allow you to create functions and classes that accept a variable number of arguments.

######  Variadic Templates Example

```cpp

#include <iostream>

// Base case
void print() {
    std::cout << std::endl;
}

// Recursive case
template <typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(args...);
}

int main() {
    print(1, 2.5, "Hello", 'a');
    return 0;
}
```
##### Explanation:

output:
1 2.5 Hello a
* template <typename T, typename... Args> void print(T first, Args... args): Template function that accepts a variable number of arguments.
* print(args...): Recursively calls print with the remaining arguments.
Template Specialization

#### 3.Template specialization:
 allows you to provide different implementations of a template for specific types.

###### Template Specialization Example

```cpp

#include <iostream>

template <typename T>
void printType(T value) {
    std::cout << "Generic type" << std::endl;
}

template <>
void printType(int value) {
    std::cout << "Integer type" << std::endl;
}

template <>
void printType(double value) {
    std::cout << "Double type" << std::endl;
}

int main() {
    printType(1);
    printType(2.5);
    printType("Hello");
    return 0;
}
```
##### Explanation:
output:
Integer type
Double type
Generic type

template <> void printType(int value): Specialization for int.
template <> void printType(double value): Specialization for double.
#### 3. Real-Time Operating Systems (RTOS)
RTOS is designed for real-time applications that require precise timing and predictable behavior. It is commonly used in embedded systems.

### RTOS Concepts

* Tasks: Basic units of execution in an RTOS.
* Scheduling: Determines the order in which tasks are executed.
* Synchronization: Mechanisms like semaphores and mutexes to manage task interaction.
* Interrupt Handling: RTOS can handle interrupts efficiently.
#####  RTOS (Pseudo-code using FreeRTOS)

```cpp

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

SemaphoreHandle_t xSemaphore;

void vTask1(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE) {
            // Critical section
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vTask2(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE) {
            // Critical section
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

int main() {
    xSemaphore = xSemaphoreCreateMutex();

    if (xSemaphore != NULL) {
        xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
        xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);

        vTaskStartScheduler();
    }

    for (;;);

    return 0;
}
```
##### Explanation:

xSemaphoreCreateMutex(): Creates a mutex semaphore.
xTaskCreate: Creates tasks.
vTaskStartScheduler(): Starts the RTOS scheduler.

!!! Daily Challenge:
* Implement a custom allocator that tracks the number of allocations and deallocations.
* Create a variadic template function to concatenate strings.
* Write a simple RTOS task that toggles an LED with a specific frequency.
