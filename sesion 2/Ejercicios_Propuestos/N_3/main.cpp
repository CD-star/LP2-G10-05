#include <iostream>
#include <string>

using namespace std;

// Clase Avion
class Avion {
private:
    string _modelo;
    double _capacidadCombustible;  // En litros
    double _consumoPorHora;  // Litros por hora

public:
    // Constructor
    Avion(string modelo, double capacidad, double consumo)
        : _modelo(modelo), _capacidadCombustible(capacidad), _consumoPorHora(consumo) {}

    // Método para verificar si el avión tiene suficiente combustible
    bool tieneCombustibleSuficiente(double duracion) {
        double consumoTotal = duracion * _consumoPorHora;
        return consumoTotal <= _capacidadCombustible;
    }

    // Método para mostrar la información del avión
    void mostrarInfo() {
        cout << "Modelo: " << _modelo << "\nCapacidad de Combustible: " 
            << _capacidadCombustible << " litros\nConsumo por hora: " 
            << _consumoPorHora << " litros/hora\n";
    }
};

// Clase Mision
class Mision {
private:
    string _destino;
    double _duracion;  // En horas
    int _tripulacion;

public:
    // Constructor
    Mision(string destino, double duracion, int tripulacion)
        : _destino(destino), _duracion(duracion), _tripulacion(tripulacion) {}

    // Método para simular la misión
    void simularMision(Avion &avion) {
        cout << "Simulando mision a " << _destino << "...\n";
        if (avion.tieneCombustibleSuficiente(_duracion)) {
            cout << "Mision exitosa: combustible suficiente.\n";
        } else {
            cout << "Mision fallida: combustible insuficiente.\n";
        }
    }

    // Método para mostrar información de la misión
    void mostrarInfo() {
        cout << "Destino: " << _destino << "\nDuracion: " << _duracion 
            << " horas\nTripulacion requerida: " << _tripulacion << "\n";
    }
};

// Función principal
int main() {
    // Crear un avión
    Avion avion1("Boeing 747", 50000, 2500); // Modelo, Capacidad, Consumo/hora
    avion1.mostrarInfo();

    // Crear una misión
    Mision mision1("Paris", 15, 5); // Destino, Duración, Tripulación
    mision1.mostrarInfo();

    // Simular la misión
    mision1.simularMision(avion1);

    return 0;
}
