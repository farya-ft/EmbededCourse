// Write a program that creates multiple HelloWorld objects, each with a different message.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HelloWorld {
public:
    HelloWorld(const string &msg) : message(msg) {}  // A constructor that initializes the message member variable with the given msg string.

    void displayMessage() const {      //const: Indicates that this member function does not modify any member variables.
        cout << message << endl;
    }

private:
    string message;
};

int main() {
    vector<string> messages = {     // Initializes a vector of strings containing different messages.
        "Hello, World!",
        "Hello, C++!",
        "Hello, OpenAI!",
        "Hello, Universe!",
        "Hello, Everyone!"
    };

     vector<HelloWorld> helloObjects;    // Declares a vector to store HelloWorld objects.
    for (const auto &msg : messages) {
        helloObjects.emplace_back(msg);    //Iterates over each message in the messages vector
    }

    for (const auto &obj : helloObjects) {   //Iterates over each HelloWorld object in the helloObjects vector
        obj.displayMessage();        //Calls the displayMessage method of each HelloWorld object to print the message.
    }

    return 0;
}
