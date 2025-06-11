#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- Clase Base Abstracta: Empleado ---
class Empleado {
protected:
    string nombre;
    string id;

public:
    Empleado(const string& nombre, const string& id)
        : nombre(nombre), id(id) {}

    virtual double calcularSalario() const = 0;
    virtual void mostrarInformacion() const = 0;

    virtual ~Empleado() {
        cout << "Empleado [" << nombre << "] destruido." << endl;
    }
};

// --- Clase Asalariado ---
class Asalariado : public Empleado {
private:
    double salarioMensual;

public:
    Asalariado(const string& nombre, const string& id, double salario)
        : Empleado(nombre, id), salarioMensual(salario) {}

    double calcularSalario() const override {
        return salarioMensual;
    }

    void mostrarInformacion() const override {
        cout << "--- Asalariado ---\n"
             << "Nombre: " << nombre << "\n"
             << "ID: " << id << "\n"
             << "Salario Mensual: $" << fixed << setprecision(2) << salarioMensual << "\n"
             << "------------------" << endl;
    }
};

// --- Clase EmpleadoPorHora ---
class EmpleadoPorHora : public Empleado {
private:
    double horasTrabajadas;
    double tarifaPorHora;

public:
    EmpleadoPorHora(const string& nombre, const string& id, double horas, double tarifa)
        : Empleado(nombre, id), horasTrabajadas(horas), tarifaPorHora(tarifa) {}

    double calcularSalario() const override {
        return horasTrabajadas * tarifaPorHora;
    }

    void mostrarInformacion() const override {
        cout << "--- Empleado por Hora ---\n"
             << "Nombre: " << nombre << "\n"
             << "ID: " << id << "\n"
             << "Horas Trabajadas: " << horasTrabajadas << "\n"
             << "Tarifa por Hora: $" << fixed << setprecision(2) << tarifaPorHora << "\n"
             << "Salario Total: $" << calcularSalario() << "\n"
             << "-------------------------" << endl;
    }
};

// --- Clase Comisionista ---
class Comisionista : public Empleado {
private:
    double ventasRealizadas;
    double porcentajeComision;

public:
    Comisionista(const string& nombre, const string& id, double ventas, double comision)
        : Empleado(nombre, id), ventasRealizadas(ventas), porcentajeComision(comision) {}

    double calcularSalario() const override {
        return ventasRealizadas * (porcentajeComision / 100.0);
    }

    void mostrarInformacion() const override {
        cout << "--- Comisionista ---\n"
             << "Nombre: " << nombre << "\n"
             << "ID: " << id << "\n"
             << "Ventas Realizadas: $" << fixed << setprecision(2) << ventasRealizadas << "\n"
             << "Porcentaje Comision: " << porcentajeComision << "%\n"
             << "Salario Total: $" << calcularSalario() << "\n"
             << "--------------------" << endl;
    }
};

// --- Clase Sistema de Nomina ---
class SistemaNomina {
private:
    vector<Empleado*> empleados;

public:
    void agregarEmpleado(Empleado* emp) {
        empleados.push_back(emp);
    }

    void mostrarTodosLosEmpleados() const {
        cout << "\n--- Lista de Empleados ---" << endl;
        for (Empleado* emp : empleados) {
            emp->mostrarInformacion();
        }
        cout << "--------------------------" << endl;
    }

    void calcularNominaTotal() const {
        double total = 0.0;
        for (Empleado* emp : empleados) {
            total += emp->calcularSalario();
        }
        cout << "\nNomina Total: $" << fixed << setprecision(2) << total << endl;
    }

    ~SistemaNomina() {
        cout << "\nLiberando memoria de empleados..." << endl;
        for (Empleado* emp : empleados) {
            delete emp;
        }
        empleados.clear();
    }
};

// --- Funcion Principal sin menú ---
int main() {
    SistemaNomina sistema;

    sistema.agregarEmpleado(new Asalariado("Luis", "A001", 2500.00));
    sistema.agregarEmpleado(new EmpleadoPorHora("Ana", "H002", 160, 15.5));
    sistema.agregarEmpleado(new Comisionista("Carlos", "C003", 10000, 5));

    sistema.mostrarTodosLosEmpleados();
    sistema.calcularNominaTotal();

    return 0;
}
