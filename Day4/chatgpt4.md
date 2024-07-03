## Day 4: Functions and Polymorphism
#### 1. Functions
Functions are reusable blocks of code that perform a specific task. They help in organizing code, reducing redundancy, and improving readability.

#### Basic Function Example

```cpp
    #include < iostream >

    // Function declaration
    int add(int a, int b);

    int main() {
        int sum = add(5, 3);
        std::cout << "Sum: " << sum << std::endl;
        return 0;
    }

    // Function definition
    int add(int a, int b) {
        return a + b;
    }
```    
***
##### Explanation:

int add(int a, int b);: Function declaration.
int add(int a, int b) { ... }: Function definition. It takes two integers and returns their sum.
sum = add(5, 3);: Calls the add function with arguments 5 and 3.
#### Function Overloading

>Function overloading allows you to define multiple functions with the same name but different parameter lists.
```cpp
    #include < iostream >

    // Function overloading
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
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

Two add functions, one for integers and one for doubles.
The correct function is called based on the argument types.
#### 2. Advanced OOP Concept: Polymorphism
Polymorphism allows methods to do different things based on the object it is acting upon, even if they share the same name.

>Code: Polymorphism Example

```cpp
    #include < iostream >
    #include < string >

    // Base class
    class Animal {
    public:
        virtual void speak() const {
            std::cout << "Animal sound" << std::endl;
        }
    };

    // Derived class
    class Dog : public Animal {
    public:
        void speak() const override {
            std::cout << "Woof!" << std::endl;
        }
    };

    // Derived class
    class Cat : public Animal {
    public:
        void speak() const override {
            std::cout << "Meow!" << std::endl;
        }
    };

    void makeAnimalSpeak(const Animal &animal) {
        animal.speak();
    }

    int main() {
        Dog dog;
        Cat cat;

        makeAnimalSpeak(dog); // Outputs: Woof!
        makeAnimalSpeak(cat); // Outputs: Meow!

        return 0;
    }
```    
***
##### Explanation:

virtual void speak() const { ... }: Declares a virtual method in the base class.
void speak() const override { ... }: Overrides the base class method in derived classes.
makeAnimalSpeak(const Animal &animal) { ... }: Accepts an Animal reference and calls the speak method. The correct method is called based on the actual object type (Dog or Cat).
#### 3. Embedded Systems Insight
In embedded systems, polymorphism can be used to handle different types of sensors or devices in a uniform way.

>Embedded Example: Polymorphism (Pseudo-code)
```cpp

    #include < iostream >

    // Base class
    class Sensor {
    public:
        virtual void read() = 0; // Pure virtual function
    };

    // Derived class for temperature sensor
    class TemperatureSensor : public Sensor {
    public:
        void read() override {
            // Read temperature value
            std::cout << "Reading temperature" << std::endl;
        }
    };

    // Derived class for pressure sensor
    class PressureSensor : public Sensor {
    public:
        void read() override {
            // Read pressure value
            std::cout << "Reading pressure" << std::endl;
        }
    };

    void readSensor(Sensor &sensor) {
        sensor.read();
    }

    int main() {
        TemperatureSensor tempSensor;
        PressureSensor pressureSensor;

        readSensor(tempSensor);  // Outputs: Reading temperature
        readSensor(pressureSensor);  // Outputs: Reading pressure

        return 0;
    }
```    
***
##### Explanation:

virtual void read() = 0;: Declares a pure virtual function in the base class Sensor.
void read() override { ... }: Implements the read method in derived classes.
readSensor(Sensor &sensor) { ... }: Accepts a Sensor reference and calls the read method, demonstrating polymorphism.

!!! Daily Challenge:
Create a Shape base class with a pure virtual method area. Derive two classes, Circle and Rectangle, that implement the area method.
Write a program that creates instances of Circle and Rectangle, stores them in an array of Shape pointers, and prints their areas.