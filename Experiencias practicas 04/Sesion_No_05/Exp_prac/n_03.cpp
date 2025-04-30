#include <iostream>
using namespace std;

// Clase Fecha
class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}  // Constructor con lista de inicialización

    void mostrar() const {
        cout << dia << "/" << mes << "/" << anio;
    }
};

// Clase Contrato
class Contrato {
private:
    string codigo;
    string descripcion;
    Fecha fechaInicio;

public:
    // Constructor con lista de inicialización
    Contrato(string c, string d, int dia, int mes, int anio)
        : codigo(c), descripcion(d), fechaInicio(dia, mes, anio) {}

    void mostrarContrato() const {
        cout << "Codigo: " << codigo << endl;
        cout << "Descripcion: " << descripcion << endl;
        cout << "Fecha de inicio: ";
        fechaInicio.mostrar();
        cout << endl;
    }
};

// Clase Empleado
class Empleado {
private:
    Contrato contrato;

public:
    // Constructor con lista de inicialización
    Empleado(string cod, string desc, int dia, int mes, int anio)
        : contrato(cod, desc, dia, mes, anio) {}

    void mostrarInfo() const {
        cout << "Informacion del contrato del empleado:" << endl;
        contrato.mostrarContrato();
    }
};

// Función principal
int main() {
    Empleado emp("C001", "Contrato tiempo completo", 15, 4, 2023);
    emp.mostrarInfo();

    return 0;
}