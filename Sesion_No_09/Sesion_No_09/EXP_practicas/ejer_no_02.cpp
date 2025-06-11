#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Clase Base Abstracta: Animal ---
class Animal {
protected:
    string nombre;
    string especie;

public:
    Animal(const string& nombre, const string& especie)
        : nombre(nombre), especie(especie) {}

    virtual void comer() const = 0;
    virtual void dormir() const = 0;
    virtual void moverse() const = 0;
    virtual void mostrarInformacion() const = 0;

    string getNombre() const { return nombre; }
    string getEspecie() const { return especie; }

    virtual ~Animal() {
        cout << "Animal generico [" << nombre << "] destruido." << endl;
    }
};

// --- Clases Derivadas Concretas ---

class Perro : public Animal {
public:
    Perro(const string& nombre) : Animal(nombre, "Perro") {}

    void comer() const override {
        cout << nombre << " (Perro) esta comiendo croquetas con entusiasmo." << endl;
    }
    void dormir() const override {
        cout << nombre << " (Perro) esta durmiendo acurrucado en su cama." << endl;
    }
    void moverse() const override {
        cout << nombre << " (Perro) esta corriendo y ladrando." << endl;
    }
    void mostrarInformacion() const override {
        cout << "--- Perro ---\n"
             << "  Nombre: " << nombre << "\n"
             << "  Especie: " << especie << "\n"
             << "-------------" << endl;
    }
    ~Perro() override {
        cout << "Perro [" << nombre << "] destruido." << endl;
    }
};

class Gato : public Animal {
public:
    Gato(const string& nombre) : Animal(nombre, "Gato") {}

    void comer() const override {
        cout << nombre << " (Gato) esta cazando un raton imaginario." << endl;
    }
    void dormir() const override {
        cout << nombre << " (Gato) esta durmiendo en una caja soleada." << endl;
    }
    void moverse() const override {
        cout << nombre << " (Gato) esta paseando sigilosamente." << endl;
    }
    void mostrarInformacion() const override {
        cout << "--- Gato ---\n"
             << "  Nombre: " << nombre << "\n"
             << "  Especie: " << especie << "\n"
             << "------------" << endl;
    }
    ~Gato() override {
        cout << "Gato [" << nombre << "] destruido." << endl;
    }
};

class Aguila : public Animal {
public:
    Aguila(const string& nombre) : Animal(nombre, "Aguila") {}

    void comer() const override {
        cout << nombre << " (Aguila) esta cazando presas desde el cielo." << endl;
    }
    void dormir() const override {
        cout << nombre << " (Aguila) esta durmiendo en su nido." << endl;
    }
    void moverse() const override {
        cout << nombre << " (Aguila) esta volando alto." << endl;
    }
    void mostrarInformacion() const override {
        cout << "--- Aguila ---\n"
             << "  Nombre: " << nombre << "\n"
             << "  Especie: " << especie << "\n"
             << "--------------" << endl;
    }
    ~Aguila() override {
        cout << "Aguila [" << nombre << "] destruida." << endl;
    }
};

class Serpiente : public Animal {
public:
    Serpiente(const string& nombre) : Animal(nombre, "Serpiente") {}

    void comer() const override {
        cout << nombre << " (Serpiente) esta devorando un raton." << endl;
    }
    void dormir() const override {
        cout << nombre << " (Serpiente) esta descansando bajo una roca." << endl;
    }
    void moverse() const override {
        cout << nombre << " (Serpiente) se esta deslizando silenciosamente." << endl;
    }
    void mostrarInformacion() const override {
        cout << "--- Serpiente ---\n"
             << "  Nombre: " << nombre << "\n"
             << "  Especie: " << especie << "\n"
             << "-----------------" << endl;
    }
    ~Serpiente() override {
        cout << "Serpiente [" << nombre << "] destruida." << endl;
    }
};

// --- Simulador de Animales ---
class SimuladorAnimales {
private:
    vector<Animal*> animales;

public:
    void agregarAnimal(Animal* animal) {
        animales.push_back(animal);
        cout << "Animal '" << animal->getNombre() << "' agregado al simulador." << endl;
    }

    void simularDia() const {
        if (animales.empty()) {
            cout << "\nEl simulador esta vacio. Agregue algunos animales primero." << endl;
            return;
        }
        cout << "\n--- Iniciando Simulacion del Dia ---" << endl;
        for (Animal* animal : animales) {
            cout << "\n--- " << animal->getNombre() << " (" << animal->getEspecie() << ") ---" << endl;
            animal->comer();
            animal->moverse();
            animal->dormir();
        }
        cout << "\n--- Fin de la Simulacion del Dia ---" << endl;
    }

    void mostrarTodosLosAnimales() const {
        if (animales.empty()) {
            cout << "\nNo hay animales en el simulador todavia." << endl;
            return;
        }
        cout << "\n--- Animales en el Simulador ---" << endl;
        for (Animal* animal : animales) {
            animal->mostrarInformacion();
        }
        cout << "---------------------------------" << endl;
    }

    ~SimuladorAnimales() {
        cout << "\n--- Limpiando la memoria del SimuladorAnimales ---" << endl;
        for (Animal* animal : animales) {
            delete animal;
        }
        animales.clear();
        cout << "Todos los animales han sido liberados de la memoria." << endl;
    }
};

int main() {
    // Ejemplo de uso sin menu
    SimuladorAnimales simulador;
    simulador.agregarAnimal(new Perro("Max"));
    simulador.agregarAnimal(new Gato("Luna"));
    simulador.agregarAnimal(new Aguila("Ares"));
    simulador.agregarAnimal(new Serpiente("Sombra"));

    simulador.simularDia();
    simulador.mostrarTodosLosAnimales();

    return 0;
}
