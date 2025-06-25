#include <iostream>
#include <fstream>
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
    Producto() {}
    Producto(string n, double p, int c) : nombre(n), precio(p), cantidad(c) {}

    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    void setPrecio(double nuevoPrecio) { precio = nuevoPrecio; }
    void setCantidad(int nuevaCantidad) { cantidad = nuevaCantidad; }

    void mostrar() const {
        cout << "Nombre: " << nombre
            << " | Precio: S/" << precio
            << " | Cantidad: " << cantidad << endl;
    }

    string toCSV() const {
        return nombre + "," + to_string(precio) + "," + to_string(cantidad);
    }

    static Producto fromCSV(const string& linea) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.rfind(',');
        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2)
            throw runtime_error("Formato de linea invalido");

        string n = linea.substr(0, pos1);
        double p = stod(linea.substr(pos1 + 1, pos2 - pos1 - 1));
        int c = stoi(linea.substr(pos2 + 1));

        return Producto(n, p, c);
    }
};

// Leer todos los productos desde el archivo
vector<Producto> leerInventario(const string& archivo) {
    vector<Producto> inventario;
    ifstream file(archivo);
    string linea;

    while (getline(file, linea)) {
        try {
            inventario.push_back(Producto::fromCSV(linea));
        } catch (...) {
            // Ignora lineas mal formateadas
        }
    }

    return inventario;
}

// Guardar todo el inventario en el archivo
void guardarInventario(const string& archivo, const vector<Producto>& inventario) {
    ofstream file(archivo);
    for (const auto& p : inventario)
        file << p.toCSV() << endl;
}

// Buscar posición del producto por nombre
int buscarProducto(const vector<Producto>& inventario, const string& nombre) {
    for (int i = 0; i < int(inventario.size()); ++i) {
        if (inventario[i].getNombre() == nombre)            return i;
    }
    return -1;
}

void registrarProducto(const string& archivo) {
    string nombre;
    double precio;
    int cantidad;

    cin.ignore();
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Precio: "; cin >> precio;
    cout << "Cantidad: "; cin >> cantidad;

    Producto nuevo(nombre, precio, cantidad);
    ofstream file(archivo, ios::app); // Modo agregar
    file << nuevo.toCSV() << endl;

    cout << "Producto agregado al inventario.\n";
}

void actualizarProducto(const string& archivo) {
    vector<Producto> inventario = leerInventario(archivo);

    string nombre;
    cin.ignore();
    cout << "Producto a actualizar: "; getline(cin, nombre);

    int pos = buscarProducto(inventario, nombre);
    if (pos != -1) {
        double nuevoPrecio;
        int nuevaCantidad;

        cout << "Nuevo precio: "; cin >> nuevoPrecio;
        cout << "Nueva cantidad: "; cin >> nuevaCantidad;

        inventario[pos].setPrecio(nuevoPrecio);
        inventario[pos].setCantidad(nuevaCantidad);

        guardarInventario(archivo, inventario);
        cout << "Producto actualizado.\n";
    } else {
        cout << "Producto no encontrado.\n";
    }
}

void venderProducto(const string& archivo) {
    vector<Producto> inventario = leerInventario(archivo);

    string nombre;
    int cantidadVenta;
    cin.ignore();
    cout << "Producto a vender: "; getline(cin, nombre);
    cout << "Cantidad: "; cin >> cantidadVenta;

    int pos = buscarProducto(inventario, nombre);
    if (pos != -1) {
        if (inventario[pos].getCantidad() >= cantidadVenta) {
            inventario[pos].setCantidad(inventario[pos].getCantidad() - cantidadVenta);
            guardarInventario(archivo, inventario);
            cout << "Venta realizada.\n";
        } else {
            cout << "Cantidad insuficiente para la venta.\n";
        }
    } else {
        cout << "Producto no encontrado.\n";
    }
}

void generarInforme(const string& archivo) {
    vector<Producto> inventario = leerInventario(archivo);
    cout << "\n--- INFORME DE INVENTARIO ---\n";
    for (const auto& p : inventario)
        p.mostrar();
}

int main() {
    const string archivo = "inventario.txt";
    int opcion;

    do {
        cout << "\n1. Registrar producto\n2. Actualizar producto\n3. Vender producto\n4. Generar informe\n5. Salir\nOpcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida.\n";
            continue;
        }
        cin.ignore(); // Limpiar salto de linea
        switch (opcion) {
            case 1: registrarProducto(archivo); break;
            case 2: actualizarProducto(archivo); break;
            case 3: venderProducto(archivo); break;
            case 4: generarInforme(archivo); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);

    return 0;
}