#include <iostream>
#include <string>

using namespace std; // Para no tener que escribir std:: antes de cada elemento estandar

// Clase base Movil
class Movil {
protected: // Usamos protected para que las clases derivadas puedan acceder si es necesario,
           // aunque en este caso se inicializan via constructor.
    string marca;
    string modelo;
    string sistema_operativo;

public:
    // Constructor de la clase Movil
    Movil(string marca_mov, string modelo_mov, string so_mov)
        : marca(marca_mov), modelo(modelo_mov), sistema_operativo(so_mov) {
        cout << "Constructor de Movil ejecutado para: " << marca << " " << modelo << endl;
    }

    // Destructor virtual de la clase Movil
    // Es virtual para asegurar que se llame al destructor correcto de la clase derivada
    // cuando se trabaja con punteros a la clase base.
    virtual ~Movil() {
        cout << "Destructor de Movil ejecutado para: " << marca << " " << modelo << endl;
    }

    // Metodo para mostrar informacion (opcional, pero util)
    virtual void mostrarDetalles() const {
        cout << "  Marca: " << marca << endl;
        cout << "  Modelo: " << modelo << endl;
        cout << "  Sistema Operativo: " << sistema_operativo << endl;
    }
};

// Clase derivada Telefono
class Telefono : public Movil {
private:
    // Atributo especifico de Telefono (ejemplo)
    bool tiene_capacidad_5g;

public:
    // Constructor especifico de la clase Telefono
    // Llama al constructor de la clase base Movil
    Telefono(string marca_tel, string modelo_tel, string so_tel, bool capacidad_5g)
        : Movil(marca_tel, modelo_tel, so_tel), tiene_capacidad_5g(capacidad_5g) {
        cout << "  -> Constructor especifico de Telefono ejecutado para: " << marca << " " << modelo << endl;
    }

    // Destructor especifico de la clase Telefono
    ~Telefono() override { // 'override' es buena practica para metodos virtuales
        cout << "  -> Destructor especifico de Telefono ejecutado para: " << marca << " " << modelo << endl;
    }

    // Sobrescribimos mostrarDetalles (opcional)
    void mostrarDetalles() const override {
        cout << "Detalles del Telefono:" << endl;
        Movil::mostrarDetalles(); // Llama al metodo de la clase base
        cout << "  Capacidad 5G: " << (tiene_capacidad_5g ? "Si" : "No") << endl;
    }
};

// Clase derivada Tablet
class Tablet : public Movil {
private:
    // Atributo especifico de Tablet (ejemplo)
    double tamanio_pantalla_pulgadas;

public:
    // Constructor especifico de la clase Tablet
    // Llama al constructor de la clase base Movil
    Tablet(string marca_tab, string modelo_tab, string so_tab, double pantalla_pulg)
        : Movil(marca_tab, modelo_tab, so_tab), tamanio_pantalla_pulgadas(pantalla_pulg) {
        cout << "  -> Constructor especifico de Tablet ejecutado para: " << marca << " " << modelo << endl;
    }

    // Destructor especifico de la clase Tablet
    ~Tablet() override {
        cout << "  -> Destructor especifico de Tablet ejecutado para: " << marca << " " << modelo << endl;
    }

    // Sobrescribimos mostrarDetalles (opcional)
    void mostrarDetalles() const override {
        cout << "Detalles de la Tablet:" << endl;
        Movil::mostrarDetalles(); // Llama al metodo de la clase base
        cout << "  Tamanio Pantalla: " << tamanio_pantalla_pulgadas << " pulgadas" << endl;
    }
};

// Funcion principal para demostrar el uso
int main() {
    cout << "--- Iniciando creacion de Telefono ---" << endl;
    Telefono miTelefono("Samsung", "Galaxy S24", "Android 14", true);
    miTelefono.mostrarDetalles();
    cout << "--- Fin creacion de Telefono ---\n" << endl;

    cout << "--- Iniciando creacion de Tablet ---" << endl;
    Tablet miTablet("Apple", "iPad Pro", "iPadOS 17", 11.0);
    miTablet.mostrarDetalles();
    cout << "--- Fin creacion de Tablet ---\n" << endl;

    cout << "--- Los objetos seran destruidos al salir del alcance (main) ---" << endl;
    // Al salir de main, los destructores se llamaran en orden inverso a la creacion:
    // 1. Destructor de miTablet (primero ~Tablet(), luego ~Movil())
    // 2. Destructor de miTelefono (primero ~Telefono(), luego ~Movil())

    return 0;
}