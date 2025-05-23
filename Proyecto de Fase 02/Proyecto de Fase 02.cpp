#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
using namespace std;

// Clase abstracta Vehiculo
class Vehiculo {
protected:
    string placa;
    int horas;

public:
    Vehiculo(string placa = "", int horas = 0) : placa(placa), horas(horas) {}
    virtual ~Vehiculo() {
        cout << "Destructor de Vehiculo (" << placa << ")" << endl;
    }

    virtual float calcularTarifa() const = 0; // Método abstracto
    string getPlaca() const { return placa; }
    int getHoras() const { return horas; }

    friend ostream& operator<<(ostream& os, const Vehiculo& v) {
        os << "Placa: " << v.placa << ", Horas: " << v.horas;
        return os;
    }
};

// Clase Auto
class Auto : public Vehiculo {
public:
    Auto(string placa, int horas) : Vehiculo(placa, horas) {}
    float calcularTarifa() const override {
        return horas * 3.5;
    }
};

// Clase Moto
class Moto : public Vehiculo {
public:
    Moto(string placa, int horas) : Vehiculo(placa, horas) {}
    float calcularTarifa() const override {
        return horas * 2.0;
    }
};

// Clase Parqueadero
class Parqueadero {
private:
    vector<shared_ptr<Vehiculo>> espacios;
    static int capacidad;
    static int ocupados;
    bool bloqueado;

public:
    Parqueadero() : bloqueado(false) {}
    ~Parqueadero() {
        cout << "Destructor de Parqueadero" << endl;
    }

    static void setCapacidad(int c) { capacidad = c; }
    static int getOcupados() { return ocupados; }

    void bloquear() { bloqueado = true; }
    void desbloquear() { bloqueado = false; }
    bool estaBloqueado() const { return bloqueado; }

    bool agregarVehiculo(shared_ptr<Vehiculo> v) {
        if (bloqueado) {
            cout << "Parqueadero bloqueado." << endl;
            return false;
        }
        if (ocupados >= capacidad) {
            cout << "Parqueadero lleno." << endl;
            return false;
        }
        espacios.push_back(v);
        ocupados++;
        return true;
    }

    void retirarVehiculo(string placa) {
        for (auto it = espacios.begin(); it != espacios.end(); ++it) {
            if ((*it)->getPlaca() == placa) {
                cout << "Tarifa a pagar: S/." << (*it)->calcularTarifa() << endl;
                espacios.erase(it);
                ocupados--;
                return;
            }
        }
        cout << "Vehículo no encontrado." << endl;
    }

    void mostrarVehiculos() const {
        if (espacios.empty()) {
            cout << "No hay vehículos en el parqueadero." << endl;
            return;
        }
        cout << "\n--- Vehículos en el parqueadero ---" << endl;
        for (const auto& v : espacios) {
            cout << *v << ", Tarifa: S/." << v->calcularTarifa() << endl;
        }
    }

    void generarReporte() const {
        cout << "\n--- Reporte del parqueadero ---" << endl;
        cout << "Capacidad: " << capacidad << endl;
        cout << "Ocupados: " << ocupados << endl;
        cout << "Disponibles: " << (capacidad - ocupados) << endl;
    }
};

// Inicialización de estáticos
int Parqueadero::capacidad = 5;
int Parqueadero::ocupados = 0;

int main() {
    Parqueadero parqueo;
    Parqueadero::setCapacidad(5);

    int opcion;
    do {
        cout << "\n--- MENÚ ---\n";
        cout << "1. Ingresar Auto\n2. Ingresar Moto\n3. Retirar Vehículo\n4. Mostrar Parqueadero\n";
        cout << "5. Bloquear Parqueadero\n6. Desbloquear Parqueadero\n7. Generar Reporte\n8. Salir\nOpción: ";
        cin >> opcion;

        string placa;
        int horas;

        try {
            switch (opcion) {
                case 1:
                    cout << "Placa: "; cin >> placa;
                    cout << "Horas: "; cin >> horas;
                    if (horas < 0) throw invalid_argument("Horas no válidas");
                    parqueo.agregarVehiculo(make_shared<Auto>(placa, horas));
                    break;
                case 2:
                    cout << "Placa: "; cin >> placa;
                    cout << "Horas: "; cin >> horas;
                    if (horas < 0) throw invalid_argument("Horas no válidas");
                    parqueo.agregarVehiculo(make_shared<Moto>(placa, horas));
                    break;
                case 3:
                    cout << "Placa: "; cin >> placa;
                    parqueo.retirarVehiculo(placa);
                    break;
                case 4:
                    parqueo.mostrarVehiculos();
                    break;
                case 5:
                    parqueo.bloquear();
                    cout << "Parqueadero bloqueado.\n";
                    break;
                case 6:
                    parqueo.desbloquear();
                    cout << "Parqueadero desbloqueado.\n";
                    break;
                case 7:
                    parqueo.generarReporte();
                    break;
                case 8:
                    cout << "Saliendo del sistema...\n";
                    break;
                default:
                    cout << "Opción inválida.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (opcion != 8);

    return 0;
}