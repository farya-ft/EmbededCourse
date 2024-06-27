
//Write a program that creates instances of Circle and Rectangle, stores them in an array of Shape pointers, and prints their areas.


#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;  // Pure virtual function
    virtual ~Shape() {}  // Virtual destructor
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}  // Constructor to initialize radius

    double area() const override {
        return 3.14 * radius * radius;
    }
};

class Rectangle : public Shape {
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}  // Constructor to initialize length and width

    double area() const override {
        return length * width;
    }
};

int main() {
    // Create instances of Circle and Rectangle
    Shape* shapes[2];
    shapes[0] = new Circle(2.0);
    shapes[1] = new Rectangle(2.0, 3.0);

    // Print the areas of the shapes
    for (int i = 0; i < 2; ++i) {
        cout << "The area of shape " << i + 1 << " is: " << shapes[i]->area() << endl;
    }

    // Clean up the allocated memory
    for (int i = 0; i < 2; ++i) {
        delete shapes[i];
    }

    return 0;
}
