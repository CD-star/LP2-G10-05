#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Clase base abstracta: Producto ---
class Producto {
protected:
    string nombre;
    double precio;
    int cantidad;

public:
    Producto(const string& nombre, double precio, int cantidad)
        : nombre(nombre), precio(precio), cantidad(cantidad) {}

    virtual double calcularValorTotal() const = 0;
    virtual void aplicarDescuento() = 0;
    virtual void mostrarInformacion() const = 0;

    virtual ~Producto() {}
};

// --- Clase Electronico ---
class Electronico : public Producto {
public:
    Electronico(const string& nombre, double precio, int cantidad)
        : Producto(nombre, precio, cantidad) {}

    double calcularValorTotal() const override {
        return precio * cantidad;
    }

    void aplicarDescuento() override {
        precio *= 0.9; // 10% de descuento
    }

    void mostrarInformacion() const override {
        cout << "Electronico: " << nombre << " | Precio: " << precio
            << " | Cantidad: " << cantidad << " | Total: " << calcularValorTotal() << endl;
    }
};

// --- Clase Ropa ---
class Ropa : public Producto {
public:
    Ropa(const string& nombre, double precio, int cantidad)
        : Producto(nombre, precio, cantidad) {}

    double calcularValorTotal() const override {
        return precio * cantidad;
    }

    void aplicarDescuento() override {
        precio *= 0.8; // 20% de descuento
    }

    void mostrarInformacion() const override {
        cout << "Ropa: " << nombre << " | Precio: " << precio
            << " | Cantidad: " << cantidad << " | Total: " << calcularValorTotal() << endl;
    }
};

// --- Clase Alimento ---
class Alimento : public Producto {
public:
    Alimento(const string& nombre, double precio, int cantidad)
        : Producto(nombre, precio, cantidad) {}

    double calcularValorTotal() const override {
        return precio * cantidad;
    }

    void aplicarDescuento() override {
        // No se aplica descuento por ser perecible
    }

    void mostrarInformacion() const override {
        cout << "Alimento: " << nombre << " | Precio: " << precio
            << " | Cantidad: " << cantidad << " | Total: " << calcularValorTotal() << endl;
    }
};

// --- Funcion principal ---
int main() {
    vector<Producto*> inventario;

    inventario.push_back(new Electronico("Laptop", 1200.0, 3));
    inventario.push_back(new Ropa("Camisa", 50.0, 10));
    inventario.push_back(new Alimento("Leche", 3.5, 20));

    cout << "\n--- INVENTARIO INICIAL ---\n";
    for (const auto& p : inventario) {
        p->mostrarInformacion();
    }

    // Aplicar descuentos
    for (auto& p : inventario) {
        p->aplicarDescuento();
    }

    cout << "\n--- INVENTARIO CON DESCUENTO ---\n";
    double valorTotalInventario = 0;
    for (const auto& p : inventario) {
        p->mostrarInformacion();
        valorTotalInventario += p->calcularValorTotal();
    }

    cout << "\nValor total del inventario: $" << valorTotalInventario << endl;

    // Liberar memoria
    for (auto& p : inventario) {
        delete p;
    }
    inventario.clear();

    return 0;
}
