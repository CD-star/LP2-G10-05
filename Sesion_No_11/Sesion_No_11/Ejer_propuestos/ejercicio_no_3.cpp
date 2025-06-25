#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Persona {
private:
    string nombre;
    int edad;
    string direccion;

public:
    Persona() {}
    Persona(string n, int e, string d) : nombre(n), edad(e), direccion(d) {}

    void mostrar() const {
        cout << "Nombre: " << nombre
             << "\nEdad: " << edad
             << "\nDirección: " << direccion << endl;
    }

    void guardarEnArchivo(const string& archivo) const {
        ofstream out(archivo);
        if (!out) {
            cerr << "No se pudo crear el archivo.\n";
            return;
        }
        out << nombre << endl;
        out << edad << endl;
        out << direccion << endl;
        out.close();
    }

    void cargarDesdeArchivo(const string& archivo) {
        ifstream in(archivo);
        if (!in) {
            cerr << "No se pudo abrir el archivo.\n";
            return;
        }
        getline(in, nombre);
        in >> edad;
        in.ignore();
        getline(in, direccion);
        in.close();
    }
};

int main() {
    string nombre, direccion;
    int edad;
    const string archivo = "persona.txt";

    cout << "Ingrese nombre: ";
    getline(cin, nombre);
    cout << "Ingrese edad: ";
    cin >> edad;
    cin.ignore();
    cout << "Ingrese dirección: ";
    getline(cin, direccion);

    Persona p1(nombre, edad, direccion);
    p1.guardarEnArchivo(archivo);

    Persona p2;
    p2.cargarDesdeArchivo(archivo);

    cout << "\nDatos deserializados:\n";
    p2.mostrar();

    return 0;
}