#include <iostream>
#include <vector> // Necesario para usar std::vector
#include <string> // Necesario para std::string

using namespace std; // Usamos el espacio de nombres estandar

// 1. Clase base Animal con un metodo virtual hacerSonido()
class Animal {
public:
    // El metodo hacerSonido es virtual, permitiendo el polimorfismo de subtipo
    virtual void hacerSonido() {
        cout << "Sonido generico de animal" << endl;
    }

    // Un destructor virtual es una buena practica para evitar fugas de memoria
    // cuando se eliminan objetos a traves de punteros a la clase base.
    virtual ~Animal() {
        cout << "Destruyendo un Animal generico." << endl;
    }
};

// 2. Clase derivada Perro
class Perro : public Animal {
public:
    // Redefinicion del metodo hacerSonido() para Perro
    void hacerSonido() override { // 'override' ayuda al compilador a verificar
        cout << "Guau! Guau!" << endl;
    }
    ~Perro() override {
        cout << "Destruyendo un Perro." << endl;
    }
};

// 2. Clase derivada Gato
class Gato : public Animal {
public:
    // Redefinicion del metodo hacerSonido() para Gato
    void hacerSonido() override {
        cout << "Miau! Miau!" << endl;
    }
    ~Gato() override {
        cout << "Destruyendo un Gato." << endl;
    }
};

// 2. Clase derivada Vaca
class Vaca : public Animal {
public:
    // Redefinicion del metodo hacerSonido() para Vaca
    void hacerSonido() override {
        cout << "Muuuu! Muuuu!" << endl;
    }
    ~Vaca() override {
        cout << "Destruyendo una Vaca." << endl;
    }
};

int main() {
    // 4. Crear un arreglo (vector) de punteros a Animal
    // Esto permite almacenar objetos de diferentes tipos de animales (Perro, Gato, Vaca)
    // y tratarlos de forma polimorfica.
    vector<Animal*> granja;

    granja.push_back(new Perro());
    granja.push_back(new Gato());
    granja.push_back(new Vaca());
    granja.push_back(new Perro()); // Podemos agregar mas de uno del mismo tipo

    cout << "--- Sonidos de la granja ---" << endl;
    // 5. Recorrer el arreglo y llamar al metodo hacerSonido() para cada objeto
    for (Animal* animal : granja) {
        animal->hacerSonido(); // Llamada polimorfica
    }
    cout << "--------------------------" << endl << endl;


    cout << "--- Limpiando la granja ---" << endl;
    // Limpiar la memoria asignada dinamicamente
    for (Animal* animal : granja) {
        delete animal; // Se llamara al destructor virtual correcto
    }
    cout << "--------------------------" << endl;

    return 0;
}