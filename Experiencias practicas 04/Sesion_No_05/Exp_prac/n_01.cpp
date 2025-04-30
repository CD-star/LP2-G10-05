#include <iostream>
using namespace std;

class CuentaBancaria {
private:
    string numero;
    string titular;
    double saldo;

public:
    // Constructor
    CuentaBancaria(string num, string tit, double sal = 0.0) {
        numero = num;
        titular = tit;
        saldo = sal;
        cout << "Cuenta creada para " << titular << endl;
    }

    // Destructor
    ~CuentaBancaria() {
        cout << "Cuenta de " << titular << " eliminada." << endl;
    }

    // Método para depositar dinero (retorna *this para encadenamiento)
    CuentaBancaria& depositar(double monto) {
        saldo += monto;
        return *this;
    }

    // Método para retirar dinero (retorna *this para encadenamiento)
    CuentaBancaria& retirar(double monto) {
        if (monto <= saldo) {
            saldo -= monto;
        } else {
            cout << "Saldo insuficiente." << endl;
        }
        return *this;
    }

    // Método para mostrar el saldo
    CuentaBancaria& mostrarSaldo() {
        cout << "Saldo actual: " << saldo << " soles" << endl;
        return *this;
    }
};

// Función principal para probar la clase
int main() {
    CuentaBancaria cuenta("123456", "Joaquín", 500);
    cuenta.depositar(1000).retirar(200).mostrarSaldo();

    return 0;
}