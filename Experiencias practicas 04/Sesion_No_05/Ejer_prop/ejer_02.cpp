#include <iostream>
using namespace std;

class FechaRegistro {
private:
    int dia, mes, anio;
public:
    FechaRegistro(int d, int m, int a) : dia(d), mes(m), anio(a) {}
    void mostrar() const {
        cout << dia << "/" << mes << "/" << anio;
    }
};

class Direccion {
private:
    string calle, ciudad;
public:
    Direccion(string c, string ci) : calle(c), ciudad(ci) {}
    void mostrar() const {
        cout << calle << ", " << ciudad;
    }
};

class Cliente {
private:
    string nombre;
    FechaRegistro fecha;
    Direccion direccion;
public:
    Cliente(string nom, FechaRegistro f, Direccion d)
        : nombre(nom), fecha(f), direccion(d) {}

    void mostrar() const {
        cout << "Cliente: " << nombre << endl;
        cout << "Direccion: ";
        direccion.mostrar();
        cout << "\nFecha de registro: ";
        fecha.mostrar();
        cout << endl;
    }
};

int main() {
    FechaRegistro f(29, 4, 2025);
    Direccion d("Av. Siempre Viva 742", "Arequipa");
    Cliente c("Joaquin", f, d);
    c.mostrar();
    return 0;
}