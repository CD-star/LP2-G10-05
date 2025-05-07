#include <iostream>
#include <vector>
#include <algorithm> // Para sort
using namespace std;

class Estudiante {
private:
    string nombre;
    vector<int> notas;

public:
    Estudiante(const string& nombreEst, const vector<int>& notasEst)
        : nombre(nombreEst), notas(notasEst) {}

    vector<int> getNotas() {
        return notas;
    }

    float promedio() const {
        if (notas.empty()) return 0.0;

        float suma = 0;
        for (int n : notas) suma += n;
        return suma / notas.size();
    }

    void mostrar() const {
        cout << "Nombre: " << nombre << "\nNotas: ";
        for (int n : notas) cout << n << " ";
        cout << "\nPromedio: " << promedio() << "\n\n";
    }
};

int main() {
    vector<Estudiante> alumnos;

    alumnos.emplace_back("Ana", vector<int>{18, 17, 19});
    alumnos.emplace_back("Luis", vector<int>{15, 14, 16});
    alumnos.emplace_back("Claudia", vector<int>{20, 19, 18});
    alumnos.emplace_back("Carlos", vector<int>{12, 15, 14});

    // Ordenar de mayor a menor promedio
    sort(alumnos.begin(), alumnos.end(), [](const Estudiante& a, const Estudiante& b) {
        return a.promedio() < b.promedio(); // Para descendente
    });

    // Mostrar resultados ordenados
    for (const Estudiante& est : alumnos) {
        est.mostrar();
    }

    return 0;
}
