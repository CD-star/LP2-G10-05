#include <iostream>
using namespace std;

class Producto {
private:
    string nombre;
    double precio;
    double descuento;

public:
    Producto() : nombre(""), precio(0), descuento(0) {}

    Producto& setNombre(string n) {
        nombre = n;
        return *this;
    }

    Producto& setPrecio(double p) {
        precio = p;
        return *this;
    }

    Producto& setDescuento(double d) {
        descuento = d;
        return *this;
    }

    double calcularPrecioFinal() const {
        return precio - (precio * descuento / 100);
    }

    void mostrar() const {
        cout << nombre << ": S/. " << calcularPrecioFinal() << endl;
    }
};

int main() {
    Producto productos[3];
    productos[0].setNombre("Laptop").setPrecio(3000).setDescuento(10);
    productos[1].setNombre("Mouse").setPrecio(100).setDescuento(5);
    productos[2].setNombre("Monitor").setPrecio(800).setDescuento(15);

    double total = 0;
    for (int i = 0; i < 3; ++i) {
        productos[i].mostrar();
        total += productos[i].calcularPrecioFinal();
    }

    cout << "Total acumulado: S/. " << total << endl;
    return 0;
}