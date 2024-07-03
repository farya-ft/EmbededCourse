

## Day 2: Variables, Data Types, and Constructors
### 1. Variables and Data Types
In C++, variables are used to store data. Each variable has a type, which determines the kind of data it can hold.

Basic Data Types:

    int: Integer type
    float: Floating-point type
    double: Double-precision floating-point type
    char: Character type
    bool: Boolean type
    Code: Basic Variables

***
```cpp
    #include <iostream>

    int main() {
        int myInt = 5;
        float myFloat = 5.99;
        double myDouble = 9.98;
        char myChar = 'A';
        bool myBool = true;

        std::cout << "Integer: " << myInt << std::endl;
        std::cout << "Float: " << myFloat << std::endl;
        std::cout << "Double: " << myDouble << std::endl;
        std::cout << "Char: " << myChar << std::endl;
        std::cout << "Bool: " << myBool << std::endl;

        return 0;
    }
```
****
#### Explanation:

Declares variables of different types and initializes them.
Prints their values using std::cout.
2. Constructors
Constructors are special member functions of a class that are executed whenever new objects of that class are created. Constructors have the same name as the class and do not have a return type.

#### Code: Class with Constructor

```cpp
    #include <iostream>
    #include <string>

    class HelloWorld {
    public:
        HelloWorld(const std::string &message) {
            this->message = message;
        }

        void sayHello() {
            std::cout << message << std::endl;
        }

    private:
        std::string message;
    };

    int main() {
        HelloWorld hello1("Hello from object 1!");
        HelloWorld hello2("Hello from object 2!");

        hello1.sayHello();
        hello2.sayHello();

        return 0;
    }
```    
***
#### Explanation:

HelloWorld(const std::string &message): Constructor that initializes the message member variable.
this->message = message;: this is a pointer to the current object. It is used to access the object's members.
The sayHello method prints the message.
3. Embedded Systems Insight
In embedded systems, we often use variables to store sensor readings or to control actuators. Constructors can be useful to initialize hardware components, like setting up communication protocols or initial states.

### Embedded Example: LED Control (Pseudo-code)

```cpp
    #include <iostream>

    // Pseudo-code for an embedded environment
    class LED {
    public:
        LED(int pin) {
            // Initialize the pin
            this->pin = pin;
            pinMode(pin, OUTPUT);
        }

        void on() {
            digitalWrite(pin, HIGH);
        }

        void off() {
            digitalWrite(pin, LOW);
        }

    private:
        int pin;
    };

    int main() {
        LED led1(13);  // Assuming pin 13 for an LED
        led1.on();

        // Some delay
        delay(1000);

        led1.off();

        return 0;
    }
```    
***
#### Explanation:

LED(int pin): Constructor initializes the pin.
on() and off() methods control the LED.
Note: pinMode, digitalWrite, and delay are typical functions in Arduino-like environments.

!!! Daily Challenge:
Create a Person class with name and age attributes. Include a constructor to initialize these attributes and a method to display them.
Write a program that creates multiple Person objects and displays their details.
