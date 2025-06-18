#include <iostream>
using namespace std;

template <typename T>
class SistemaEntrega {
private:
    T recurso;
public:
    SistemaEntrega(T r) : recurso(r) {}

    void mostrarRecurso() {
        cout << "Recurso en uso: " << recurso << endl;
    }
};

int main() {
    SistemaEntrega<string> sistema1("Camión de reparto");
    SistemaEntrega<int> sistema2(5); // 5 recursos disponibles

    sistema1.mostrarRecurso();
    sistema2.mostrarRecurso();

    return 0;
}