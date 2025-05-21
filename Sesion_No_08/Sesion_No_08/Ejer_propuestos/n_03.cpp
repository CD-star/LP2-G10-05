#include <iostream>
using namespace std;

class Empleado {
public:
    virtual double calcularSalario() = 0;
    virtual ~Empleado() {}
};

class EmpleadoTiempoCompleto : public Empleado {
private:
    double salarioMensual;
public:
    EmpleadoTiempoCompleto(double s) : salarioMensual(s) {}
    double calcularSalario() override {
        return salarioMensual;
    }
};

class EmpleadoMedioTiempo : public Empleado {
private:
    double horasTrabajadas;
    double pagoPorHora;
public:
    EmpleadoMedioTiempo(double horas, double pago)
        : horasTrabajadas(horas), pagoPorHora(pago) {}
    double calcularSalario() override {
        return horasTrabajadas * pagoPorHora;
    }
};

int main() {
    Empleado* emp1 = new EmpleadoTiempoCompleto(2500);
    Empleado* emp2 = new EmpleadoMedioTiempo(80, 15);

    cout << "Salario Tiempo Completo: " << emp1->calcularSalario() << "\n";
    cout << "Salario Medio Tiempo: " << emp2->calcularSalario() << "\n";

    delete emp1;
    delete emp2;

    return 0;
}