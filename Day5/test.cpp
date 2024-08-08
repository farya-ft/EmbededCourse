#include <iostream>

using namespace std;
 template<typename T>

 class Max{
   private:
   T x,y;
   public:
   Max(T a,T b):x(a),y(b){}
   
    T find(){
    T max;
   max= (x>y)? x:y;
   return max;}

 };
 int main(){
    Max ob(3,2); //Max<int> ob(3,2);
    cout<< ob.find() <<endl;
    return 0;
 }