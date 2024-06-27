
//std::unique_ptr: Owns a resource exclusively. No other smart pointer can own the same resource.

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
