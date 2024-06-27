//Write a program that creates multiple Person objects and displays their details.

#include <iostream>
#include <vector>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    // Constructor
    Person(std::string n, int a) : name(n), age(a) {}

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Getter for age
    int getAge() const {
        return age;
    }

    // Method to display person details
    void displayDetails() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    // Vector to store Person objects
    std::vector<Person> people;

    // Creating Person objects
    people.push_back(Person("Alice", 30));
    people.push_back(Person("Bob", 25));
    people.push_back(Person("Charlie", 20));

    // Displaying details of each person
    for (const auto& person : people) {
        person.displayDetails();
    }

    return 0;
}
