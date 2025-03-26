#include <iostream>
#include <vector>
using namespace std;

class Producto {
private:
    string nombre;
    double precio;
    int cantidad;

public:
    // Constructor
    Producto(string _nombre, double _precio, int _cantidad) {
        nombre = _nombre;
        setPrecio(_precio);
        setCantidad(_cantidad);
    }

    // Getters
    string getNombre() {
        return nombre;
    }

    double getPrecio() {
        return precio;
    }

    int getCantidad() {
        return cantidad;
    }

    // Setters con validaciones
    void setPrecio(double _precio) {
        if (_precio > 0) {
            precio = _precio;
        } else {
            cout << "El precio del producto no puede ser negativo. Se asignara 0 por defecto." << endl;
            precio = 0;
        }
    }

    void setCantidad(int _cantidad) {
        if (_cantidad >= 0) {
            cantidad = _cantidad;
        } else {
            cout << "La cantidad del producto no puede ser negativa. Se asignara 0 por defecto." << endl;
            cantidad = 0;
        }
    }
};

class Factura {
private:
    vector<Producto> productos;

public:
    // Método para agregar un producto a la factura
    void agregarProducto(Producto producto) {
        if (producto.getCantidad() > 0) {
            productos.push_back(producto);
            cout << "Producto \"" << producto.getNombre() << "\" agregado a la factura." << endl;
        } else {
            cout << "No se puede agregar el producto \"" << producto.getNombre() << "\" porque no hay unidades disponibles." << endl;
        }
    }

    // Método para mostrar la factura
    void mostrarFactura() {
        cout << "\n*** Factura ***" << endl;
        if (productos.empty()) {
            cout << "No hay productos en la factura." << endl;
            return;
        }

        double total = 0;
        for (Producto p : productos) {
            cout << "- " << p.getNombre() << " | Precio: $" << p.getPrecio() 
                 << " | Cantidad: " << p.getCantidad() 
                 << " | Subtotal: $" << (p.getPrecio() * p.getCantidad()) << endl;
            total += p.getPrecio() * p.getCantidad();
        }
        cout << "Total a pagar: $" << total << endl;
    }
};

int main() {
    // Crear productos
    Producto producto1("Laptop", 1200, 1);
    Producto producto2("Mouse", 25, 2);
    Producto producto3("Monitor", -200, 1); // Intento con precio negativo
    Producto producto4("Teclado", 40, -5);  // Intento con cantidad negativa

    // Crear factura
    Factura factura;

    // Agregar productos a la factura
    factura.agregarProducto(producto1);
    factura.agregarProducto(producto2);
    factura.agregarProducto(producto3); // No se agregará
    factura.agregarProducto(producto4); // No se agregará

    // Mostrar la factura
    factura.mostrarFactura();

    return 0;
}
