#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Clase Auto
class Auto {
private:
    string _nombre;
    double _velocidadPromedio; // Km por turno
    double _distanciaRecorrida;

public:
    // Constructor
    Auto(string nombre, double velocidad)
        : _nombre(nombre), _velocidadPromedio(velocidad), _distanciaRecorrida(0) {}

    // Método para avanzar
    void avanzar() {
        double avance = (rand() % 20 + 1) + _velocidadPromedio; // Variación aleatoria
        _distanciaRecorrida += avance;
        cout << _nombre << " avanza " << avance << " km (Total: " << _distanciaRecorrida << " km)" << endl;
    }

    // Obtener distancia recorrida
    double getDistanciaRecorrida() {
        return _distanciaRecorrida;
    }

    // Obtener nombre
    string getNombre() {
        return _nombre;
    }
};

// Clase Carrera
class Carrera {
private:
    double _distanciaTotal;
    Auto *_jugador;
    Auto *_computadora;

public:
    // Constructor
    Carrera(double distancia, string nombreJugador, double dificultad)
        : _distanciaTotal(distancia) {
        _jugador = new Auto(nombreJugador, 10); // Velocidad base 10 km/turno
        _computadora = new Auto("Computadora", 10 + dificultad); // Mayor dificultad = más velocidad
    }

    // Simular carrera
    void iniciar() {
        cout << "\n¡Inicia la carrera de " << _distanciaTotal << " km!\n" << endl;
        while (_jugador->getDistanciaRecorrida() < _distanciaTotal &&
            _computadora->getDistanciaRecorrida() < _distanciaTotal) {
            _jugador->avanzar();
            _computadora->avanzar();
            cout << "-------------------------------------\n";
            system("pause"); // Pausa después de cada turno (opcional)
        }
        determinarGanador();
    }

    // Determinar el ganador
    void determinarGanador() {
        if (_jugador->getDistanciaRecorrida() >= _distanciaTotal &&
            _computadora->getDistanciaRecorrida() >= _distanciaTotal) {
            cout << "¡Empate!\n";
        } else if (_jugador->getDistanciaRecorrida() >= _distanciaTotal) {
            cout << "¡" << _jugador->getNombre() << " gana la carrera!\n";
        } else {
            cout << "¡La computadora gana la carrera!\n";
        }
    }

    // Destructor
    ~Carrera() {
        delete _jugador;
        delete _computadora;
    }
};

// Función principal
int main() {
    srand(time(0)); // Inicializar la semilla aleatoria

    double distancia;
    string nombreJugador;
    double dificultad;

    // Entrada de datos
    cout << "Ingrese el nombre de su auto: ";
    cin >> nombreJugador;
    cout << "Ingrese la distancia total de la carrera (en km): ";
    cin >> distancia;
    cout << "Ingrese la dificultad del oponente (1-10): ";
    cin >> dificultad;

    // Crear la carrera
    Carrera carrera(distancia, nombreJugador, dificultad);
    carrera.iniciar();

    return 0;
}
