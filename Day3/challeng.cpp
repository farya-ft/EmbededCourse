/*Create a Vehicle base class with make and model attributes and a method to display them. Derive a Car class that adds a numberOfDoors attribute and a method to display all details.
Write a program that creates multiple Car objects and displays their details.*/

#include <iostream>
#include <string>

using namespace std;

class vehicle
{
private:
    string make;
    int model;

public:
    vehicle(const string &make, int model) : make(make), model(model) {}

    virtual void display()
    {
        cout << "make: " << make << "   model: " << model << endl;
    }
};
class car : public vehicle
{
private:
    int numberofdoors;

public:
    car(const string &make, int model, int numberofdoors) : vehicle(make, model), numberofdoors(numberofdoors) {}

    void display() override
    {
        vehicle::display();
        cout << "numberofdoord: " << numberofdoors << endl;
    }
};
int main()
{

    Car car1("Germany", 2020, 4);
    Car car2("Japan", 2018, 2);
    Car car3("USA", 2021, 4);

    car1.display();
    car2.display();
    car3.display();
    return 0;
}
