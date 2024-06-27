//  Modify the HelloWorld class to accept a custom message and print it.

#include <iostream>
#include <string>
using namespace std;

class HelloWorld
{
public:
    void s(string massage)
    {
        cout << "Your Massage is:" << massage << endl;
    }
};

int main()
{
    HelloWorld ob;
    string massage;
    cout << " enter your massage:" << endl;
    getline(cin, massage);
    ob.s(massage);
    return 0;
}
