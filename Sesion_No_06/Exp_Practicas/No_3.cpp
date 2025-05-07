#include <iostream>
using namespace std;

// Clase Banco con tasa de interés estática
class Banco {
private:
    static double tasaInteres; // Atributo estático

public:
    // Método estático para cambiar la tasa
    static void setTasaInteres(double nuevaTasa) {
        tasaInteres = nuevaTasa;
    }

    // Método estático para obtener la tasa
    static double getTasaInteres() {
        return tasaInteres;
    }
};

// Inicialización de atributo estático
double Banco::tasaInteres = 0.03; // 3% por defecto

// Clase CuentaBancaria
class CuentaBancaria {
private:
    double saldo;

public:
    CuentaBancaria(double inicial) : saldo(inicial) {}

    void depositar(double monto) {
        if (monto > 0) {
            saldo += monto;
            cout << "Deposito de " << monto << " realizado.\n";
        } else {
            cout << "Monto invalido.\n";
        }
    }

    void retirar(double monto) {
        if (monto > 0 && monto <= saldo) {
            saldo -= monto;
            cout << "Retiro de " << monto << " realizado.\n";
        } else {
            cout << "Fondos insuficientes o monto invalido.\n";
        }
    }

    double calcularInteres() const {
        return saldo * Banco::getTasaInteres();
    }

    void mostrarSaldo() const {
        cout << "Saldo actual: " << saldo << endl;
    }
};

int main() {
    // Establecer tasa de interés del banco
    Banco::setTasaInteres(0.05); // 5%

    // Crear una cuenta con saldo inicial
    CuentaBancaria cuenta1(1000.0);

    cuenta1.mostrarSaldo();

    cuenta1.depositar(500.0);
    cuenta1.retirar(200.0);
    cuenta1.mostrarSaldo();

    // Calcular y mostrar el interés ganado
    double interes = cuenta1.calcularInteres();
    cout << "Interes ganado (con tasa del " << Banco::getTasaInteres() * 100 << "%): " << interes << endl;

    return 0;
}
