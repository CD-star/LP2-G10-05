#include <iostream>
using namespace std;

class Ruta {
public:
    string nombre;

    Ruta(string n) : nombre(n) {}

    template <typename T>
    void asignarVehiculo(T vehiculo) {
        cout << "Ruta " << nombre << " asignada al vehículo: " << vehiculo << endl;
    }
};

int main() {
    Ruta r1("Centro-Arequipa");
    r1.asignarVehiculo<string>("Camioneta 4x4");
    r1.asignarVehiculo<int>(1024);

    return 0;
}