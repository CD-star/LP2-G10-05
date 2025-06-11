#include <iostream>
using namespace std;

class Figura {
public:
    virtual void calcular_area() {
        cout << "Área calculada" << endl;
    }
    virtual ~Figura() {}
};

class Circulo : public Figura {
public:
    void calcular_area() override {
        cout << "Área calculada Circulo" << endl;
    }
};

class Rectangulo : public Figura {
public:
    void calcular_area() override {
        cout << "Área calculada Rectangulo" << endl;
    }
};

class Triangulo : public Figura {
public:
    void calcular_area() override {
        cout << "Área calculada Triangulo" << endl;
    }
};

int main() {
    const int N = 3;
    Figura* figuras[N];

    figuras[0] = new Circulo();
    figuras[1] = new Rectangulo();
    figuras[2] = new Triangulo();

    for (int i = 0; i < N; i++) {
        figuras[i]->calcular_area();
    }

    for (int i = 0; i < N; i++) {
        delete figuras[i];
    }

    return 0;
}