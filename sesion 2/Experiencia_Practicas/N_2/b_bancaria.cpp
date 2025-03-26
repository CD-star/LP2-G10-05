#include <iostream>
using namespace std;

class CuentaBancaria {
public:
    string titular;
    double saldo;

    // Constructor
    CuentaBancaria(string _titular, double _saldo) {
        titular = _titular;
        saldo = (_saldo >= 0) ? _saldo : 0; // Evitar saldo negativo al iniciar
        if (_saldo < 0) {
            cout << "Saldo inicial invalido. Se asignara 0." << endl;
        }
    }

    // Metodo publico para mostrar informacion
    void mostrarInfo() {
        cout << "Titular: " << titular << ", Saldo: " << saldo << endl;
    }

    // Metodos publicos para operar con la cuenta
    void depositar(double monto) {
        _depositar(monto);
    }

    void retirar(double monto) {
        _retirar(monto);
    }

private:
    // Metodo privado para realizar depositos
    void _depositar(double monto) {
        if (monto > 0) {
            saldo += monto;
            cout << "Deposito exitoso. Nuevo saldo: " << saldo << endl;
        } else {
            cout << "El monto a depositar debe ser positivo." << endl;
        }
    }

    // Metodo privado para realizar retiros
    void _retirar(double monto) {
        if (monto > 0) {
            if (monto <= saldo) {
                saldo -= monto;
                cout << "Retiro exitoso. Nuevo saldo: " << saldo << endl;
            } else {
                cout << "Fondos insuficientes. Saldo actual: " << saldo << endl;
            }
        } else {
            cout << "El monto a retirar debe ser positivo." << endl;
        }
    }
};

int main() {
    // Crear una cuenta bancaria con saldo inicial valido
    CuentaBancaria cuenta1("Juan Perez", 500);

    // Mostrar informacion inicial
    cuenta1.mostrarInfo();

    // Intentar depositar y retirar dinero
    cuenta1.depositar(200);
    cuenta1.retirar(100);
    cuenta1.retirar(700); // Intento de retiro mayor al saldo disponible
    cuenta1.retirar(-50); // Intento de retiro con monto negativo

    return 0;
}

