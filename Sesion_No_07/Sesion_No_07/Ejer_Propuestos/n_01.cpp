#include <iostream>
#include <string>
#include <vector>

// Usar el espacio de nombres std para evitar escribir std:: repetidamente
using namespace std;

// Clase base Vehículo
class Vehiculo {
protected:
    string marca;
    string modelo;
    int anio_fabricacion;
    double precio;

public:
    // Constructor de la clase base
    Vehiculo(string marca, string modelo, int anio, double precio)
        : marca(marca), modelo(modelo), anio_fabricacion(anio), precio(precio) {
        // cout << "Constructor de Vehiculo llamado para: " << this->marca << " " << this->modelo << endl;
    }

    // Destructor virtual (importante para la correcta destrucción de objetos derivados a través de punteros base)
    virtual ~Vehiculo() {
        // cout << "Destructor de Vehiculo llamado para: " << this->marca << " " << this->modelo << endl;
    }

    // Método virtual para mostrar información (puede ser sobrescrito por clases derivadas)
    virtual void mostrar_info() const {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Fecha de fabricacion: " << anio_fabricacion << endl;
        cout << "Precio: $" << precio << endl;
    }

    // Getters (opcional, pero útil para acceder a los atributos si fueran privados)
    string get_marca() const { return marca; }
    string get_modelo() const { return modelo; }
    int get_anio_fabricacion() const { return anio_fabricacion; }
    double get_precio() const { return precio; }
};

// Clase derivada Automóvil
class Automovil : public Vehiculo {
private:
    int numero_puertas;
    string tipo_combustible;

public:
    // Constructor de Automóvil, llama al constructor de Vehículo
    Automovil(string marca, string modelo, int anio, double precio, int puertas, string combustible)
        : Vehiculo(marca, modelo, anio, precio), numero_puertas(puertas), tipo_combustible(combustible) {
        // cout << "Constructor de Automovil llamado." << endl;
    }

    ~Automovil() {
        // cout << "Destructor de Automovil llamado." << endl;
    }

    // Sobrescribe el método mostrar_info para incluir atributos específicos
    void mostrar_info() const override {
        Vehiculo::mostrar_info(); // Llama al método de la clase base
        cout << "Numero de puertas: " << numero_puertas << endl;
        cout << "Tipo de combustible: " << tipo_combustible << endl;
    }

    // Getters específicos de Automóvil
    int get_numero_puertas() const { return numero_puertas; }
    string get_tipo_combustible() const { return tipo_combustible; }
};

// Clase derivada Motocicleta
class Motocicleta : public Vehiculo {
private:
    int cilindrada_cc; // cc para centímetros cúbicos

public:
    // Constructor de Motocicleta, llama al constructor de Vehículo
    Motocicleta(string marca, string modelo, int anio, double precio, int cilindrada)
        : Vehiculo(marca, modelo, anio, precio), cilindrada_cc(cilindrada) {
        // cout << "Constructor de Motocicleta llamado." << endl;
    }

    ~Motocicleta() {
        // cout << "Destructor de Motocicleta llamado." << endl;
    }

    // Sobrescribe el método mostrar_info para incluir atributos específicos
    void mostrar_info() const override {
        Vehiculo::mostrar_info(); // Llama al método de la clase base
        cout << "Cilindrada (cc): " << cilindrada_cc << endl;
    }

    // Getter específico de Motocicleta
    int get_cilindrada_cc() const { return cilindrada_cc; }
};

// Función principal para demostrar el uso de las clases
int main() {
    cout << "--- Informacion del Automóvil ---" << endl;
    Automovil miAuto("Toyota", "Rav4", 2023, 35000.00, 5, "Gasolina");
    miAuto.mostrar_info();
    cout << endl;

    cout << "--- Informacion de la Motocicleta ---" << endl;
    Motocicleta miMoto("Honda", "CBR600RR", 2022, 12000.00, 599);
    miMoto.mostrar_info();
    cout << endl;

    // Ejemplo de polimorfismo (opcional)
    cout << "--- Demostracion de Polimorfismo ---" << endl;
    Vehiculo* vehiculo1 = new Automovil("Ford", "Mustang", 2024, 55000.00, 2, "Gasolina Premium");
    Vehiculo* vehiculo2 = new Motocicleta("Ducati", "Panigale V4", 2023, 28000.00, 1103);

    vehiculo1->mostrar_info();
    cout << endl;
    vehiculo2->mostrar_info();
    cout << endl;

    delete vehiculo1; // Libera memoria
    delete vehiculo2; // Libera memoria

    return 0;
}