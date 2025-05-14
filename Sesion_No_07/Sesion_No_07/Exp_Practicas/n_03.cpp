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
    string direccionPostal;
    string datosFinancierosSensibles;
    string* recursoDinamicoBase; // Para demostrar la gestion de recursos (punto f)

    // Metodo protegido en la clase base para encriptar la informacion.
    // Es virtual por si futuras clases derivadas necesitaran un metodo de encriptacion base diferente.
    // Esta es una simulacion MUY basica de encriptacion.
    virtual string _encriptarInformacionInterna(const string& dato) const {
        if (dato.empty()) {
            return "";
        }
        string datoEncriptado = dato;
        reverse(datoEncriptado.begin(), datoEncriptado.end()); // Simulacion: revertir el string
        cout << "  (Cliente INFO: Encriptacion interna base ejecutada sobre dato)" << endl;
        return datoEncriptado;
    }

public:
    // Constructor para la clase Cliente
    Cliente(string nombre, string id, string direccion, string datosFin)
        : nombreCompleto(nombre), idCliente(id), direccionPostal(direccion), datosFinancierosSensibles(datosFin) {
        recursoDinamicoBase = new string("Recurso dinamico de la clase Cliente para " + nombreCompleto); // Asigna recurso
        cout << "Constructor BASE Cliente: Objeto creado para " << nombreCompleto << ". Recurso base asignado." << endl;
    }

    // Destructor virtual para la clase Cliente.
    // Es buena practica que sea virtual si la clase sera heredada y se usan punteros a la base.
    // Libera recursos de la clase base (parte de f).
    virtual ~Cliente() {
        delete recursoDinamicoBase; // Libera el recurso asignado por Cliente
        recursoDinamicoBase = nullptr; // Buena practica despues de delete
        cout << "Destructor BASE Cliente: Objeto destruido para " << nombreCompleto << ". Recurso base liberado." << endl;
    }

    // Metodo para mostrar informacion basica (no sensible)
    void mostrarInformacionBasica() const {
        cout << "--- Informacion Basica Cliente ---" << endl;
        cout << "Nombre: " << nombreCompleto << endl;
        cout << "ID Cliente: " << idCliente << endl;
        cout << "Direccion: " << direccionPostal << endl;
        if (recursoDinamicoBase) {
            // cout << "  Recurso Base: " << *recursoDinamicoBase << endl; // Solo para depuracion
        }
    }

    // Metodo para actualizar los datos financieros (ejemplo para tener algo que encriptar)
    void actualizarDatosFinancieros(const string& nuevosDatos) {
        this->datosFinancierosSensibles = nuevosDatos;
        cout << "Datos financieros de " << nombreCompleto << " actualizados." << endl;
    }
};

// --- Clase Derivada: ClienteSeguro ---
class ClienteSeguro : public Cliente { // Herencia publica
private:
    string datosFinancierosAlmacenadosEncriptados;
    string tokenDeAutenticacion;
    string* recursoDinamicoDerivado; // Para demostrar la gestion de recursos (punto f)

public:
    // e) Constructor en la clase derivada que llame al constructor de la clase base
    //    y que inicialice los atributos adicionales de la clase derivada.
    ClienteSeguro(string nombre, string id, string direccion, string datosFin, string token)
        : Cliente(nombre, id, direccion, datosFin), // Llamada al constructor de la clase base
          datosFinancierosAlmacenadosEncriptados(""), // Inicializa atributo adicional
          tokenDeAutenticacion(token) {               // Inicializa atributo adicional
        recursoDinamicoDerivado = new string("Recurso dinamico de la clase ClienteSeguro para " + nombreCompleto); // Asigna recurso derivado
        cout << "  -> Constructor DERIVADO ClienteSeguro: Objeto creado para " << nombreCompleto << ". Recurso derivado asignado." << endl;
    }

    // f) Destructor en la clase derivada que libere los recursos utilizados por la clase derivada
    //    y por la clase base (la parte de la clase base se maneja por su propio destructor).
    ~ClienteSeguro() override {
        delete recursoDinamicoDerivado; // Libera el recurso asignado por ClienteSeguro
        recursoDinamicoDerivado = nullptr; // Buena practica
        cout << "  -> Destructor DERIVADO ClienteSeguro: Objeto destruido para " << nombreCompleto << ". Recurso derivado liberado." << endl;
        // El destructor de Cliente se llamara automaticamente despues de este.
    }

    // Metodo para encriptar y almacenar la informacion financiera utilizando el metodo protegido de la base
    void procesarYEncriptarDatosFinancieros() {
        if (!datosFinancierosSensibles.empty()) {
            datosFinancierosAlmacenadosEncriptados = _encriptarInformacionInterna(datosFinancierosSensibles);
            cout << "  ClienteSeguro (" << nombreCompleto << "): Datos financieros sensibles procesados y encriptados usando metodo base." << endl;
        } else {
            cout << "  ClienteSeguro (" << nombreCompleto << "): No hay datos financieros sensibles para procesar y encriptar." << endl;
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
        mostrarInformacionBasica();
        cout << "Estado Datos Financieros Encriptados (Almacenados): "
            << (datosFinancierosAlmacenadosEncriptados.empty() ? "No procesados/encriptados aun" : "Procesados y Encriptados") << endl;
        if (!datosFinancierosAlmacenadosEncriptados.empty()) {
            cout << "  (Representacion encriptada almacenada: " << datosFinancierosAlmacenadosEncriptados << ")" << endl;
        }
        if (recursoDinamicoDerivado) {
            // cout << "  Recurso Derivado: " << *recursoDinamicoDerivado << endl; // Solo para depuracion
        }
    }
};


int main() {
    cout << "--- DEMOSTRACION PUNTOS (e) y (f) ---" << endl;

    cout << "\n1. Creando un objeto ClienteSeguro:" << endl;
    ClienteSeguro* clienteS_ptr = new ClienteSeguro("Laura Palmer", "LP456", "Twin Peaks Main St", "Diario secreto", "tokenLauraSecure");

    cout << "\n2. Mostrando informacion segura:" << endl;
    clienteS_ptr->mostrarInformacionSegura();

    cout << "\n3. Procesando y encriptando datos:" << endl;
    clienteS_ptr->procesarYEncriptarDatosFinancieros();
    clienteS_ptr->mostrarInformacionSegura();

    cout << "\n4. Eliminando el objeto ClienteSeguro (probando destructores):" << endl;
    delete clienteS_ptr; // Esto llamara a ~ClienteSeguro() y luego a ~Cliente()
    clienteS_ptr = nullptr;

    cout << "\n5. Creando otro objeto ClienteSeguro en el stack (para ver destruccion automatica):" << endl;
    {
        ClienteSeguro clienteS_stack("Dale Cooper", "DC001", "Great Northern Hotel", "Informes del FBI", "tokenCooperSpecial");
        clienteS_stack.mostrarInformacionSegura();
        cout << "Saliendo del bloque donde se creo clienteS_stack..." << endl;
    } // clienteS_stack se destruye aqui automaticamente

    cout << "\n6. Fin de la demostracion." << endl;

    return 0;
}
