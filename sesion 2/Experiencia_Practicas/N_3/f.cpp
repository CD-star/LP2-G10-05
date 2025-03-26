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

    // Metodo para mostrar informacion
    void mostrarInformacion() {
        cout << "Tienda: " << _nombre << " | Direccion: " << _direccion << " | Tipo: " << _tipoDeTienda << " | Stock: " << _stock << endl;
    }
};

// Funcion para recorrer e imprimir tiendas
void imprimirTiendas(vector<Tienda>& tiendas) {
    for (size_t i = 0; i < tiendas.size(); i++) {
        tiendas[i].mostrarInformacion();
    }
}

int main() {
    vector<Tienda> tiendas;

    // Agregar tiendas al arreglo
    tiendas.push_back(Tienda("Moda Express", "Av. Central 123", "Ropa", 10));
    tiendas.push_back(Tienda("TecnoShop", "Calle Principal 456", "Electronicos", 5));
    tiendas.push_back(Tienda("SuperMarket", "Av. Los Olivos 789", "Alimentos", 15));

    // Recorrer e imprimir la lista
    imprimirTiendas(tiendas);

    return 0;
}
