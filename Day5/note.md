## Understanding Virtual Destructors
A virtual destructor ensures that the destructor of the derived class is called when a base class pointer is used to delete an object. This is crucial for proper cleanup of resources allocated by derived classes.

##### Detailed Explanation
>Polymorphic Deletion:

When dealing with polymorphism (i.e., using base class pointers to point to derived class objects), the destructor of the base class should be virtual. This ensures that when a derived class object is deleted through a base class pointer, the correct destructor (both base and derived) is called.
Resource Management:

If the base class destructor is not virtual, deleting a derived class object through a base class pointer results in undefined behavior. Specifically, the destructor of the derived class won't be called, potentially leading to resource leaks (e.g., memory, file handles).
Example without Virtual Destructor
>Consider the following example where the destructor is not virtual:

class Base {
public:
    ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    Base* obj = new Derived();
    delete obj; // Undefined behavior: Only Base destructor is called
    return 0;
}
>Output:

Base destructor
***
In this case, only the Base destructor is called, and the Derived destructor is not, leading to improper cleanup.

Example with Virtual Destructor
>consider the example with a virtual destructor:


class Base {
public:
    virtual ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    Base* obj = new Derived();
    delete obj; // Proper behavior: Both Base and Derived destructors are called
    return 0;
}
***
>Output:


Derived destructor
Base destructor
***
In this case, both the Derived and Base destructors are called, ensuring proper cleanup.

###### Applying this to Your Code
In your code, the Task class is a base class with derived classes PrintTask and ComputeTask. By defining a virtual destructor in Task, you ensure that if an object of PrintTask or ComputeTask is deleted through a Task pointer, the appropriate destructor of the derived class is called.

>Your Code with Explanation

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

// Base class with pure virtual method
class Task
{
public:
    virtual void execute() = 0; // Pure virtual method
    virtual ~Task() = default; // Virtual destructor for proper cleanup
};

// Derived class PrintTask
class PrintTask : public Task
{
public:
    void execute() override
    {
        for (int i = 0; i < 10; ++i)
        {
            cout << "PrintTask: " << i << endl;
        }
    }
};

// Derived class ComputeTask
class ComputeTask : public Task
{
public:
    void execute() override
    {
        int sum = 0;
        for (int i = 1; i <= 10; ++i)
        {
            sum += i;
            cout << "ComputeTask: sum = " << sum << endl;
        }
    }
};

// Function to run a task
void runTask(Task *task)
{
    task->execute();
}

int main()
{
    // Create instances of PrintTask and ComputeTask
    PrintTask printTask;
    ComputeTask computeTask;

    // Create threads to run the tasks concurrently
    thread printThread(runTask, &printTask);
    thread computeThread(runTask, &computeTask);

    // Wait for both threads to finish
    printThread.join();
    computeThread.join();

    return 0;
}
***
In this code, virtual ~Task() = default; ensures that the destructors of PrintTask and ComputeTask are correctly called when a Task pointer to these objects is deleted, ensuring proper cleanup.