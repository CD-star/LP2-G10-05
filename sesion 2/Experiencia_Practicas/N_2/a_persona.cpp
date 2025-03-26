#include <iostream>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;
    string dni;

public:
    // Constructor
    Persona(string _nombre, int _edad, string _dni) {
        nombre = _nombre;
        edad = _edad;
        dni = _dni;
    }

    // Métodos Getters y Setters
    void setNombre(string _nombre) {
        nombre = _nombre;
    }

    string getNombre() {
        return nombre;
    }

    void setEdad(int _edad) {
        if (_edad > 0) { // Validación
            edad = _edad;
        } else {
            cout << "Edad inválida." << endl;
        }
    }

    int getEdad() {
        return edad;
    }

    void setDNI(string _dni) {
        dni = _dni;
    }

    string getDNI() {
        return dni;
    }

    // Método para mostrar la información de la persona
    void mostrarInfo() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << ", DNI: " << dni << endl;
    }
};

int main() {
    // Crear objetos de la clase Persona
    Persona p1("Juan Perez", 30, "12345678A");
    Persona p2("Maria Gomez", 25, "87654321B");

    // Mostrar información inicial
    cout << "Informacion inicial:" << endl;
    p1.mostrarInfo();
    p2.mostrarInfo();

    // Modificar valores con los métodos set
    p1.setNombre("Carlos Lopez");
    p1.setEdad(35);
    p1.setDNI("11122233C");

    cout << "\nDespues de modificar los datos de p1:" << endl;
    p1.mostrarInfo();

    return 0;
}
