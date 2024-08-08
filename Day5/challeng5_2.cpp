// Create a class Task with a pure virtual method execute. Derive two classes, PrintTask and ComputeTask, that implement the execute method.
//  Use multi-threading to run instances of PrintTask and ComputeTask concurrently.

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

// Base class with pure virtual method
class Task
{
public:
    virtual void execute() = 0; // Pure virtual method
    virtual ~Task() = default; 
     // we ensure that the destructors of PrintTask and ComputeTask are correctly called when a Task pointer
     // to these objects is deleted, ensuring proper cleanup.
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
    //با استفاده از 
    //join()،
    // برنامه منتظر می‌ماند تا هر دو ریسمان کارشان را به اتمام برسانند،
    // سپس برنامه به پایان می‌رسد.
    printThread.join();
    computeThread.join();

    return 0;
}


/*  You can directly pass the member function pointer along with the object to std::thread. This approach requires using the 
    &ClassName::MemberFunction syntax and providing the object on which the member function should be called.

        thread printThread(&Task::execute, &printTask);
        thread computeThread(&Task::execute, &computeTask);

   */

  /*
  اگر تابع 
  runTask
   را تعریف نکنید و به جای آن به طور مستقیم متد 
  execute
   را از طریق شیء 
  Task
   فراخوانی کنید،
   
   int main()
{
    PrintTask printTask;
    ComputeTask computeTask;

    // ایجاد رشته‌های جدید و اجرای مستقیم متدهای عضو از کلاس‌های مشتق شده
    thread printThread(&Task::execute, &printTask);
    thread computeThread(&Task::execute, &computeTask);

    // منتظر ماندن برای اتمام کار هر دو رشته
    printThread.join();
    computeThread.join();

    return 0;
}

   
   
   */