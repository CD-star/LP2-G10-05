#include <iostream>
using namespace std;

// Template de función para calcular distancia (por ejemplo, entre puntos)
template <typename T>
T calcularDistancia(T inicio, T fin) {
    return fin - inicio;
}

// Template para imprimir datos genéricos
template <typename T>
void generarInforme(T dato) {
    cout << "Informe: " << dato << endl;
}

int main() {
    cout << "Distancia (int): " << calcularDistancia(10, 25) << endl;
    cout << "Distancia (float): " << calcularDistancia(5.5f, 9.2f) << endl;

    generarInforme<string>("Ruta entregada correctamente.");
    generarInforme<int>(100);

    return 0;
}