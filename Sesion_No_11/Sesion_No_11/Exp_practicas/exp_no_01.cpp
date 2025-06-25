#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Clase Producto
class Producto {
private:
    string nombre;
    double precio;
    int cantidad;

public:
    Producto(string n, double p, int c) : nombre(n), precio(p), cantidad(c) {}

    // Métodos de acceso
    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    // Métodos de modificación
    void setPrecio(double nuevoPrecio) { precio = nuevoPrecio; }
    void setCantidad(int nuevaCantidad) { cantidad = nuevaCantidad; }

    void mostrar() const {
        cout << "Nombre: " << nombre
            << " | Precio: S/" << precio
            << " | Cantidad: " << cantidad << endl;
    }
};

// Función para registrar un nuevo producto
void registrarProducto(vector<Producto>& inventario) {
    string nombre;
    double precio;
    int cantidad;

    cout << "Ingrese nombre del producto: ";
    cin.ignore(); // Limpiar buffer
    getline(cin, nombre);
    cout << "Ingrese precio: ";
    cin >> precio;
    cout << "Ingrese cantidad: ";
    cin >> cantidad;

    Producto nuevo(nombre, precio, cantidad);
    inventario.push_back(nuevo);

    cout << "Producto registrado con exito.\n";
}

// Función para actualizar un producto
void actualizarProducto(vector<Producto>& inventario) {
    string nombre;
    cout << "Ingrese nombre del producto a actualizar: ";
    cin.ignore();
    getline(cin, nombre);

    for (auto& producto : inventario) {
        if (producto.getNombre() == nombre) {
            double nuevoPrecio;
            int nuevaCantidad;
            cout << "Nuevo precio: ";
            cin >> nuevoPrecio;
            cout << "Nueva cantidad: ";
            cin >> nuevaCantidad;

            producto.setPrecio(nuevoPrecio);
            producto.setCantidad(nuevaCantidad);

            cout << "Producto actualizado.\n";
            return;
        }
    }

    cout << "Producto no encontrado.\n";
}

// Función para realizar una venta
void venderProducto(vector<Producto>& inventario) {
    string nombre;
    int cantidadVenta;

    cout << "Ingrese nombre del producto a vender: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese cantidad a vender: ";
    cin >> cantidadVenta;

    for (auto& producto : inventario) {
        if (producto.getNombre() == nombre) {
            if (producto.getCantidad() >= cantidadVenta) {
                producto.setCantidad(producto.getCantidad() - cantidadVenta);
                cout << "Venta realizada con exito.\n";
            } else {
                cout << "Cantidad insuficiente para la venta.\n";
            }
            return;
        }
    }

    cout << "Producto no encontrado.\n";
}

// Función para generar informe
void generarInforme(const vector<Producto>& inventario) {
    cout << "\n--- INFORME DE INVENTARIO ---\n";
    for (const auto& producto : inventario) {
        producto.mostrar();
    }
}

// Menú principal
int main() {
    vector<Producto> inventario;
    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Registrar producto\n";
        cout << "2. Actualizar producto\n";
        cout << "3. Vender producto\n";
        cout << "4. Generar informe\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarProducto(inventario); break;
            case 2: actualizarProducto(inventario); break;
            case 3: venderProducto(inventario); break;
            case 4: generarInforme(inventario); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 5);

    return 0;
}
