#include <iostream>
#include <cmath>
using namespace std;

class Figura {
public:
    virtual void dibujar() = 0;
    virtual double calcularArea() = 0;
    virtual ~Figura() {}
};

class Circulo : public Figura {
private:
    double radio;
public:
    Circulo(double r) : radio(r) {}
    void dibujar() override {
        cout << "Dibujando un circulo\n";
    }
    double calcularArea() override {
        return M_PI * radio * radio;
    }
};

class Rectangulo : public Figura {
private:
    double base, altura;
public:
    Rectangulo(double b, double h) : base(b), altura(h) {}
    void dibujar() override {
        cout << "Dibujando un rectangulo\n";
    }
    double calcularArea() override {
        return base * altura;
    }
};

class Triangulo : public Figura {
private:
    double base, altura;
public:
    Triangulo(double b, double h) : base(b), altura(h) {}
    void dibujar() override {
        cout << "Dibujando un triangulo\n";
    }
    double calcularArea() override {
        return (base * altura) / 2;
    }
};

int main() {
    Figura* f1 = new Circulo(4);
    Figura* f2 = new Rectangulo(5, 3);
    Figura* f3 = new Triangulo(6, 2);

    f1->dibujar(); cout << "Area: " << f1->calcularArea() << "\n";
    f2->dibujar(); cout << "Area: " << f2->calcularArea() << "\n";
    f3->dibujar(); cout << "Area: " << f3->calcularArea() << "\n";

    delete f1;
    delete f2;
    delete f3;

    return 0;
}