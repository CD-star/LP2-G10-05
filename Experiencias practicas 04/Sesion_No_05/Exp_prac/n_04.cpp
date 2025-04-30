#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "Constructor de A" << endl;
    }
    ~A() {
        cout << "Destructor de A" << endl;
    }
};

class B {
private:
    A a;  // Composición: B contiene un objeto A

public:
    B() {
        cout << "Constructor de B" << endl;
    }
    ~B() {
        cout << "Destructor de B" << endl;
    }
};

int main() {
    cout << "Creando objeto B..." << endl;
    B obj;
    cout << "Fin del main()" << endl;
    return 0;
}