#include <iostream>
using namespace std;

class Calculadora{
    public:
        int sumar(int a, int b){
            return a+b;
        }
        double sumar(double a, double b){
            return a+b;
        }
        int sumar(int a, int b, int c){
            return a+b+c;
        }
};

int main()
{
    Calculadora cal;
    cout<<cal.sumar(5,6)<<endl;
    cout<<cal.sumar(3.2,5.3)<<endl;
    cout<<cal.sumar(7,3,9)<<endl;

    return 0;
}