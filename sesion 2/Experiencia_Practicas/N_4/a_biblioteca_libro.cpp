#include <iostream>
using namespace std;

class Libro {
private:
    string titulo;
    string autor;
    bool prestado; // Indica si el libro está prestado

public:
    // Constructor
    Libro(string _titulo, string _autor) {
        titulo = _titulo;
        autor = _autor;
        prestado = false; // Inicialmente, el libro no está prestado
    }

    // Getters
    string getTitulo() {
        return titulo;
    }

    string getAutor() {
        return autor;
    }

    bool estaPrestado() {
        return prestado;
    }

    // Método para prestar el libro
    void prestar() {
        if (!prestado) {
            prestado = true;
            cout << "El libro \"" << titulo << "\" ha sido prestado." << endl;
        } else {
            cout << "El libro \"" << titulo << "\" ya está prestado." << endl;
        }
    }

    // Método para devolver el libro
    void devolver() {
        if (prestado) {
            prestado = false;
            cout << "El libro \"" << titulo << "\" ha sido devuelto." << endl;
        } else {
            cout << "El libro \"" << titulo << "\" no estaba prestado." << endl;
        }
    }
};

class Biblioteca {
public:
    // Método para prestar un libro
    void prestarLibro(Libro &libro) {
        libro.prestar();
    }

    // Método para devolver un libro
    void devolverLibro(Libro &libro) {
        libro.devolver();
    }
};

int main() {
    // Crear libros
    Libro libro1("Cien anios de soledad", "Gabriel Garcia Marquez");
    Libro libro2("1984", "George Orwell");

    // Crear biblioteca
    Biblioteca biblioteca;

    // Pruebas de préstamo y devolución
    biblioteca.prestarLibro(libro1);
    biblioteca.prestarLibro(libro1); // Intento de préstamo de un libro ya prestado
    biblioteca.devolverLibro(libro1);
    biblioteca.devolverLibro(libro1); // Intento de devolución de un libro no prestado

    return 0;
}
