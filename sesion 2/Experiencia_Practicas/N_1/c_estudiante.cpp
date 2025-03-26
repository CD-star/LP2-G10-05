#include <iostream>
using namespace std;

class Estudiante {
private:
    string _nombre;
    int _edad;
    string _grado;
    float _ultimaNota;

public:
    // Constructor
    Estudiante(string nombre, int edad, string grado) {
        _nombre = nombre;
        _edad = edad;
        _grado = grado;
        _ultimaNota = 0.0;
    }

    // Metodo para tomar un examen
    void tomarExamen() {
        cout << _nombre << " esta tomando un examen..." << endl;
    }

    // Metodo para recibir calificacion
    void recibirCalificacion(float nota) {
        _ultimaNota = nota;
        cout << _nombre << " ha recibido una calificacion de " << _ultimaNota << "." << endl;
    }

    // Metodo para obtener la ultima calificacion
    float getUltimaNota() {
        return _ultimaNota;
    }
};

int main() {
    // Crear objetos de la clase Estudiante
    Estudiante estudiante1("Carlos", 16, "10mo grado");
    Estudiante estudiante2("Ana", 17, "11mo grado");

    // Simular examenes y calificaciones
    estudiante1.tomarExamen();
    estudiante1.recibirCalificacion(85.5);

    estudiante2.tomarExamen();
    estudiante2.recibirCalificacion(92.0);

    return 0;
}
