#include <iostream>
#include <stdexcept>  // Para std::runtime_error

using namespace std;

// Función divide que lanza excepción si divisor es cero
double divide(int numerador, int denominador) {
    if (denominador == 0)
        throw runtime_error("No se puede dividir por cero.");
    return static_cast<double>(numerador) / denominador;
}

int main() {
    int a, b;

    cout << "Ingrese el numerador: ";
    cin >> a;
    cout << "Ingrese el denominador: ";
    cin >> b;

    try {
        double resultado = divide(a, b);
        cout << "Resultado: " << resultado << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Otra prueba con valores fijos
    try {
        cout << "\nDividiendo 10 / 0:\n";
        cout << "Resultado: " << divide(10, 0) << endl;
    } catch (const runtime_error& e) {
        cerr << "Error capturado: " << e.what() << endl;
    }

    return 0;
}