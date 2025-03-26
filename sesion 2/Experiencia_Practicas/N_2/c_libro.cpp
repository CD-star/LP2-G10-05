#include <iostream>
using namespace std;

class Libro {
private:
    string titulo;
    string autor;
    string genero;

public:
    // Constructor
    Libro(string _titulo, string _autor, string _genero) {
        titulo = _titulo;
        autor = _autor;
        genero = _genero;
    }

    // Getters
    string getTitulo() {
        return titulo;
    }

    string getAutor() {
        return autor;
    }

    string getGenero() {
        return genero;
    }

    // Setters
    void setTitulo(string _titulo) {
        titulo = _titulo;
    }

    void setAutor(string _autor) {
        autor = _autor;
    }

    void setGenero(string _genero) {
        genero = _genero;
    }

    // Metodo auxiliar para mostrar informacion del libro
    void mostrarInfoLibro() {
        cout << "Titulo: " << titulo << ", Autor: " << autor << ", Genero: " << genero << endl;
    }
};

int main() {
    // Crear instancias de la clase Libro
    Libro libro1("1984", "George Orwell", "Distopia");
    Libro libro2("Cien anios de soledad", "Gabriel Garcia Marquez", "Realismo magico");

    // Mostrar informacion de los libros
    libro1.mostrarInfoLibro();
    libro2.mostrarInfoLibro();

    // Modificar el titulo de libro1 usando el setter
    libro1.setTitulo("Rebelion en la granja");

    // Verificar que el cambio se aplico correctamente
    cout << "Despues de modificar el titulo:" << endl;
    libro1.mostrarInfoLibro();

    return 0;
}
