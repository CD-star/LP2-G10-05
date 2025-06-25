#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class Producto {
private:
    string nombre;
    double precio;
    int cantidad;

public:
    Producto() {}
    Producto(string n, double p, int c) {
        if (p < 0 || c < 0) throw invalid_argument("Precio o cantidad no pueden ser negativos");
        nombre = n;
        precio = p;
        cantidad = c;
    }

    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    void setPrecio(double p) {
        if (p < 0) throw invalid_argument("Precio inválido");
        precio = p;
    }

    void setCantidad(int c) {
        if (c < 0) throw invalid_argument("Cantidad inválida");
        cantidad = c;
    }

    void mostrar() const {
        cout << "Nombre: " << nombre << " | Precio: S/" << precio << " | Cantidad: " << cantidad << endl;
    }

    string toCSV() const {
        return nombre + "," + to_string(precio) + "," + to_string(cantidad);
    }

    static Producto fromCSV(const string& linea) {
        size_t p1 = linea.find(',');
        size_t p2 = linea.rfind(',');
        if (p1 == string::npos || p2 == string::npos || p1 == p2)
            throw runtime_error("Formato de línea inválido");

        string nombre = linea.substr(0, p1);
        double precio = stod(linea.substr(p1 + 1, p2 - p1 - 1));
        int cantidad = stoi(linea.substr(p2 + 1));

        return Producto(nombre, precio, cantidad);
    }
};

vector<Producto> leerInventario(const string& archivo) {
    ifstream file(archivo);
    if (!file) throw runtime_error("No se pudo abrir el archivo para lectura.");

    vector<Producto> inventario;
    string linea;
    while (getline(file, linea)) {
        try {
            inventario.push_back(Producto::fromCSV(linea));
        } catch (...) {
            cerr << "Línea ignorada por mal formato.\n";
        }
    }
    return inventario;
}

void guardarInventario(const string& archivo, const vector<Producto>& inventario) {
    ofstream file(archivo);
    if (!file) throw runtime_error("No se pudo abrir el archivo para escritura.");

    for (const auto& p : inventario)
        file << p.toCSV() << endl;
}

int buscarProducto(const vector<Producto>& inventario, const string& nombre) {
    for (int i = 0; i < int(inventario.size()); ++i)
        if (inventario[i].getNombre() == nombre)
            return i;
    throw runtime_error("Producto no encontrado.");
}

void registrarProducto(vector<Producto>& inventario) {
    string nombre;
    double precio;
    int cantidad;

    cout << "Nombre: ";
    cin >> nombre;

    cout << "Precio: ";
    if (!(cin >> precio)) throw invalid_argument("Entrada no válida para precio.");

    cout << "Cantidad: ";
    if (!(cin >> cantidad)) throw invalid_argument("Entrada no válida para cantidad.");

    Producto nuevo(nombre, precio, cantidad);
    inventario.push_back(nuevo);

    cout << "Producto registrado correctamente.\n";
}

void venderProducto(vector<Producto>& inventario) {
    string nombre;
    int cantidad;

    cout << "Producto a vender: ";
    cin >> nombre;

    int pos = buscarProducto(inventario, nombre);

    cout << "Cantidad a vender: ";
    if (!(cin >> cantidad)) throw invalid_argument("Entrada inválida de cantidad.");

    if (cantidad <= 0) throw invalid_argument("Cantidad debe ser mayor que cero.");
    if (inventario[pos].getCantidad() < cantidad)
        throw runtime_error("No hay suficiente stock para la venta.");

    inventario[pos].setCantidad(inventario[pos].getCantidad() - cantidad);

    cout << "Venta realizada con éxito.\n";
}

void actualizarProducto(vector<Producto>& inventario) {
    string nombre;
    cout << "Producto a actualizar: ";
    cin >> nombre;

    int pos = buscarProducto(inventario, nombre);

    double nuevoPrecio;
    int nuevaCantidad;

    cout << "Nuevo precio: ";
    if (!(cin >> nuevoPrecio)) throw invalid_argument("Entrada inválida de precio.");

    cout << "Nueva cantidad: ";
    if (!(cin >> nuevaCantidad)) throw invalid_argument("Entrada inválida de cantidad.");

    inventario[pos].setPrecio(nuevoPrecio);
    inventario[pos].setCantidad(nuevaCantidad);

    cout << "Producto actualizado correctamente.\n";
}

void generarInforme(const vector<Producto>& inventario) {
    cout << "\n--- INFORME DE INVENTARIO ---\n";
    for (const auto& p : inventario)
        p.mostrar();
}

int main() {
    const string archivo = "inventario.txt";
    vector<Producto> inventario;

    try {
        inventario = leerInventario(archivo);
    } catch (const exception& e) {
        cerr << "Error al cargar inventario: " << e.what() << endl;
    }

    int opcion;
    do {
        cout << "\n1. Registrar producto\n2. Actualizar producto\n3. Vender producto\n4. Generar informe\n5. Guardar y salir\nOpcion: ";
        cin >> opcion;

        try {
            switch (opcion) {
                case 1: registrarProducto(inventario); break;
                case 2: actualizarProducto(inventario); break;
                case 3: venderProducto(inventario); break;
                case 4: generarInforme(inventario); break;
                case 5: guardarInventario(archivo, inventario); break;
                default: cout << "Opcion invalida.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear(); // limpia errores de entrada
            cin.ignore(1000, '\n'); // descarta entrada incorrecta
        }

    } while (opcion != 5);

    return 0;
}