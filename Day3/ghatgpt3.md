## Day 3: Control Structures and Inheritance
1. Control Structures: If-Else and Loops
Control structures allow you to control the flow of your program based on conditions.

> If-Else Statement


    #include <iostream>

    int main() {
        int x = 10;

        if (x > 0) {
            std::cout << "x is positive" << std::endl;
        } else if (x == 0) {
            std::cout << "x is zero" << std::endl;
        } else {
            std::cout << "x is negative" << std::endl;
        }

        return 0;
    }
***
##### Explanation:

if (x > 0) { ... }: Executes the block if the condition is true.
else if (x == 0) { ... }: Executes the block if the previous conditions are false and this condition is true.
else { ... }: Executes the block if all previous conditions are false.
> For Loop:


    #include <iostream>

    int main() {
        for (int i = 0; i < 5; i++) {
            std::cout << "i: " << i << std::endl;
        }

        return 0;
    }
***
##### Explanation:

for (int i = 0; i < 5; i++) { ... }: Repeats the block 5 times, with i ranging from 0 to 4.
> While Loop


    #include < iostream >

    int main() {
        int i = 0;

        while (i < 5) {
            std::cout << "i: " << i << std::endl;
            i++;
        }

        return 0;
    }
***
#### Explanation:

while (i < 5) { ... }: Repeats the block as long as the condition is true.
##### 2. Advanced OOP Concept: Inheritance
Inheritance allows you to create new classes based on existing classes. This promotes code reuse and establishes a relationship between the base and derived classes.

> Code: Inheritance Example

    #include < iostream >
    #include < string >

    // Base class
    class Animal {
    public:
        Animal(const std::string &name) : name(name) {}

        void speak() const {
            std::cout << "Animal sound" << std::endl;
        }

    protected:
        std::string name;
    };

    // Derived class
    class Dog : public Animal {
    public:
        Dog(const std::string &name) : Animal(name) {}

        void speak() const {
            std::cout << name << " says: Woof!" << std::endl;
        }
    };

    int main() {
        Animal animal("Generic Animal");
        Dog dog("Buddy");

        animal.speak(); // Calls base class method
        dog.speak();    // Calls derived class method

        return 0;
    }
***
##### Explanation:

class Animal { ... };: Base class with a constructor and a method speak.
class Dog : public Animal { ... };: Derived class that inherits from Animal and overrides the speak method.
Dog(const std::string &name) : Animal(name) {}: Calls the base class constructor from the derived class.
3. Embedded Systems Insight
In embedded systems, inheritance can be used to create specific drivers or handlers based on generic interfaces. For instance, you might have a generic Sensor class and specific classes for different types of sensors.

> Embedded Example: Sensor Inheritance (Pseudo-code)


    #include <iostream>

    // Pseudo-code for an embedded environment
    class Sensor {
    public:
        virtual void read() = 0; // Pure virtual function
    };

    class TemperatureSensor : public Sensor {
    public:
        void read() override {
            // Read temperature value
            std::cout << "Reading temperature" << std::endl;
        }
    };

    class PressureSensor : public Sensor {
    public:
        void read() override {
            // Read pressure value
            std::cout << "Reading pressure" << std::endl;
        }
    };

    int main() {
        TemperatureSensor tempSensor;
        PressureSensor pressureSensor;

        tempSensor.read();
        pressureSensor.read();

        return 0;
    }
***
#### Explanation:

class Sensor { ... };: Abstract base class with a pure virtual function read.
class TemperatureSensor : public Sensor { ... }; and class PressureSensor : public Sensor { ... };: Derived classes that implement the read method.
Daily Challenge:
Create a Vehicle base class with make and model attributes and a method to display them. Derive a Car class that adds a numberOfDoors attribute and a method to display all details.
Write a program that creates multiple Car objects and displays their details.