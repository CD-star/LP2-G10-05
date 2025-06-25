#include <iostream>
#include <fstream>
#include <map>
#include <cstring>  // para strncpy
#include <iomanip>

using namespace std;

const string ARCHIVO = "inventario.dat";
const int MAX_NOMBRE = 30;

class Producto {
private:
    char nombre[MAX_NOMBRE];  // tamaño fijo
    double precio;
    int cantidad;

public:
    Producto() {
        strcpy(nombre, "");
        precio = 0.0;
        cantidad = 0;
    }

    Producto(string n, double p, int c) {
        strncpy(nombre, n.c_str(), MAX_NOMBRE);
        nombre[MAX_NOMBRE - 1] = '\0';
        precio = p;
        cantidad = c;
    }

    string getNombre() const { return string(nombre); }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    void setPrecio(double p) { precio = p; }
    void setCantidad(int c) { cantidad = c; }

    void mostrar() const {
        cout << left << setw(30) << nombre
             << " | S/" << setw(7) << precio
             << " | Cantidad: " << cantidad << endl;
    }
};

// Crear índice: nombre → posición en archivo
map<string, int> crearIndice() {
    map<string, int> indice;
    ifstream archivo(ARCHIVO, ios::binary);
    if (!archivo) return indice;

    Producto prod;
    int pos = 0;
    while (archivo.read(reinterpret_cast<char*>(&prod), sizeof(Producto))) {
        indice[prod.getNombre()] = pos++;
    }
    return indice;
}

void guardarProductoBinario(const Producto& p) {
    ofstream archivo(ARCHIVO, ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
}

void registrarProducto() {
    string nombre;
    double precio;
    int cantidad;

    cout << "Nombre: "; cin >> nombre;
    cout << "Precio: "; cin >> precio;
    cout << "Cantidad: "; cin >> cantidad;

    Producto nuevo(nombre, precio, cantidad);
    guardarProductoBinario(nuevo);

    cout << "Producto registrado.\n";
}

void buscarProductoPorNombre(const map<string, int>& indice) {
    string nombre;
    cout << "Nombre a buscar: "; cin >> nombre;

    auto it = indice.find(nombre);
    if (it != indice.end()) {
        ifstream archivo(ARCHIVO, ios::binary);
        archivo.seekg(it->second * sizeof(Producto));
        Producto p;
        archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto));
        cout << "Producto encontrado:\n";
        p.mostrar();
    } else {
        cout << "Producto no encontrado.\n";
    }
}

void actualizarCantidadPorNombre(map<string, int>& indice) {
    string nombre;
    int nuevaCantidad;

    cout << "Producto a actualizar: "; cin >> nombre;
    auto it = indice.find(nombre);
    if (it != indice.end()) {
        fstream archivo(ARCHIVO, ios::in | ios::out | ios::binary);
        archivo.seekg(it->second * sizeof(Producto));
        Producto p;
        archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto));

        cout << "Cantidad actual: " << p.getCantidad() << "\n";
        cout << "Nueva cantidad: "; cin >> nuevaCantidad;
        p.setCantidad(nuevaCantidad);

        archivo.seekp(it->second * sizeof(Producto));
        archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

        cout << "Producto actualizado.\n";
    } else {
        cout << "Producto no encontrado.\n";
    }
}

void informeCompleto() {
    ifstream archivo(ARCHIVO, ios::binary);
    Producto p;
    cout << "\n--- INFORME COMPLETO ---\n";
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        p.mostrar();
    }
}

int main() {
    int opcion;
    map<string, int> indice = crearIndice();

    do {
        cout << "\n1. Registrar producto\n2. Buscar por nombre\n3. Actualizar cantidad\n4. Generar informe\n5. Salir\nOpción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarProducto(); indice = crearIndice(); break;
            case 2: buscarProductoPorNombre(indice); break;
            case 3: actualizarCantidadPorNombre(indice); break;
            case 4: informeCompleto(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 5);

    return 0;
}