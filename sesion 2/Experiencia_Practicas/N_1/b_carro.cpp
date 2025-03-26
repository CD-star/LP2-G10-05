#include <iostream>
using namespace std;

class Coche {
private:
    string _modelo;
    int _anio;
    int _velocidad;

public:
    // Constructor
    Coche(string modelo, int anio) {
        _modelo = modelo;
        _anio = anio;
        _velocidad = 0; // Velocidad inicial en 0
    }

    // Metodo para acelerar
    void acelerar() {
        _velocidad += 10;
        cout << _modelo << " ha acelerado. Velocidad actual: " << _velocidad << " km/h." << endl;
    }

    // Metodo para frenar
    void frenar() {
        if (_velocidad >= 10) {
            _velocidad -= 10;
        } else {
            _velocidad = 0;
        }
        cout << _modelo << " ha frenado. Velocidad actual: " << _velocidad << " km/h." << endl;
    }

    // Metodo para obtener la velocidad actual
    int getVelocidad() {
        return _velocidad;
    }
};

int main() {
    // Crear objetos de la clase Coche
    Coche coche1("Toyota Corolla", 2020);
    Coche coche2("Ford Focus", 2018);

    // Probar metodos
    coche1.acelerar();
    coche1.acelerar();
    coche1.frenar();

    coche2.acelerar();
    coche2.frenar();
    coche2.frenar();

    return 0;
}
