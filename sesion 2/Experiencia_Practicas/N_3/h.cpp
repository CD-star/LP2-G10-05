#include <iostream>
#include <vector>
using namespace std;

class Libro {
private:
    string _titulo;
    string _autor;
    int _anio;

public:
    // Constructor
    Libro(string titulo, string autor, int anio) {
        _titulo = titulo;
        _autor = autor;
        _anio = anio;
    }

    // Metodo para comparar dos libros (usando referencia & para evitar copias)
    bool esIgualA(const Libro& otro) {
        return (_titulo == otro._titulo && _autor == otro._autor);
    }

    // Metodo para mostrar informacion del libro
    void mostrarInformacion() {
        cout << "Titulo: " << _titulo << " | Autor: " << _autor << " | Anio: " << _anio << endl;
    }
};

int main() {
    // Crear un arreglo de libros
    vector<Libro> biblioteca;
    biblioteca.push_back(Libro("El Quijote", "Miguel de Cervantes", 1605));
    biblioteca.push_back(Libro("Cien anios de soledad", "Gabriel Garcia Marquez", 1967));
    biblioteca.push_back(Libro("El Quijote", "Miguel de Cervantes", 1605)); // Libro duplicado

    // Comparar dos libros de la biblioteca
    if (biblioteca[0].esIgualA(biblioteca[2])) {
        cout << "Los libros son iguales." << endl;
    } else {
        cout << "Los libros son diferentes." << endl;
    }

    // Comparar libros distintos
    if (biblioteca[0].esIgualA(biblioteca[1])) {
        cout << "Los libros son iguales." << endl;
    } else {
        cout << "Los libros son diferentes." << endl;
    }

    return 0;
}
