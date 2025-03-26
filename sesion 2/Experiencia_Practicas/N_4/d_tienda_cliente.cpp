#include <iostream>
#include <vector>
using namespace std;

class Producto {
public:
    string nombre;
    double precio;
    int stock;

    Producto(string _nombre, double _precio, int _stock) {
        nombre = _nombre;
        precio = _precio;
        stock = _stock;
    }

    bool reducirStock(int cantidad) {
        if (cantidad > stock) {
            return false;
        }
        stock -= cantidad;
        return true;
    }
};

class Tienda {
private:
    vector<Producto> inventario;

public:
    // Método para agregar productos al inventario
    void agregarProducto(string nombre, double precio, int stock) {
        inventario.push_back(Producto(nombre, precio, stock));
    }

    // Método para mostrar productos disponibles
    void mostrarProductos() {
        cout << "Productos disponibles en la tienda:\n";
        for (size_t i = 0; i < inventario.size(); i++) {
            cout << i + 1 << ". " << inventario[i].nombre << " - $" << inventario[i].precio 
                << " (" << inventario[i].stock << " disponibles)\n";
        }
    }

    // Método para vender productos a un cliente
    bool venderProducto(int indice, int cantidad) {
        if (indice < 0 || indice >= inventario.size()) {
            cout << "Producto no valido.\n";
            return false;
        }

        if (inventario[indice].reducirStock(cantidad)) {
            return true;
        } else {
            cout << "No hay suficiente stock de " << inventario[indice].nombre << ".\n";
            return false;
        }
    }

    // Método para obtener información de un producto (para Cliente)
    Producto obtenerProducto(int indice) {
        return inventario[indice];
    }
};

class Cliente {
private:
    string nombre;
    vector<pair<Producto, int>> carrito;
    double total;

public:
    Cliente(string _nombre) {
        nombre = _nombre;
        total = 0.0;
    }

    // Método para agregar productos al carrito
    void agregarAlCarrito(Tienda &tienda, int indice, int cantidad) {
        if (tienda.venderProducto(indice, cantidad)) {
            Producto p = tienda.obtenerProducto(indice);
            carrito.push_back({p, cantidad});
            total += p.precio * cantidad;
            cout << cantidad << " unidad(es) de " << p.nombre << " agregadas al carrito.\n";
        }
    }

    // Método para pagar
    void pagar() {
        cout << nombre << " ha pagado un total de $" << total << ".\n";
        carrito.clear();
        total = 0;
    }
};

int main() {
    // Crear una tienda
    Tienda miTienda;
    miTienda.agregarProducto("Laptop", 1200, 5);
    miTienda.agregarProducto("Telefono", 800, 10);
    miTienda.agregarProducto("Audifonos", 50, 20);

    // Mostrar los productos de la tienda
    miTienda.mostrarProductos();

    // Crear un cliente
    Cliente cliente1("Juan");

    // El cliente agrega productos a su carrito
    cliente1.agregarAlCarrito(miTienda, 0, 1);  // Comprar 1 Laptop
    cliente1.agregarAlCarrito(miTienda, 2, 3);  // Comprar 3 Audifonos

    // El cliente paga
    cliente1.pagar();

    return 0;
}
