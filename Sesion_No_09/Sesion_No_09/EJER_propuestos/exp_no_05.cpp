#include <iostream>
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class FiguraGeometrica {
public:
    virtual double calcularArea() const = 0;
    virtual double calcularPerimetro() const = 0;
    virtual ~FiguraGeometrica() {
        cout << "Destruyendo FiguraGeometrica generica." << endl;
    }
};

class Circulo : public FiguraGeometrica {
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

    ~Circulo() override {
        cout << "Destruyendo Circulo." << endl;
    }
};

class Rectangulo : public FiguraGeometrica {
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

    ~Rectangulo() override {
        cout << "Destruyendo Rectangulo." << endl;
    }
};

class Triangulo : public FiguraGeometrica {
private:
    double base;
    double altura;
    double lado1, lado2, lado3;
public:
    Triangulo(double b, double h, double l1, double l2, double l3)
        : base(b), altura(h), lado1(l1), lado2(l2), lado3(l3) {}

    double calcularArea() const override {
        return (base * altura) / 2;
    }

    double calcularPerimetro() const override {
        return lado1 + lado2 + lado3;
    }

    ~Triangulo() override {
        cout << "Destruyendo Triangulo." << endl;
    }
};

int main() {
    vector<FiguraGeometrica*> figuras; // Usando punteros crudos

    figuras.push_back(new Circulo(5.0)); // Añadiendo objetos con new
    figuras.push_back(new Rectangulo(4.0, 6.0));
    figuras.push_back(new Triangulo(3.0, 4.0, 3.0, 4.0, 5.0));

    cout << "--- Calculando Areas y Perimetros de las Figuras ---" << endl;
    for (size_t i = 0; i < figuras.size(); ++i) {
        cout << "Figura " << i + 1 << ":" << endl;
        cout << "  Area: " << figuras[i]->calcularArea() << endl;
        cout << "  Perimetro: " << figuras[i]->calcularPerimetro() << endl;
        cout << endl;
    }
    cout << "----------------------------------------------" << endl << endl;

    cout << "--- Limpiando la memoria ---" << endl;
    // IMPORTANTE: Con punteros crudos, debes liberar la memoria manualmente
    for (FiguraGeometrica* figura : figuras) {
        delete figura; // Liberar la memoria asignada con 'new'
    }
    cout << "--------------------------" << endl;

    return 0;
}