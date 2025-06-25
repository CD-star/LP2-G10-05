#include <iostream>
#include <fstream>
#include <string>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>

using namespace std; // This line brings std components into the current scope

// Clase Persona con serializacion
class Persona {
private:
    string nombre;
    int edad;
    string direccion;

public:
    // Default constructor is needed for deserialization
    Persona() : nombre(""), edad(0), direccion("") {}

    Persona(string n, int e, string d)
        : nombre(std::move(n)), edad(e), direccion(std::move(d)) {}

    void setNombre(string n) { nombre = std::move(n); }
    void setEdad(int e) { edad = e; }
    void setDireccion(string d) { direccion = std::move(d); }

    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    string getDireccion() const { return direccion; }

    void mostrar() const {
        cout << "Nombre: " << nombre << "\nEdad: " << edad << "\nDireccion: " << direccion << endl;
    }

    // Serializacion con Cereal
    template<class Archive>
    void serialize(Archive & ar) {
        ar(nombre, edad, direccion);
    }
};

int main() {
    const string archivo = "persona.dat";

    // --- Serializar (Guardar) un objeto Persona ---
    Persona p1("Joaquin", 18, "Calle Los Robles 123");
    {
        ofstream ofs(archivo, ios::binary);
        if (!ofs.is_open()) {
            cerr << "Error: No se pudo crear o abrir el archivo para escritura.\n";
            return 1;
        }
        cereal::BinaryOutputArchive oarch(ofs);
        oarch(p1);
    }
    cout << "Objeto 'p1' serializado y guardado en '" << archivo << "'\n";

    // --- Deserializar (Cargar) un objeto Persona ---
    Persona p2;
    {
        ifstream ifs(archivo, ios::binary);
        if (!ifs.is_open()) {
            cerr << "Error: No se pudo abrir el archivo '" << archivo << "' para lectura.\n";
            return 1;
        }
        cereal::BinaryInputArchive iarch(ifs);
        try {
            iarch(p2);
        } catch (const cereal::Exception& e) {
            cerr << "Error durante la deserializacion: " << e.what() << '\n';
            return 1;
        }
    }

    cout << "\nObjeto 'p2' deserializado desde archivo:\n";
    p2.mostrar();

    return 0;
}