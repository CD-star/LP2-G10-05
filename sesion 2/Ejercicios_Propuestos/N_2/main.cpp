#include <iostream>
#include <vector>
using namespace std;

class Producto {
private:
    string _nombre;
    int _cantidad;
    double _precio;

public:
    // Constructor
    Producto(string nombre, int cantidad, double precio) {
        _nombre = nombre;
        _cantidad = cantidad;
        _precio = precio;
    }

    // Métodos para obtener valores
    string getNombre() { return _nombre; }
    int getCantidad() { return _cantidad; }
    double getPrecio() { return _precio; }

    // Método para reducir la cantidad en stock
    void reducirCantidad(int cantidad) {
        _cantidad = (_cantidad >= cantidad) ? _cantidad - cantidad : 0;
    }

    // Método para verificar si está agotado
    bool estaAgotado() { return _cantidad == 0; }
};

class Factura {
private:
    string _cliente;
    vector<string> _productos;
    vector<int> _cantidades;
    double _total;

public:
    // Constructor
    Factura(string cliente) {
        _cliente = cliente;
        _total = 0.0;
    }

    // Agregar un producto a la factura
    void agregarProducto(string producto, int cantidad, double precio) {
        _productos.push_back(producto);
        _cantidades.push_back(cantidad);
        _total += cantidad * precio;
    }

    // Mostrar factura
    void mostrarFactura() {
        cout << "Factura - Cliente: " << _cliente << endl;
        for (size_t i = 0; i < _productos.size(); i++) {
            cout << "  " << _productos[i] << " - Cantidad: " << _cantidades[i] << endl;
        }
        cout << "Total: $" << _total << endl;
    }
};

class Inventario {
private:
    vector<Producto> _productosDisponibles;
    vector<Producto> _productosAgotados;
    vector<Factura> _facturas;

public:
    // Agregar un producto al inventario
    void agregarProducto(string nombre, int cantidad, double precio) {
        _productosDisponibles.push_back(Producto(nombre, cantidad, precio));
        cout << "Producto agregado: " << nombre << " (Cantidad: " << cantidad << ", Precio: $" << precio << ")" << endl;
    }

    // Actualizar el inventario (mueve productos agotados a la lista correspondiente)
    void actualizarInventario() {
        vector<Producto> productosRestantes;
        for (Producto& producto : _productosDisponibles) {
            if (producto.estaAgotado()) {
                _productosAgotados.push_back(producto);
            } else {
                productosRestantes.push_back(producto);
            }
        }
        _productosDisponibles = productosRestantes;
    }

    // Realizar un pedido con múltiples productos
    void realizarPedido(string cliente, vector<pair<string, int>> pedidos) {
        Factura nuevaFactura(cliente);

        for (auto& pedido : pedidos) {
            string nombreProducto = pedido.first;
            int cantidad = pedido.second;
            bool productoEncontrado = false;

            for (Producto& producto : _productosDisponibles) {
                if (producto.getNombre() == nombreProducto) {
                    productoEncontrado = true;
                    if (producto.getCantidad() >= cantidad) {
                        producto.reducirCantidad(cantidad);
                        nuevaFactura.agregarProducto(nombreProducto, cantidad, producto.getPrecio());
                        cout << cliente << " compro " << cantidad << " de " << nombreProducto << "." << endl;
                    } else {
                        cout << "Stock insuficiente para " << nombreProducto << "." << endl;
                    }
                    break;
                }
            }
            if (!productoEncontrado) {
                cout << "Producto " << nombreProducto << " no encontrado en inventario." << endl;
            }
        }

        actualizarInventario();
        _facturas.push_back(nuevaFactura);
    }

    // Mostrar todas las facturas
    void mostrarFacturas() {
        cout << "\nFacturas generadas:" << endl;
        for (Factura& factura : _facturas) {
            factura.mostrarFactura();
            cout << "-----------------------------" << endl;
        }
    }
};

int main() {
    Inventario tienda;

    // Agregar productos al inventario
    tienda.agregarProducto("Laptop", 5, 1200.00);
    tienda.agregarProducto("Mouse", 10, 25.50);
    tienda.agregarProducto("Teclado", 8, 45.75);

    // Realizar un pedido con múltiples productos
    tienda.realizarPedido("Carlos", {{"Laptop", 2}, {"Mouse", 3}});
    tienda.realizarPedido("Ana", {{"Teclado", 2}, {"Mouse", 1}, {"Laptop", 1}});
    tienda.realizarPedido("Luis", {{"Teclado", 10}}); // Stock insuficiente

    // Mostrar facturas
    tienda.mostrarFacturas();

    return 0;
}
