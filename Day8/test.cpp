/* #include <iostream>

// Base case
void print() {
    std::cout << std::endl;
}

// Recursive case
template <typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(args...);
}

int main() {
    print(1, 2.5, "Hello", 'a');
    return 0;
} */


#include <iostream>

template <typename T>
void printType(T value) {
    std::cout << "Generic type" << std::endl;
}

template <>
void printType(int value) {
    std::cout << "Integer type" << std::endl;
}

template <>
void printType(double value) {
    std::cout << "Double type" << std::endl;
}

int main() {
    printType(1);
    printType(2.5);
    printType("Hello");
    return 0;
}