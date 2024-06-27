// Create a class template function that finds the maximum of two values

#include <iostream>
using namespace std;

template <typename T>
class Max
{

private:
    T x, y;

public:
    Max(T n, T m) : x(n), y(m) {}
    void display()
    {
        T max;
        max = (x > y) ? x : y;
        cout << "the max of two value is:  " << max << endl;
    }
};

int main()
{

    Max ob(2, 3);
    ob.display();

    return 0;
}


//without class
//********************************************************************* */
/*#include <iostream>
using namespace std;

template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int int1 = 2, int2 = 3;
    double double1 = 5.5, double2 = 3.3;
    char char1 = 'a', char2 = 'z';

    cout << "The maximum of " << int1 << " and " << int2 << " is: " << findMax(int1, int2) << endl;
    cout << "The maximum of " << double1 << " and " << double2 << " is: " << findMax(double1, double2) << endl;
    cout << "The maximum of " << char1 << " and " << char2 << " is: " << findMax(char1, char2) << endl;

    return 0;
}
*/