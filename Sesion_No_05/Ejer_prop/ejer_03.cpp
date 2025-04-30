#include <iostream>
using namespace std;

class Habitacion {
private:
    int numero;
    string tipo;
    double precioPorNoche;

public:
    Habitacion() {
        numero = 0;
        tipo = "";
        precioPorNoche = 0.0;
    }

    Habitacion(int n, string t, double p) {
        numero = n;
        tipo = t;
        precioPorNoche = p;
    }

    double getPrecioPorNoche() const {
        return precioPorNoche;
    }

    void mostrar() const {
        cout << "Habitación " << numero << " (" << tipo << ") - S/. " << precioPorNoche << endl;
    }
};

class ReservaHotel {
private:
    Habitacion* habitaciones;
    int cantidad;

public:
    ReservaHotel(int cant) {
        cantidad = cant;
        habitaciones = new Habitacion[cantidad];

        for (int i = 0; i < cantidad; i++) {
            int num;
            string tipo;
            double precio;
            cout << "Ingrese datos de la habitacion " << i + 1 << ":\n";
            cout << "Numero: ";
            cin >> num;
            cout << "Tipo: ";
            cin >> tipo;
            cout << "Precio por noche: ";
            cin >> precio;
            habitaciones[i] = Habitacion(num, tipo, precio);
        }
    }

    ~ReservaHotel() {
        delete[] habitaciones;
        cout << "Reserva destruida.\n";
    }

    double calcularTotalPorNoche() const {
        double total = 0;
        for (int i = 0; i < cantidad; i++) {
            total += habitaciones[i].getPrecioPorNoche();
        }
        return total;
    }

    void mostrarHabitaciones() const {
        for (int i = 0; i < cantidad; i++) {
            habitaciones[i].mostrar();
        }
    }
};

int main() {
    int cant;
    cout << "¿Cuántas habitaciones desea registrar? ";
    cin >> cant;

    ReservaHotel reserva(cant);
    cout << "\nHabitaciones registradas:\n";
    reserva.mostrarHabitaciones();

    cout << "\nTotal por noche: S/. " << reserva.calcularTotalPorNoche() << endl;
    return 0;
}