#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Clase base abstracta: Personaje ---
class Personaje {
protected:
    string nombre;
    int vida;
    int ataqueBase;
    int defensaBase;

public:
    Personaje(const string& nombre, int vida, int ataque, int defensa)
        : nombre(nombre), vida(vida), ataqueBase(ataque), defensaBase(defensa) {}

    virtual void atacar() const = 0;
    virtual void defender() const = 0;
    virtual void habilidadEspecial() const = 0;

    virtual void mostrarEstado() const {
        cout << "Nombre: " << nombre << ", Vida: " << vida
            << ", Ataque: " << ataqueBase << ", Defensa: " << defensaBase << endl;
    }

    virtual ~Personaje() {
        cout << "Personaje [" << nombre << "] eliminado." << endl;
    }
};

// --- Clase Guerrero ---
class Guerrero : public Personaje {
public:
    Guerrero(const string& nombre)
        : Personaje(nombre, 150, 25, 20) {}

    void atacar() const override {
        cout << nombre << " ataca con su espada causando " << ataqueBase << " de dano." << endl;
    }

    void defender() const override {
        cout << nombre << " se cubre con su escudo, aumentando su defensa a " << defensaBase + 10 << "." << endl;
    }

    void habilidadEspecial() const override {
        cout << nombre << " usa 'Furia del Guerrero' y duplica su ataque por un turno!" << endl;
    }
};

// --- Clase Mago ---
class Mago : public Personaje {
public:
    Mago(const string& nombre)
        : Personaje(nombre, 100, 35, 10) {}

    void atacar() const override {
        cout << nombre << " lanza un hechizo causando " << ataqueBase << " de dano magico." << endl;
    }

    void defender() const override {
        cout << nombre << " invoca un escudo magico, aumentando su defensa a " << defensaBase + 15 << "." << endl;
    }

    void habilidadEspecial() const override {
        cout << nombre << " usa 'Bola de Fuego' y quema a todos los enemigos!" << endl;
    }
};

// --- Clase Arquero ---
class Arquero : public Personaje {
public:
    Arquero(const string& nombre)
        : Personaje(nombre, 120, 20, 15) {}

    void atacar() const override {
        cout << nombre << " dispara una flecha precisa causando " << ataqueBase << " de dano." << endl;
    }

    void defender() const override {
        cout << nombre << " se esquiva agilmente, reduciendo el dano recibido a la mitad." << endl;
    }

    void habilidadEspecial() const override {
        cout << nombre << " usa 'Lluvia de Flechas' y ataca a multiples enemigos!" << endl;
    }
};

// --- Funcion principal ---
int main() {
    vector<Personaje*> equipo;

    equipo.push_back(new Guerrero("Thor"));
    equipo.push_back(new Mago("Merlin"));
    equipo.push_back(new Arquero("Legolas"));

    cout << "\n--- ESTADO DE LOS PERSONAJES ---" << endl;
    for (const auto& p : equipo) {
        p->mostrarEstado();
    }

    cout << "\n--- ACCIONES DE COMBATE ---" << endl;
    for (const auto& p : equipo) {
        p->atacar();
        p->defender();
        p->habilidadEspecial();
        cout << "------------------------------" << endl;
    }

    // Liberar memoria
    for (auto& p : equipo) {
        delete p;
    }
    equipo.clear();

    return 0;
}
