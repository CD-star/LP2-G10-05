#include <iostream>
#include <vector>
using namespace std;

class Tienda {
private:
    string _nombre;
    string _direccion;
    string _tipoDeTienda;
    int _stock;

public:
    // Constructor
    Tienda(string nombre, string direccion, string tipoDeTienda, int stock) {
        _nombre = nombre;
        _direccion = direccion;
        _tipoDeTienda = tipoDeTienda;
        _stock = stock;
    }

    string getNombre() { return _nombre; }
    int getStock() { return _stock; }
    void setStock(int stock) { _stock = stock; }

    // Metodo para mostrar informacion
    void mostrarInformacion() {
        cout << "Tienda: " << _nombre << " | Direccion: " << _direccion << " | Tipo: " << _tipoDeTienda << " | Stock: " << _stock << endl;
    }
};

// Funcion para imprimir la lista de tiendas
void imprimirTiendas(vector<Tienda>& tiendas) {
    for (size_t i = 0; i < tiendas.size(); i++) {
        tiendas[i].mostrarInformacion();
    }
}

// Funcion para eliminar una tienda por nombre
void eliminarTienda(vector<Tienda>& tiendas, string nombre) {
    for (size_t i = 0; i < tiendas.size(); i++) {
        if (tiendas[i].getNombre() == nombre) {
            tiendas.erase(tiendas.begin() + i);
            cout << "Tienda " << nombre << " eliminada." << endl;
            return;
        }
    }
    cout << "Tienda no encontrada." << endl;
}

// Funcion para actualizar el stock de una tienda
void actualizarStock(vector<Tienda>& tiendas, string nombre, int nuevoStock) {
    for (size_t i = 0; i < tiendas.size(); i++) {
        if (tiendas[i].getNombre() == nombre) {
            tiendas[i].setStock(nuevoStock);
            cout << "Stock de " << nombre << " actualizado a " << nuevoStock << endl;
            return;
        }
    }
    cout << "Tienda no encontrada." << endl;
}

int main() {
    vector<Tienda> tiendas;

    // Agregar tiendas
    tiendas.push_back(Tienda("Moda Express", "Av. Central 123", "Ropa", 10));
    tiendas.push_back(Tienda("TecnoShop", "Calle Principal 456", "Electronicos", 5));
    tiendas.push_back(Tienda("SuperMarket", "Av. Los Olivos 789", "Alimentos", 15));

    // Mostrar lista inicial
    cout << "Lista de tiendas antes de eliminar o actualizar:" << endl;
    imprimirTiendas(tiendas);

    // Eliminar una tienda
    eliminarTienda(tiendas, "TecnoShop");

    // Actualizar el stock de una tienda
    actualizarStock(tiendas, "Moda Express", 25);

    // Mostrar lista final
    cout << "\nLista de tiendas despues de eliminar y actualizar:" << endl;
    imprimirTiendas(tiendas);

    return 0;
}
