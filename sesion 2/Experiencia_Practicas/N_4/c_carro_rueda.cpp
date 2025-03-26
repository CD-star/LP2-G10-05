#include <iostream>
using namespace std;

class Rueda {
private:
    int tamano;
    bool enBuenEstado;

public:
    // Constructor
    Rueda(int _tamano) {
        tamano = _tamano;
        enBuenEstado = true; // Se asume que la rueda es nueva y está en buen estado.
    }

    // Método para dañar una rueda (simulación)
    void pinchar() {
        enBuenEstado = false;
        cout << "¡Una rueda de tamaño " << tamano << " se ha pinchado!" << endl;
    }

    // Método para cambiar una rueda
    void cambiar() {
        enBuenEstado = true;
        cout << "La rueda de tamaño " << tamano << " ha sido reemplazada." << endl;
    }

    // Método para verificar si la rueda está en buen estado
    bool estaEnBuenEstado() {
        return enBuenEstado;
    }
};

class Carro {
private:
    Rueda* ruedas[4]; // Cuatro ruedas

public:
    // Constructor
    Carro(int tamanoRuedas) {
        for (int i = 0; i < 4; i++) {
            ruedas[i] = new Rueda(tamanoRuedas);
        }
    }

    // Método para mover el carro
    void mover() {
        for (int i = 0; i < 4; i++) {
            if (!ruedas[i]->estaEnBuenEstado()) {
                cout << "El carro no puede moverse porque una rueda está dañada." << endl;
                return;
            }
        }
        cout << "El carro está en movimiento." << endl;
    }

    // Método para cambiar una rueda específica
    void cambiarRueda(int indice) {
        if (indice >= 0 && indice < 4) {
            ruedas[indice]->cambiar();
            cout << "Rueda " << indice + 1 << " cambiada con éxito." << endl;
        } else {
            cout << "Índice de rueda no válido." << endl;
        }
    }

    // Destructor para liberar memoria
    ~Carro() {
        for (int i = 0; i < 4; i++) {
            delete ruedas[i];
        }
    }
};

int main() {
    // Crear un carro con ruedas de tamaño 16
    Carro miCarro(16);

    // Intentar mover el carro
    miCarro.mover();

    // Pinchar una rueda
    cout << "Simulando una rueda dañada..." << endl;
    miCarro.cambiarRueda(2); // Se reemplaza la tercera rueda antes de que se dañe

    // Intentar moverlo de nuevo
    miCarro.mover();

    return 0;
}
