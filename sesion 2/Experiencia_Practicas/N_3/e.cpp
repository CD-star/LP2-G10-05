#include <iostream>
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

    // Getters
    string getNombre() { return _nombre; }
    string getDireccion() { return _direccion; }
    string getTipoDeTienda() { return _tipoDeTienda; }
    int getStock() { return _stock; }

    // Setters
    void setNombre(string nombre) { _nombre = nombre; }
    void setDireccion(string direccion) { _direccion = direccion; }
    void setTipoDeTienda(string tipo) { _tipoDeTienda = tipo; }
    void setStock(int stock) { _stock = stock; }

    // Metodo para mostrar informacion
    void mostrarInformacion() {
        cout << "Tienda: " << _nombre << " | Direccion: " << _direccion << " | Tipo: " << _tipoDeTienda << " | Stock: " << _stock << endl;
    }
};

int main() {
    // Crear objetos
    Tienda tienda1("Moda Express", "Av. Central 123", "Ropa", 10);
    Tienda tienda2("TecnoShop", "Calle Principal 456", "Electronicos", 5);

    // Usar getters para mostrar datos iniciales
    cout << "Nombre de la primera tienda: " << tienda1.getNombre() << endl;
    cout << "Stock de la segunda tienda: " << tienda2.getStock() << endl;

    // Modificar valores con setters
    tienda1.setStock(20);
    tienda2.setDireccion("Av. Nueva 789");

    // Mostrar cambios
    tienda1.mostrarInformacion();
    tienda2.mostrarInformacion();

    return 0;
}