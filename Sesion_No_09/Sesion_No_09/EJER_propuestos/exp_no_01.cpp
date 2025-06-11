#include <iostream>
#include <string> // Necesario para std::string si se usa en otros contextos

using namespace std; // Usamos el espacio de nombres estandar

// Clase base Animal
class Animal {
public:
    // Metodo virtual que puede ser redefinido por clases derivadas
    virtual void hacerSonido() {
        cout << "Sonido generico de animal" << endl;
    }

    // Metodo no virtual
    void mostrarNombre(const string& nombre) {
        cout << "Animal: " << nombre << endl;
    }
};

// Clase derivada Perro
class Perro : public Animal {
public:
    // Redefinicion del metodo hacerSonido() de la clase base
    void hacerSonido() override { // 'override' es opcional pero buena practica
        cout << "Guau!" << endl;
    }
};

// Clase derivada Gato
class Gato : public Animal {
public:
    // Redefinicion del metodo hacerSonido() de la clase base
    void hacerSonido() override {
        cout << "Miau!" << endl;
    }
};

int main() {
    // Declaramos punteros de la clase base Animal
    Animal *animal1 = new Perro(); // animal1 apunta a un objeto Perro
    Animal *animal2 = new Gato();  // animal2 apunta a un objeto Gato

    // Llamadas polimorficas: se ejecuta el metodo de la clase real del objeto
    cout << "Animal 1 hace: ";
    animal1->hacerSonido(); // Llama a Perro::hacerSonido()

    cout << "Animal 2 hace: ";
    animal2->hacerSonido(); // Llama a Gato::hacerSonido()

    // Llamada a un metodo no virtual (se resuelve en tiempo de compilacion)
    animal1->mostrarNombre("Fido");

    // ¡Importante! Liberar la memoria asignada dinamicamente
    delete animal1;
    delete animal2;

    return 0;
}