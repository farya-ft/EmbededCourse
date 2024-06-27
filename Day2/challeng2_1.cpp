// Create a Person class with name and age attributes. Include a constructor to initialize these attributes and a method to display them.

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class person
{
private:
    string name;
    int age;

public:
    person(string n, int x) : name(n), age(x) {}
    void display()
    {
        cout << "the name and the age are :" << name << age << endl;
    }
};
int main()
{

    int x = 20;
    string n = "sara";
    person obj(n, x);
    obj.display();
}