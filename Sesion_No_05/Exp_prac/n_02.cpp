#include <iostream>
using namespace std;

class Dispositivo {
private:
    string marca;
    string modelo;
    int anioFabricacion;

public:
    // Constructor predeterminado
    Dispositivo() {
        marca = "Desconocida";
        modelo = "Genérico";
        anioFabricacion = 0;
        cout << "Constructor predeterminado llamado." << endl;
    }

    // Constructor parametrizado
    Dispositivo(string m, string mo, int anio) {
        marca = m;
        modelo = mo;
        anioFabricacion = anio;
        cout << "Constructor parametrizado llamado: " << modelo << endl;
    }

    // Constructor de copia
    Dispositivo(const Dispositivo& otro) {
        marca = otro.marca;
        modelo = otro.modelo;
        anioFabricacion = otro.anioFabricacion;
        cout << "Constructor de copia llamado para: " << modelo << endl;
    }

    // Destructor
    ~Dispositivo() {
        cout << "Destructor llamado para el modelo: " << modelo << endl;
    }
};

// Función principal
int main() {
    // Crear arreglo de objetos Dispositivo
    Dispositivo dispositivos[3] = {
        Dispositivo("Apple", "iPhone 14", 2022),
        Dispositivo("Samsung", "Galaxy S22", 2022),
        Dispositivo("Xiaomi", "Redmi Note 12", 2023)
    };

    return 0;
}