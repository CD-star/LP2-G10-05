#include <iostream>
#include <string>
#include <algorithm> // Necesario para std::reverse (simulacion de encriptacion)

// Usaremos el espacio de nombres std para simplificar.
using namespace std;

// --- Clase Base: Cliente ---
class Cliente {
// Atributos 'protected' para que la clase derivada pueda heredarlos y acceder a ellos.
protected:
    string nombreCompleto;
    string idCliente;
    string direccionPostal; // Ejemplo de informacion personal
    string datosFinancierosSensibles; // Ejemplo de informacion financiera a encriptar

public:
    // Constructor para la clase Cliente
    Cliente(string nombre, string id, string direccion, string datosFin)
        : nombreCompleto(nombre), idCliente(id), direccionPostal(direccion), datosFinancierosSensibles(datosFin) {
        cout << "Constructor BASE Cliente: Objeto creado para " << nombreCompleto << endl;
    }

    // Destructor virtual para la clase Cliente.
    // Es buena practica que sea virtual si la clase sera heredada y se usan punteros a la base.
    virtual ~Cliente() {
        cout << "Destructor BASE Cliente: Objeto destruido para " << nombreCompleto << endl;
    }

    // Metodo para mostrar informacion basica (no sensible)
    void mostrarInformacionBasica() const {
        cout << "--- Informacion Basica Cliente ---" << endl;
        cout << "Nombre: " << nombreCompleto << endl;
        cout << "ID Cliente: " << idCliente << endl;
        cout << "Direccion: " << direccionPostal << endl;
    }
};

// --- Clase Derivada: ClienteSeguro ---
class ClienteSeguro : public Cliente { // Herencia publica
private:
    string datosFinancierosEncriptados;
    string tokenDeAutenticacion; // Para simular la verificacion de autenticidad

public:
    // Constructor para ClienteSeguro
    ClienteSeguro(string nombre, string id, string direccion, string datosFin, string token)
        : Cliente(nombre, id, direccion, datosFin), // Llama al constructor de la clase base
        tokenDeAutenticacion(token) {
        cout << "  -> Constructor DERIVADO ClienteSeguro: Objeto creado para " << nombreCompleto << endl;
    }

    // Destructor para ClienteSeguro
    ~ClienteSeguro() override {
        cout << "  -> Destructor DERIVADO ClienteSeguro: Objeto destruido para " << nombreCompleto << endl;
    }

    // Metodo para encriptar la informacion financiera
    // Te informo: Esta es una simulacion MUY basica de encriptacion.
    void encriptarDatosFinancieros() {
        if (!datosFinancierosSensibles.empty()) {
            // Simulacion: revertir el string
            datosFinancierosEncriptados = datosFinancierosSensibles;
            reverse(datosFinancierosEncriptados.begin(), datosFinancierosEncriptados.end());
            cout << "  ClienteSeguro (" << nombreCompleto << "): Datos financieros encriptados." << endl;
            // Opcional: Limpiar la version original no encriptada por seguridad
            // datosFinancierosSensibles = "[DATOS ENCRIPTADOS]";
        } else {
            cout << "  ClienteSeguro (" << nombreCompleto << "): No hay datos financieros para encriptar." << endl;
        }
    }

    // Metodo para verificar la autenticidad del cliente
    // Te informo: Esta es una simulacion MUY basica de verificacion.
    bool verificarAutenticidad(const string& tokenIngresado) const {
        cout << "  ClienteSeguro (" << nombreCompleto << "): Verificando autenticidad con token..." << endl;
        if (tokenIngresado == tokenDeAutenticacion && !tokenDeAutenticacion.empty()) {
            cout << "  ClienteSeguro (" << nombreCompleto << "): Autenticacion EXITOSA." << endl;
            return true;
        } else {
            cout << "  ClienteSeguro (" << nombreCompleto << "): Autenticacion FALLIDA." << endl;
            return false;
        }
    }

    // Metodo para mostrar la informacion, incluyendo el estado de los datos encriptados
    void mostrarInformacionSegura() const {
        mostrarInformacionBasica(); // Muestra la info de la clase base
        cout << "Estado Datos Financieros: "
            << (datosFinancierosEncriptados.empty() ? "No encriptados o sin datos originales" : "Encriptados") << endl;
        if (!datosFinancierosEncriptados.empty()) {
             // En un sistema real, no se mostraria el dato encriptado directamente.
            cout << "  (Representacion encriptada ejemplo: " << datosFinancierosEncriptados << ")" << endl;
        }
    }
};

int main() {
    cout << "--- DEMOSTRACION PUNTOS (a) y (b) ---" << endl;

    cout << "\n1. Creando un objeto ClienteSeguro:" << endl;
    ClienteSeguro cliente1("Maria Lopez", "ML001", "Av. Principal 456", "Numero de tarjeta 1234-5678-9012-3456", "tokenMaria123");

    cout << "\n2. Mostrando informacion basica (heredada):" << endl;
    cliente1.mostrarInformacionBasica();

    cout << "\n3. Mostrando informacion desde ClienteSeguro (antes de encriptar):" << endl;
    cliente1.mostrarInformacionSegura();

    cout << "\n4. Encriptando datos financieros:" << endl;
    cliente1.encriptarDatosFinancieros();

    cout << "\n5. Mostrando informacion desde ClienteSeguro (despues de encriptar):" << endl;
    cliente1.mostrarInformacionSegura();

    cout << "\n6. Verificando autenticidad:" << endl;
    cliente1.verificarAutenticidad("tokenIncorrecto");
    cliente1.verificarAutenticidad("tokenMaria123");

    cout << "\n7. Fin de la demostracion (los destructores se llamaran al salir del main):" << endl;

    return 0;
}
