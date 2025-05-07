#include <iostream>
#include <cmath> // Para M_PI
using namespace std;

class Circulo {
private:
    double radio;
    double diametro;

public:
    // Constructor
    Circulo(double r) : radio(r), diametro(2 * r) {}

    // Mostrar datos del círculo
    void mostrar() const {
        cout << "Radio: " << radio << " - Diámetro: " << diametro << endl;
    }

    // Declaración de función amiga
    friend double calcularArea(const Circulo& c);
};

// Función amiga que accede al atributo privado 'radio'
double calcularArea(const Circulo& c) {
    return M_PI * c.radio * c.radio;
}

int main() {
    // Crear círculos
    Circulo c1(5.0);
    Circulo c2(3.2);

    // Mostrar datos
    c1.mostrar();
    cout << "Área: " << calcularArea(c1) << endl;

    c2.mostrar();
    cout << "Área: " << calcularArea(c2) << endl;

    return 0;
}
