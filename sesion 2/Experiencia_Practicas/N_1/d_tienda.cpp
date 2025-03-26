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

    // Metodo para vender un producto
    void venderProducto() {
        if (_stock > 0) {
            _stock--;
            cout << "Producto vendido en " << _nombre << ". Stock restante: " << _stock << endl;
        } else {
            cout << "No hay stock disponible en " << _nombre << "." << endl;
        }
    }

    // Metodo para agregar productos al stock
    void agregarProducto(int cantidad) {
        _stock += cantidad;
        cout << "Se han agregado " << cantidad << " productos a " << _nombre << ". Stock actual: " << _stock << endl;
    }

    // Metodo para obtener informacion de la tienda
    void mostrarInformacion() {
        cout << "Tienda: " << _nombre << " | Direccion: " << _direccion << " | Tipo: " << _tipoDeTienda << " | Stock: " << _stock << endl;
    }
};

int main() {
    // Crear objetos de la clase Tienda
    Tienda tiendaRopa("Moda Express", "Av. Central 123", "Ropa", 10);
    Tienda tiendaElectronicos("TecnoShop", "Calle Principal 456", "Electronicos", 5);

    // Mostrar informacion inicial
    tiendaRopa.mostrarInformacion();
    tiendaElectronicos.mostrarInformacion();

    // Probar metodos
    tiendaRopa.venderProducto();
    tiendaElectronicos.venderProducto();
    
    tiendaRopa.agregarProducto(5);
    tiendaElectronicos.agregarProducto(3);

    return 0;
}
