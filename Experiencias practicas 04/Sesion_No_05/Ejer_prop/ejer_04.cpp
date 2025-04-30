#include <iostream>
using namespace std;

class Gerente {
public:
    Gerente() {
        cout << "Constructor de Gerente" << endl;
    }
    ~Gerente() {
        cout << "Destructor de Gerente" << endl;
    }
};

class Direccion {
public:
    Direccion() {
        cout << "Constructor de Direccion" << endl;
    }
    ~Direccion() {
        cout << "Destructor de Direccion" << endl;
    }
};

class Empresa {
private:
    Gerente g;
    Direccion d;
public:
    Empresa() : g(), d() {
        cout << "Constructor de Empresa" << endl;
    }
    ~Empresa() {
        cout << "Destructor de Empresa" << endl;
    }
};

int main() {
    Empresa e;
    return 0;
}