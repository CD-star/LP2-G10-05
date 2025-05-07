#include <iostream>
#include <vector>
using namespace std;

class Vector2D {
private:
    vector<vector<double>> componentes;  // Un vector de vectores para representar un vector 2D

public:
    // Constructor que recibe un vector de vectores
    Vector2D(const vector<vector<double>>& componentes_iniciales) : componentes(componentes_iniciales) {}

    // Método para mostrar el vector 2D
    void mostrar() const {
        for (size_t i = 0; i < componentes.size(); i++) {
            cout << "(";
            for (size_t j = 0; j < componentes[i].size(); j++) {
                cout << componentes[i][j];
                if (j != componentes[i].size() - 1) cout << ", ";
            }
            cout << ")";
            if (i != componentes.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    // Método para sumar dos vectores 2D
    Vector2D operator+(const Vector2D& v) const {
        size_t filas = componentes.size();
        size_t columnas = componentes[0].size();

        if (filas != v.componentes.size() || columnas != v.componentes[0].size()) {
            cout << "Error: Los vectores 2D deben tener las mismas dimensiones.\n";
            return Vector2D({});
        }

        vector<vector<double>> resultado(filas, vector<double>(columnas));
        for (size_t i = 0; i < filas; i++) {
            for (size_t j = 0; j < columnas; j++) {
                resultado[i][j] = componentes[i][j] + v.componentes[i][j];
            }
        }

        return Vector2D(resultado);
    }

    // Método para restar dos vectores 2D
    Vector2D operator-(const Vector2D& v) const {
        size_t filas = componentes.size();
        size_t columnas = componentes[0].size();

        if (filas != v.componentes.size() || columnas != v.componentes[0].size()) {
            cout << "Error: Los vectores 2D deben tener las mismas dimensiones.\n";
            return Vector2D({});
        }

        vector<vector<double>> resultado(filas, vector<double>(columnas));
        for (size_t i = 0; i < filas; i++) {
            for (size_t j = 0; j < columnas; j++) {
                resultado[i][j] = componentes[i][j] - v.componentes[i][j];
            }
        }

        return Vector2D(resultado);
    }
};

int main() {
    // Crear vectores 2D (matrices de tamaño 2x3)
    Vector2D v1({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});  // Vector 2D de 2 filas y 3 columnas
    Vector2D v2({{6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});  // Vector 2D de 2 filas y 3 columnas

    // Mostrar los vectores
    cout << "Primer vector 2D: ";
    v1.mostrar();

    cout << "Segundo vector 2D: ";
    v2.mostrar();

    // Sumar los vectores 2D
    Vector2D suma = v1 + v2;
    cout << "Resultado de la suma de los vectores 2D: ";
    suma.mostrar();

    // Restar los vectores 2D
    Vector2D resta = v1 - v2;
    cout << "Resultado de la resta de los vectores 2D: ";
    resta.mostrar();

    return 0;
}
