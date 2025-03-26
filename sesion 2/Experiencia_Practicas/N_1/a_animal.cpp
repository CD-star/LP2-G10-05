#include <iostream>
using namespace std;

class Animal {
private:
    string _nombre;
    int _edad;
    string _tipo;

public:
    // Constructor
    Animal(string nombre, int edad, string tipo) {
        _nombre = nombre;
        _edad = edad;
        _tipo = tipo;
    }

    // Metodo para alimentar
    void alimentar() {
        cout << _nombre << " esta comiendo." << endl;
    }

    // Metodo para hacer sonido
    void hacerSonido() {
        cout << _nombre << " hace un sonido caracteristico." << endl;
    }

    // Metodos de acceso (getters)
    string getNombre() {
        return _nombre;
    }

    int getEdad() {
        return _edad;
    }

    string getTipo() {
        return _tipo;
    }
};

int main() {
    // Crear un objeto de la clase Animal
    Animal animal1("Toby", 3, "Perro");

    // Probar los metodos
    cout << "Nombre: " << animal1.getNombre() << endl;
    cout << "Edad: " << animal1.getEdad() << " edad" << endl;
    cout << "Tipo: " << animal1.getTipo() << endl;

    animal1.alimentar();
    animal1.hacerSonido();

    return 0;
}
