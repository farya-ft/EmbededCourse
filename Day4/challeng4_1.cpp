//Create a Shape base class with a pure virtual method area. Derive two classes, Circle and Rectangle, that implement the area method.


#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;  // Pure virtual function
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}  // Constructor to initialize radius

    double area() override {
        return 3.14 * radius * radius;
    }
};

class Rectangle : public Shape {
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}  // Constructor to initialize length and width

    double area() override {
        return length * width;
    }
};

int main() {
    Circle crl(2);
    Rectangle rct(2, 3);

    cout << "The area of the circle is: " << crl.area() << endl;
    cout << "The area of the rectangle is: " << rct.area() << endl;

    return 0;
}
