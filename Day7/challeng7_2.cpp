//std::shared_ptr: Allows multiple smart pointers to share ownership of a resource.


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


/*In the context of std::shared_ptr in C++, the use_count() method returns the number of std::shared_ptr instances that manage the same object.
 This is also known as the reference count.
 The reference count for the managed object is initialized to 1. 
 When main function exits, ptr1 is destroyed.
The reference count drops to 0, triggering the destruction of the managed MyClass object.
The MyClass destructor is called. */