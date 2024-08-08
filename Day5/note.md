## Understanding Virtual Destructors
A virtual destructor ensures that the destructor of the derived class is called when a base class pointer is used to delete an object. This is crucial for proper cleanup of resources allocated by derived classes.

##### Detailed Explanation
>Polymorphic Deletion:

When dealing with polymorphism (i.e., using base class pointers to point to derived class objects), the destructor of the base class should be virtual. This ensures that when a derived class object is deleted through a base class pointer, the correct destructor (both base and derived) is called.
Resource Management:

If the base class destructor is not virtual, deleting a derived class object through a base class pointer results in undefined behavior. Specifically, the destructor of the derived class won't be called, potentially leading to resource leaks (e.g., memory, file handles).
Example without Virtual Destructor


هنگام برخورد با چندشکلی (یعنی استفاده از اشاره گرهای کلاس پایه برای اشاره به اشیاء کلاس مشتق شده)، تخریب کننده کلاس پایه باید مجازی باشد. این تضمین می کند که وقتی یک شی کلاس مشتق شده از طریق یک اشاره گر کلاس پایه حذف می شود، مخرب صحیح (هم پایه و هم مشتق شده) فراخوانی می شود.
مدیریت منابع:

اگر مخرب کلاس پایه مجازی نباشد، حذف یک شی کلاس مشتق شده از طریق اشاره گر کلاس پایه منجر به رفتار نامشخص می شود. به طور خاص، مخرب کلاس مشتق شده فراخوانی نمی شود، که به طور بالقوه منجر به نشت منابع (به عنوان مثال، حافظه، دسته فایل) می شود.م

***

>Consider the following example where the destructor is not virtual:
```cpp
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
```
>Output:

Base destructor
***
In this case, only the Base destructor is called, and the Derived destructor is not, leading to improper cleanup.

Example with Virtual Destructor
>consider the example with a virtual destructor:

```cpp
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
```
***
>Output:


Derived destructor
Base destructor
***
In this case, both the Derived and Base destructors are called, ensuring proper cleanup.

###### Applying this to Your Code
In your code, the Task class is a base class with derived classes PrintTask and ComputeTask. By defining a virtual destructor in Task, you ensure that if an object of PrintTask or ComputeTask is deleted through a Task pointer, the appropriate destructor of the derived class is called.

>Your Code with Explanation
```cpp
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
```    
***
In this code, virtual ~Task() = default; ensures that the destructors of PrintTask and ComputeTask are correctly called when a Task pointer to these objects is deleted, ensuring proper cleanup.


### Destructor (دستور مخرب) چیست و چرا به آن نیاز داریم؟

**Destructor** یا دستور مخرب، یک تابع خاص در یک کلاس است که هنگام تخریب شیء (به پایان رسیدن دوره عمر شیء)، به صورت خودکار فراخوانی می‌شود. نام دستور مخرب همان نام کلاس است، با یک علامت 
`~` 
در ابتدای آن. برای مثال، اگر نام کلاس 
`MyClass` 
باشد، دستور مخرب به شکل 
`~MyClass()`
 خواهد بود.

#### چرا به Destructor نیاز داریم؟
1. **پاکسازی حافظه و منابع**: اگر شیء از منابعی مانند حافظه پویا، فایل‌ها یا شبکه استفاده می‌کند، دستور مخرب وظیفه دارد این منابع را آزاد کند تا از نشت حافظه 
(Memory Leak) 
یا قفل شدن منابع جلوگیری شود.
2. **جمع‌آوری و مدیریت منابع**: هنگام اتمام کار با یک شیء، باید منابع مرتبط با آن (مانند حافظه، فایل‌ها، یا قفل‌ها) به درستی آزاد شوند تا سیستم کارآیی مناسبی داشته باشد.

### Destructor مجازی (Virtual Destructor) چیست و چرا از آن استفاده می‌کنیم؟

یک 
**Virtual Destructor**
 یا دستور مخرب مجازی، دستوری است که با استفاده از کلمه کلیدی 
`virtual` تعریف می‌شود. این دستور در کلاس پایه تعریف می‌شود تا تخریب صحیح شیء در سلسله مراتب ارث‌بری 
(Inheritance Hierarchy)
 تضمین شود.

#### چرا و چه زمانی از Destructor مجازی استفاده می‌کنیم؟
1. **تخریب صحیح اشیاء در ارث‌بری**: اگر یک کلاس دارای کلاس‌های مشتق شده باشد و در برنامه از اشاره‌گر به کلاس پایه برای کار با اشیاء کلاس‌های مشتق شده استفاده شود، باید دستور مخرب پایه مجازی باشد. این کار اطمینان می‌دهد که هنگام حذف شیء، دستور مخرب کلاس مشتق شده نیز به درستی فراخوانی می‌شود. در غیر این صورت، تنها دستور مخرب کلاس پایه فراخوانی شده و منابع خاص کلاس مشتق شده ممکن است آزاد نشوند، که می‌تواند منجر به نشت منابع شود.

2. **پرهیز از مشکلات حافظه**: اگر دستور مخرب پایه مجازی نباشد و شیء از طریق اشاره‌گر به کلاس پایه حذف شود، ممکن است تنها بخش پایه شیء تخریب شود و بخش‌های دیگر آن (مربوط به کلاس‌های مشتق شده) تخریب نشوند. این موضوع می‌تواند باعث مشکلات جدی حافظه و منابع شود.

#### مثال از Destructor مجازی

```cpp
class Base {
public:
    virtual ~Base() {
        cout << "Base Destructor" << endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived Destructor" << endl;
    }
};

int main() {
    Base *obj = new Derived();
    delete obj;  // فراخوانی دستور مخرب مجازی
    return 0;
}
```

در این مثال، چون دستور مخرب 
`Base`
 مجازی است، زمانی که شیء از طریق اشاره‌گر به 
`Base` حذف می‌شود 
(`delete obj`)
، دستور مخرب 
`Derived`
 نیز به درستی فراخوانی شده و همه منابع آزاد می‌شوند. در صورت عدم استفاده از دستور مخرب مجازی، تنها دستور مخرب 
`Base`
 فراخوانی شده و منابع مرتبط با 
`Derived`
 آزاد نمی‌شوند، که باعث نشت حافظه خواهد شد.