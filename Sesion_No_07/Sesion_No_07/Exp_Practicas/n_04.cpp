#include <iostream>
#include <string>
#include <algorithm> // Necesario para std::reverse

// Usaremos el espacio de nombres std para simplificar.
using namespace std;

// --- Clase Base: Cliente (para puntos a, b, c, d, e, f, g) ---
class Cliente {
protected:
    string nombreCompleto;
    string idCliente;
    string direccionPostal;
    string datosFinancierosSensibles;
    string* recursoDinamicoBase; // Para demostrar gestion de recursos

    // d) Metodo protegido en la clase base para encriptar
    virtual string _encriptarInformacionInterna(const string& dato) const {
        if (dato.empty()) return "";
        string datoEncriptado = dato;
        reverse(datoEncriptado.begin(), datoEncriptado.end());
        cout << "  (Cliente INFO: Encriptacion interna base ejecutada)" << endl;
        return datoEncriptado;
    }

public:
    // a) Atributos para informacion personal y financiera
    // c) Atributos definidos como protegidos
    Cliente(string nombre, string id, string direccion, string datosFin)
        : nombreCompleto(nombre), idCliente(id), direccionPostal(direccion), datosFinancierosSensibles(datosFin) {
        recursoDinamicoBase = new string("Recurso base para " + nombreCompleto);
        cout << "Constructor BASE Cliente: " << nombreCompleto << ". Recurso base asignado." << endl;
    }

    // f) Parte del destructor que libera recursos de la clase base
    virtual ~Cliente() {
        delete recursoDinamicoBase;
        recursoDinamicoBase = nullptr;
        cout << "Destructor BASE Cliente: " << nombreCompleto << ". Recurso base liberado." << endl;
    }

    // Metodo publico en la base
    void mostrarInformacionBasica() const {
        cout << "--- Informacion Basica Cliente (desde Cliente) ---" << endl;
        cout << "Nombre: " << nombreCompleto << endl;
        cout << "ID Cliente: " << idCliente << endl;
    }
    
    string getNombre() const { return nombreCompleto; }
};

// --- Clase Derivada: ClienteSeguro (para puntos b, e, f, g) ---
// g) Utilizar la herencia publica
class ClienteSeguro : public Cliente {
private:
    string datosFinancierosAlmacenadosEncriptados;
    string tokenDeAutenticacion;
    string* recursoDinamicoDerivado; // Para demostrar gestion de recursos

public:
    // e) Constructor en la clase derivada que llama al constructor de la clase base
    //    y que inicialice los atributos adicionales de la clase derivada.
    ClienteSeguro(string nombre, string id, string direccion, string datosFin, string token)
        : Cliente(nombre, id, direccion, datosFin), // Llamada al constructor base
          datosFinancierosAlmacenadosEncriptados(""), // Inicializa atributo adicional
          tokenDeAutenticacion(token) {               // Inicializa atributo adicional
        recursoDinamicoDerivado = new string("Recurso derivado para " + nombreCompleto);
        cout << "  -> Constructor DERIVADO ClienteSeguro: " << this->getNombre() << ". Recurso derivado asignado." << endl;
    }

    // f) Destructor en la clase derivada que libere los recursos utilizados por la clase derivada
    //    (los de la base se liberan por el destructor base).
    ~ClienteSeguro() override {
        delete recursoDinamicoDerivado;
        recursoDinamicoDerivado = nullptr;
        cout << "  -> Destructor DERIVADO ClienteSeguro: " << nombreCompleto << ". Recurso derivado liberado." << endl;
    }

    // b) Metodos para encriptar la informacion y verificar autenticidad
    void procesarYEncriptarDatosFinancieros() {
        if (!datosFinancierosSensibles.empty()) {
            datosFinancierosAlmacenadosEncriptados = _encriptarInformacionInterna(datosFinancierosSensibles);
            cout << "  ClienteSeguro (" << nombreCompleto << "): Datos financieros procesados." << endl;
        } else {
            cout << "  ClienteSeguro (" << nombreCompleto << "): No hay datos financieros para procesar." << endl;
        }
    }

    bool verificarAutenticidad(const string& tokenIngresado) const {
        cout << "  ClienteSeguro (" << nombreCompleto << "): Verificando autenticidad..." << endl;
        bool autenticado = (tokenIngresado == tokenDeAutenticacion && !tokenDeAutenticacion.empty());
        cout << "  ClienteSeguro (" << nombreCompleto << "): Autenticacion " << (autenticado ? "EXITOSA." : "FALLIDA.") << endl;
        return autenticado;
    }

    void mostrarInformacionSeguraDetallada() const {
        mostrarInformacionBasica(); // Metodo publico de la base, sigue publico aqui
        cout << "--- Detalles Adicionales ClienteSeguro ---" << endl;
        cout << "Token: " << tokenDeAutenticacion << endl;
        cout << "Finanzas Encriptadas: " << (datosFinancierosAlmacenadosEncriptados.empty() ? "N/A" : datosFinancierosAlmacenadosEncriptados) << endl;
        cout << "Nombre (accedido via protected): " << nombreCompleto << endl; // Acceso a miembro protected de la base
    }
};


// --- EJEMPLOS PARA HERENCIA PROTEGIDA (h) Y PRIVADA (i) ---

// Clase base para los ejemplos de herencia protegida y privada
class BaseParaHerenciaEjemplos {
public:
    string miembroPublicoBase;
    void metodoPublicoBase() {
        cout << "  BaseParaHerenciaEjemplos: Metodo Publico Base ejecutado." << endl;
    }

protected:
    string miembroProtegidoBase;
    void metodoProtegidoBase() {
        cout << "  BaseParaHerenciaEjemplos: Metodo Protegido Base ejecutado." << endl;
    }

private:
    string miembroPrivadoBase;

public:
    BaseParaHerenciaEjemplos() :
        miembroPublicoBase("Dato Publico en Base"),
        miembroProtegidoBase("Dato Protegido en Base"),
        miembroPrivadoBase("Dato Privado en Base") {
        // cout << "Constructor BaseParaHerenciaEjemplos." << endl;
        }
    ~BaseParaHerenciaEjemplos(){
        // cout << "Destructor BaseParaHerenciaEjemplos." << endl;
    }

    void mostrarMiembroPrivadoDesdeBase() { // Metodo para acceder al privado de la base
        cout << "  BaseParaHerenciaEjemplos mostrando su miembro privado: " << miembroPrivadoBase << endl;
    }
};

// h) Ejemplo de Herencia Protegida
class DerivadaProtegida : protected BaseParaHerenciaEjemplos {
public:
    DerivadaProtegida() {
        cout << "Constructor DerivadaProtegida." << endl;
    }
    ~DerivadaProtegida() {
        cout << "Destructor DerivadaProtegida." << endl;
    }

    void accederMiembrosHeredadosEnDerivadaProtegida() {
        cout << "--- Desde DerivadaProtegida (Herencia Protected) ---" << endl;
        // Miembros publicos de BaseParaHerenciaEjemplos se vuelven protected aqui
        cout << "Accediendo a miembroPublicoBase (ahora protected): " << miembroPublicoBase << endl;
        metodoPublicoBase(); // OK, ahora es protected

        // Miembros protegidos de BaseParaHerenciaEjemplos siguen siendo protected aqui
        cout << "Accediendo a miembroProtegidoBase (sigue protected): " << miembroProtegidoBase << endl;
        metodoProtegidoBase(); // OK, sigue protected

        // Miembros privados de BaseParaHerenciaEjemplos NO son accesibles
        // cout << miembroPrivadoBase; // ERROR DE COMPILACION
        // Para ver el miembro privado de la base, la base necesita un metodo publico/protegido
        // mostrarMiembroPrivadoDesdeBase(); // OK si BaseParaHerenciaEjemplos::mostrarMiembroPrivadoDesdeBase fuera protected
                                        // pero como es public en la base, se vuelve protected aqui.
        BaseParaHerenciaEjemplos::mostrarMiembroPrivadoDesdeBase(); // Si se quiere llamar indirectamente un metodo publico de la base que se volvio protected
    }
};

class NietaDeDerivadaProtegida : public DerivadaProtegida {
public:
    NietaDeDerivadaProtegida() {
        cout << "Constructor NietaDeDerivadaProtegida." << endl;
    }
    ~NietaDeDerivadaProtegida() {
        cout << "Destructor NietaDeDerivadaProtegida." << endl;
    }
    void accederMiembrosHeredadosEnNieta() {
        cout << "--- Desde NietaDeDerivadaProtegida (hereda de DerivadaProtegida) ---" << endl;
        // miembroPublicoBase y metodoPublicoBase() son protected en DerivadaProtegida,
        // por lo tanto, son accesibles y siguen siendo protected aqui.
        cout << "Accediendo a miembroPublicoBase (via DerivadaProtegida, es protected): " << miembroPublicoBase << endl;
        metodoPublicoBase();

        // miembroProtegidoBase y metodoProtegidoBase() son protected en DerivadaProtegida,
        // por lo tanto, son accesibles y siguen siendo protected aqui.
        cout << "Accediendo a miembroProtegidoBase (via DerivadaProtegida, es protected): " << miembroProtegidoBase << endl;
        metodoProtegidoBase();
    }
};


// i) Ejemplo de Herencia Privada
class DerivadaPrivada : private BaseParaHerenciaEjemplos {
public:
    DerivadaPrivada() {
        cout << "Constructor DerivadaPrivada." << endl;
    }
    ~DerivadaPrivada() {
        cout << "Destructor DerivadaPrivada." << endl;
    }

    void accederMiembrosHeredadosEnDerivadaPrivada() {
        cout << "--- Desde DerivadaPrivada (Herencia Private) ---" << endl;
        // Miembros publicos de BaseParaHerenciaEjemplos se vuelven private aqui
        cout << "Accediendo a miembroPublicoBase (ahora private): " << miembroPublicoBase << endl;
        metodoPublicoBase(); // OK, ahora es private

        // Miembros protegidos de BaseParaHerenciaEjemplos se vuelven private aqui
        cout << "Accediendo a miembroProtegidoBase (ahora private): " << miembroProtegidoBase << endl;
        metodoProtegidoBase(); // OK, ahora es private

        // Miembros privados de BaseParaHerenciaEjemplos NO son accesibles
        // cout << miembroPrivadoBase; // ERROR DE COMPILACION
        BaseParaHerenciaEjemplos::mostrarMiembroPrivadoDesdeBase(); // Si se quiere llamar un metodo publico de la base que se volvio private
    }
};

class NietaDeDerivadaPrivada : public DerivadaPrivada {
public:
    NietaDeDerivadaPrivada() {
        cout << "Constructor NietaDeDerivadaPrivada." << endl;
    }
    ~NietaDeDerivadaPrivada() {
        cout << "Destructor NietaDeDerivadaPrivada." << endl;
    }
    void accederMiembrosHeredadosEnNieta() {
        cout << "--- Desde NietaDeDerivadaPrivada (hereda de DerivadaPrivada) ---" << endl;
        // Todos los miembros heredados de BaseParaHerenciaEjemplos son private en DerivadaPrivada.
        // Por lo tanto, NO son accesibles por NietaDeDerivadaPrivada.
        // cout << miembroPublicoBase; // ERROR DE COMPILACION
        // metodoPublicoBase();       // ERROR DE COMPILACION
        cout << "No se puede acceder a los miembros de BaseParaHerenciaEjemplos desde la nieta aqui (se volvieron privados en DerivadaPrivada)." << endl;
    }
};


// --- Funcion main para demostrar todos los puntos ---
int main() {
    cout << "****** INICIO EXPERIENCIAS DE PRACTICA ******" << endl;

    cout << "\n--- g) Demostracion de Herencia Publica con Cliente y ClienteSeguro ---" << endl;
    ClienteSeguro* cs1 = new ClienteSeguro("Carlos Publico", "CPUB001", "Calle Publica 1", "Datos Financieros Publicos", "tokenPUB1");
    cout << "\nLlamando a metodo publico de la base desde objeto ClienteSeguro:" << endl;
    cs1->mostrarInformacionBasica(); // OK, mostrarInformacionBasica() es public en Cliente y sigue public en ClienteSeguro.
    
    cout << "\nLlamando a metodo de ClienteSeguro que accede a miembros heredados (public y protected):" << endl;
    cs1->mostrarInformacionSeguraDetallada();
    cs1->procesarYEncriptarDatosFinancieros(); // ClienteSeguro usa el _encriptarInformacionInterna (protected) de Cliente
    cs1->verificarAutenticidad("tokenPUB1");

    // Desde main, no podemos acceder directamente a miembros protected de Cliente a traves de cs1
    // cout << cs1->nombreCompleto; // ERROR: nombreCompleto es protected
    // cs1->_encriptarInformacionInterna("test"); // ERROR: _encriptarInformacionInterna es protected
    
    delete cs1; // Probar destructores
    cs1 = nullptr;
    cout << "-------------------------------------------------\n";


    cout << "\n--- h) Demostracion de Herencia Protegida ---" << endl;
    DerivadaProtegida dp1;
    cout << "\nIntentando acceder a miembros desde DerivadaProtegida (internamente):" << endl;
    dp1.accederMiembrosHeredadosEnDerivadaProtegida();
    
    // Desde main, no podemos acceder a los metodos que eran publicos en la base y ahora son protected en DerivadaProtegida
    // dp1.metodoPublicoBase(); // ERROR DE COMPILACION: 'metodoPublicoBase' is a protected member of 'BaseParaHerenciaEjemplos'
    // cout << dp1.miembroPublicoBase; // ERROR DE COMPILACION
    
    cout << "\nCreando NietaDeDerivadaProtegida (para ver acceso desde una clase mas derivada):" << endl;
    NietaDeDerivadaProtegida ndp1;
    ndp1.accederMiembrosHeredadosEnNieta(); // OK, la nieta puede acceder a lo que es protected en su padre (DerivadaProtegida)
    cout << "-------------------------------------------------\n";


    cout << "\n--- i) Demostracion de Herencia Privada ---" << endl;
    DerivadaPrivada dpr1;
    cout << "\nIntentando acceder a miembros desde DerivadaPrivada (internamente):" << endl;
    dpr1.accederMiembrosHeredadosEnDerivadaPrivada();

    // Desde main, no podemos acceder a los metodos que eran publicos/protegidos en la base y ahora son privados en DerivadaPrivada
    // dpr1.metodoPublicoBase(); // ERROR DE COMPILACION: 'metodoPublicoBase' is a private member of 'BaseParaHerenciaEjemplos'
    // cout << dpr1.miembroPublicoBase; // ERROR DE COMPILACION

    cout << "\nCreando NietaDeDerivadaPrivada (para ver que la herencia 'se detiene'):" << endl;
    NietaDeDerivadaPrivada ndpr1;
    ndpr1.accederMiembrosHeredadosEnNieta(); // Mostrara que no puede acceder a los miembros de BaseParaHerenciaEjemplos
    cout << "-------------------------------------------------\n";

    cout << "\nAl finalizar main, se llamaran a los destructores de los objetos restantes en el stack..." << endl;
    // Destructores de dp1, ndp1, dpr1, ndpr1 se llamaran aqui si son objetos locales en stack.
    // cs1 fue eliminado con delete.

    return 0;
}