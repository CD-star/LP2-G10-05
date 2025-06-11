#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// --- Clase Base Abstracta: FormaGeometrica ---
class FormaGeometrica {
public:
    virtual double calcularArea() const = 0;
    virtual double calcularPerimetro() const = 0;
    virtual void mostrarInformacion() const = 0;
    virtual ~FormaGeometrica() {}
};

// --- Clases Derivadas ---

class Circulo : public FormaGeometrica {
private:
    double radio;
public:
    Circulo(double r) : radio(r) {}

    double calcularArea() const override {
        return M_PI * radio * radio;
    }

    double calcularPerimetro() const override {
        return 2 * M_PI * radio;
    }

    void mostrarInformacion() const override {
        cout << fixed << setprecision(2);
        cout << "Tipo: Circulo" << endl;
        cout << "  Radio: " << radio << endl;
        cout << "  Area: " << calcularArea() << endl;
        cout << "  Perimetro: " << calcularPerimetro() << endl;
        cout << defaultfloat;
    }

    ~Circulo() override {}
};

class Rectangulo : public FormaGeometrica {
private:
    double base;
    double altura;
public:
    Rectangulo(double b, double h) : base(b), altura(h) {}

    double calcularArea() const override {
        return base * altura;
    }

    double calcularPerimetro() const override {
        return 2 * (base + altura);
    }

    void mostrarInformacion() const override {
        cout << fixed << setprecision(2);
        cout << "Tipo: Rectangulo" << endl;
        cout << "  Base: " << base << endl;
        cout << "  Altura: " << altura << endl;
        cout << "  Area: " << calcularArea() << endl;
        cout << "  Perimetro: " << calcularPerimetro() << endl;
        cout << defaultfloat;
    }

    ~Rectangulo() override {}
};

class Triangulo : public FormaGeometrica {
private:
    double base;
    double altura;
public:
    Triangulo(double b, double h) : base(b), altura(h) {}

    double calcularArea() const override {
        return (base * altura) / 2;
    }

    double calcularPerimetro() const override {
        double hipotenusa = sqrt(base * base + altura * altura);
        return base + altura + hipotenusa;
    }

    void mostrarInformacion() const override {
        cout << fixed << setprecision(2);
        cout << "Tipo: Triangulo" << endl;
        cout << "  Base: " << base << endl;
        cout << "  Altura: " << altura << endl;
        cout << "  Area: " << calcularArea() << endl;
        cout << "  Perimetro: " << calcularPerimetro() << endl;
        cout << defaultfloat;
    }

    ~Triangulo() override {}
};

// --- Clase Gestora ---

class GestorFormas {
private:
    vector<FormaGeometrica*> formas;

public:
    void agregarForma(FormaGeometrica* forma) {
        if (forma) {
            formas.push_back(forma);
            cout << "Forma agregada exitosamente." << endl;
        } else {
            cout << "No se pudo agregar la forma." << endl;
        }
    }

    void calcularAreasTotales() const {
        double areaTotal = 0.0;
        for (const auto& forma : formas) {
            areaTotal += forma->calcularArea();
        }
        cout << fixed << setprecision(2);
        cout << "Area total: " << areaTotal << endl;
        cout << defaultfloat;
    }

    void calcularPerimetrosTotales() const {
        double perimetroTotal = 0.0;
        for (const auto& forma : formas) {
            perimetroTotal += forma->calcularPerimetro();
        }
        cout << fixed << setprecision(2);
        cout << "Perimetro total: " << perimetroTotal << endl;
        cout << defaultfloat;
    }

    void mostrarTodasLasFormas() const {
        for (const auto& forma : formas) {
            forma->mostrarInformacion();
            cout << "-----------------------------" << endl;
        }
    }

    ~GestorFormas() {
        for (FormaGeometrica* forma : formas) {
            delete forma;
        }
        formas.clear();
    }
};

// --- Funcion Principal ---

int main() {
    GestorFormas gestor;

    gestor.agregarForma(new Circulo(5.0));
    gestor.agregarForma(new Rectangulo(4.0, 6.0));
    gestor.agregarForma(new Triangulo(3.0, 4.0));

    cout << "\n--- Informacion de todas las formas ---" << endl;
    gestor.mostrarTodasLasFormas();

    cout << "\n--- Calculos generales ---" << endl;
    gestor.calcularAreasTotales();
    gestor.calcularPerimetrosTotales();

    return 0;
}