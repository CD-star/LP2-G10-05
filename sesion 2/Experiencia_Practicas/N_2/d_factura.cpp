#include <iostream>
using namespace std;

class Factura {
private:
    int numero;
    string cliente;
    double monto;

public:
    // Constructor
    Factura(int _numero, string _cliente, double _monto) {
        numero = _numero;
        cliente = _cliente;
        monto = (_monto >= 0) ? _monto : 0; // Evitar montos negativos
        if (_monto < 0) {
            cout << "Monto invalido. Se asignara 0." << endl;
        }
    }

    // Getters
    int getNumero() {
        return numero;
    }

    string getCliente() {
        return cliente;
    }

    double getMonto() {
        return monto;
    }

    // Setters
    void setNumero(int _numero) {
        numero = _numero;
    }

    void setCliente(string _cliente) {
        cliente = _cliente;
    }

    void setMonto(double _monto) {
        if (_monto >= 0) {
            monto = _monto;
        } else {
            cout << "El monto no puede ser negativo." << endl;
        }
    }

    // Metodo para mostrar la informacion de la factura
    void mostrarFactura() {
        cout << "Factura #" << numero << " - Cliente: " << cliente << " - Monto: $" << monto << endl;
    }
};

int main() {
    // Crear facturas con diferentes valores
    Factura factura1(101, "Carlos Gomez", 250.75);
    Factura factura2(102, "Maria Torres", -500); // Intento de monto negativo

    // Mostrar las facturas
    factura1.mostrarFactura();
    factura2.mostrarFactura();

    // Modificar datos de una factura y mostrar nuevamente
    factura2.setMonto(450.30);
    cout << "Despues de modificar el monto de la factura 2:" << endl;
    factura2.mostrarFactura();

    return 0;
}
