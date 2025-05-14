#include <iostream>
#include <string>
#include <algorithm> // Necesario para std::reverse (simulacion de encriptacion)

// Usaremos el espacio de nombres std para simplificar.
using namespace std;

// --- Clase Base: Cliente ---
class Cliente {
// c) Atributos 'protected' para que la clase derivada pueda heredarlos y acceder a ellos.
protected:
    string nombreCompleto;
    string idCliente;
    string direccionPostal;
    string datosFinancierosSensibles;

    // d) Metodo protegido en la clase base para encriptar la informacion.
    // Te informo: Lo he hecho virtual por si futuras clases derivadas necesitaran
    // un metodo de encriptacion base diferente.
    // Esta es una simulacion MUY basica de encriptacion.
    virtual string _encriptarInformacionInterna(const string& dato) const {
        if (dato.empty()) {
            return "";
        }
        string datoEncriptado = dato;
        reverse(datoEncriptado.begin(), datoEncriptado.end()); // Simulacion: revertir el string
        // En un sistema real, aqui se usarian algoritmos criptograficos robustos.
        cout << "  (Cliente INFO: Encriptacion interna base ejecutada sobre dato)" << endl;
        return datoEncriptado;
    }

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

    // Metodo para actualizar los datos financieros (ejemplo para tener algo que encriptar)
    void actualizarDatosFinancieros(const string& nuevosDatos) {
        this->datosFinancierosSensibles = nuevosDatos;
        cout << "Datos financieros de " << nombreCompleto << " actualizados." << endl;
    }
};

// --- Clase Derivada: ClienteSeguro ---
class ClienteSeguro : public Cliente { // Herencia publica
private:
    string datosFinancierosAlmacenadosEncriptados; // Almacenara el resultado de la encriptacion
    string tokenDeAutenticacion;

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

    // Metodo para encriptar y almacenar la informacion financiera utilizando el metodo protegido de la base
    void procesarYEncriptarDatosFinancieros() {
        if (!datosFinancierosSensibles.empty()) {
            // Llama al metodo protegido _encriptarInformacionInterna de la clase Cliente
            datosFinancierosAlmacenadosEncriptados = _encriptarInformacionInterna(datosFinancierosSensibles);
            cout << "  ClienteSeguro (" << nombreCompleto << "): Datos financieros sensibles procesados y encriptados usando metodo base." << endl;
            // Opcional: Limpiar la version original no encriptada en la clase base por seguridad
            // datosFinancierosSensibles = "[DATOS BASE ENCRIPTADOS Y PROCESADOS]";
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
        mostrarInformacionBasica(); // Muestra la info de la clase base
        cout << "Estado Datos Financieros Encriptados (Almacenados): "
            << (datosFinancierosAlmacenadosEncriptados.empty() ? "No procesados/encriptados aun" : "Procesados y Encriptados") << endl;
        if (!datosFinancierosAlmacenadosEncriptados.empty()) {
             // En un sistema real, no se mostraria el dato encriptado directamente.
            cout << "  (Representacion encriptada almacenada: " << datosFinancierosAlmacenadosEncriptados << ")" << endl;
        }
         // Mostrar el dato original para comparacion (solo para fines de demostracion)
        cout << "  (Dato financiero sensible original en Base: " << datosFinancierosSensibles << ")" << endl;
    }
};

int main() {
    cout << "--- DEMOSTRACION PUNTOS (c) y (d) ---" << endl;

    cout << "\n1. Creando un objeto ClienteSeguro:" << endl;
    ClienteSeguro clienteS1("Pedro Pascal", "PP007", "Calle Luna 12", "Detalles bancarios confidenciales", "tokenPedroSecure");

    cout << "\n2. Mostrando informacion segura (antes de procesar/encriptar):" << endl;
    clienteS1.mostrarInformacionSegura();

    cout << "\n3. Procesando y encriptando datos financieros (usando metodo protegido de la base):" << endl;
    clienteS1.procesarYEncriptarDatosFinancieros();

    cout << "\n4. Mostrando informacion segura (despues de procesar/encriptar):" << endl;
    clienteS1.mostrarInformacionSegura();

    cout << "\n5. Actualizando datos financieros en la base (para probar de nuevo):" << endl;
    clienteS1.actualizarDatosFinancieros("Nueva info super secreta de Pedro");
    clienteS1.procesarYEncriptarDatosFinancieros();
    clienteS1.mostrarInformacionSegura();


    cout << "\n6. Verificando autenticidad:" << endl;
    clienteS1.verificarAutenticidad("tokenIncorrecto");
    clienteS1.verificarAutenticidad("tokenPedroSecure");

    cout << "\n7. Fin de la demostracion (los destructores se llamaran al salir del main):" << endl;

    return 0;
}