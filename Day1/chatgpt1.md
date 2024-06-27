
## Day 1: Introduction to C++ and Basic Syntax

Today, we'll start with the very basics of C++: understanding the syntax and writing your first program.

>Code: Hello, World!

    #include <iostream>

    int main() {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    }
##### Explanation:

#include <iostream>: Includes the Input/Output stream library.
int main() { ... }: The main function where execution starts.
std::cout << "Hello, World!" << std::endl;: Outputs the string to the console.
return 0;: Ends the program.
Embedded Systems Note:
In embedded systems, we typically don't have a console. Instead, we might write to a serial port or control hardware directly. However, understanding standard C++ is crucial before diving into embedded specifics.

#### OOP Concept: Classes and Objects
> Code: Simple Class Example


    #include <iostream>
    #include <string>

    class HelloWorld {
    public:
        void sayHello() {
            std::cout << "Hello, World from a class!" << std::endl;
        }
    };

    int main() {
        HelloWorld hello;
        hello.sayHello();
        return 0;
    }
##### Explanation:

class HelloWorld { ... };: Defines a class named HelloWorld.
void sayHello() { ... }: A public method that prints a message.
HelloWorld hello;: Creates an object of the class HelloWorld.
hello.sayHello();: Calls the sayHello method on the object.
Daily Challenge:
Modify the HelloWorld class to accept a custom message and print it.
Write a program that creates multiple HelloWorld objects, each with a different message.
Embedded Systems Insight:
In embedded systems, classes are often used to encapsulate hardware functionality. For example, you might have a class LED with methods to turn the LED on and off.

Feel free to ask any questions or request further explanations on today's topics. Tomorrow, we'll dive into variables, data types, and more OOP concepts!

