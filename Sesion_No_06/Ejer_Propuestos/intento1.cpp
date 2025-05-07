#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // Para sort
#include <iomanip>    // Para setprecision

using namespace std;

class Alumno {
private:
    string nombre;
    int edad;
    float promedio;

public:
    // Constructor
    Alumno(const string& nombre, int edad, float promedio)
        : nombre(nombre), edad(edad), promedio(promedio) {}

    // Método que representa al alumno como string
    string to_string() const {
        return "Nombre: " + nombre + ", Edad: " + std::to_string(edad) + ", Promedio: " + std::to_string(promedio);
    }

    // Comparar promedios
    bool esMenorQue(const Alumno& otro) const {
        return this->promedio < otro.promedio;
    }

    float getPromedio() const {
        return promedio;
    }

    string getNombre() const {
        return nombre;
    }

    int getEdad() const {
        return edad;
    }
};

class Grupo {
private:
    vector<Alumno> alumnos;
    int cantidad;

public:
    // Constructor que reserva capacidad para cantidad elementos
    Grupo(int cantidad) : cantidad(cantidad) {
        alumnos.reserve(cantidad);
    }

    // Agregar nuevo alumno
    void agregarAlumno(const string& nombre, int edad, float promedio) {
        if (alumnos.size() < cantidad) {
            alumnos.emplace_back(nombre, edad, promedio);
        } else {
            cout << "No se pueden agregar más alumnos. Capacidad llena." << endl;
        }
    }

    // Representar el grupo como string
    string to_string() const {
        string resultado = "Grupo de " + std::to_string(alumnos.size()) + " alumnos:\n";
        for (const auto& alumno : alumnos) {
            resultado += " - " + alumno.to_string() + "\n";
        }
        return resultado;
    }

    // Ordenar por promedio (de menor a mayor)
    void ordenarPorPromedio() {
        sort(alumnos.begin(), alumnos.end(), [](const Alumno& a, const Alumno& b) {
            return a.getPromedio() < b.getPromedio();
        });
    }

    // Calcular promedio general
    float promedioGeneral() const {
        if (alumnos.empty()) return 0.0f;

        float suma = 0.0;
        for (const auto& alumno : alumnos) {
            suma += alumno.getPromedio();
        }
        return suma / alumnos.size();
    }

    // Alumno con mejor promedio
    Alumno obtenerMejorAlumno() const {
        if (alumnos.empty()) {
            throw runtime_error("No hay alumnos en el grupo.");
        }

        return *max_element(alumnos.begin(), alumnos.end(), [](const Alumno& a, const Alumno& b) {
            return a.getPromedio() < b.getPromedio();
        });
    }
};

int main() {
    // Crear un grupo con capacidad para 5 alumnos
    Grupo grupo(5);

    // Agregar 5 alumnos
    grupo.agregarAlumno("Ana", 20, 17.8);
    grupo.agregarAlumno("Luis", 21, 15.2);
    grupo.agregarAlumno("Carla", 22, 18.3);
    grupo.agregarAlumno("Mario", 19, 14.7);
    grupo.agregarAlumno("Sofia", 20, 19.1);

    // Mostrar grupo antes de ordenar
    cout << "=== Grupo Original ===" << endl;
    cout << grupo.to_string() << endl;

    // Ordenar grupo por promedio
    grupo.ordenarPorPromedio();

    // Mostrar grupo ordenado
    cout << "=== Grupo Ordenado por Promedio ===" << endl;
    cout << grupo.to_string() << endl;

    // Promedio general del grupo
    cout << fixed << setprecision(2);
    cout << "Promedio general del grupo: " << grupo.promedioGeneral() << endl;

    // Mejor alumno
    Alumno mejor = grupo.obtenerMejorAlumno();
    cout << "Mejor alumno: " << mejor.to_string() << endl;

    return 0;
}
