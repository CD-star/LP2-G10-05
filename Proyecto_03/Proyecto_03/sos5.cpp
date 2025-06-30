#include <iostream> // Para entrada/salida como cout y cin
#include <string>   // Para usar el tipo de dato string
#include <vector>   // Para usar vectores (listas dinámicas)
#include <map>      // Para usar mapas (colecciones clave-valor)
#include <limits>   // Para numeric_limits (limpiar buffer de entrada)

using namespace std;

// --- Clase Base: Vehiculo ---
// Es una clase abstracta porque tiene métodos virtuales puros (= 0)
class Vehiculo {
public:
    string placa;
    string tipoVehiculo; // "Automovil" o "Moto"

    // Constructor de la clase base
    Vehiculo(const string& _placa, const string& _tipoVehiculo)
        : placa(_placa), tipoVehiculo(_tipoVehiculo) {}

    // Destructor virtual: importante para la herencia
    virtual ~Vehiculo() {}

    // Método virtual puro: cada tipo de vehículo lo implementará a su manera
    virtual void mostrarInformacion() const = 0;
    
    // Método virtual puro: cada tipo de vehículo calculará su tarifa (simplificado aquí)
    virtual void calcularTarifa() const = 0;
};

// --- Clase Derivada: Automovil ---
class Automovil : public Vehiculo {
public:
    // Constructor de Automovil llama al constructor de Vehiculo
    Automovil(const string& _placa)
        : Vehiculo(_placa, "Automovil") {}

    // Implementación del método virtual mostrarInformacion para Automovil
    void mostrarInformacion() const override {
        cout << "  - Placa: " << placa << ", Tipo: " << tipoVehiculo << endl;
    }

    // Implementación del método virtual calcularTarifa (muy simplificado)
    void calcularTarifa() const override {
        cout << "  - Tarifa calculada para Automovil." << endl;
    }
};

// --- Clase Derivada: Moto ---
class Moto : public Vehiculo {
public:
    // Constructor de Moto llama al constructor de Vehiculo
    Moto(const string& _placa)
        : Vehiculo(_placa, "Moto") {}

    // Implementación del método virtual mostrarInformacion para Moto
    void mostrarInformacion() const override {
        cout << "  - Placa: " << placa << ", Tipo: " << tipoVehiculo << endl;
    }

    // Implementación del método virtual calcularTarifa (muy simplificado)
    void calcularTarifa() const override {
        cout << "  - Tarifa calculada para Moto." << endl;
    }
};

// --- Clase: Parqueadero (Representa un espacio de estacionamiento) ---
class Parqueadero {
public:
    string codigo;           // Ej: "A1", "M2", "X3"
    string tipoPermitido;    // "Automovil", "Moto", "Mixto"
    bool estaOcupado;
    bool estaBloqueado;
    Vehiculo* vehiculoEstacionado; // Puntero al vehículo que lo ocupa (para simplificar)

    Parqueadero(const string& _codigo, const string& _tipoPermitido)
        : codigo(_codigo), tipoPermitido(_tipoPermitido), estaOcupado(false),
          estaBloqueado(false), vehiculoEstacionado(nullptr) {}

    // Método para ocupar el parqueadero
    void ocupar(Vehiculo* vehiculo) {
        if (!estaOcupado && !estaBloqueado) {
            estaOcupado = true;
            vehiculoEstacionado = vehiculo; // Asignar el vehículo
            cout << "  -> Parqueadero " << codigo << " ocupado por " << vehiculo->placa << endl;
        } else {
            cout << "  -> ERROR: El parqueadero " << codigo << " no esta disponible o esta bloqueado." << endl;
        }
    }

    // Método para desocupar el parqueadero
    void desocupar() {
        if (estaOcupado) {
            cout << "  -> Vehiculo " << vehiculoEstacionado->placa << " saliendo del parqueadero " << codigo << "." << endl;
            delete vehiculoEstacionado; // Liberar la memoria del vehículo (¡importante!)
            vehiculoEstacionado = nullptr;
            estaOcupado = false;
        } else {
            cout << "  -> ERROR: El parqueadero " << codigo << " ya esta vacio." << endl;
        }
    }

    // Método para bloquear el parqueadero
    void bloquear() {
        if (!estaOcupado) { // Solo se puede bloquear si no está ocupado
            estaBloqueado = true;
            cout << "  -> Parqueadero " << codigo << " bloqueado." << endl;
        } else {
            cout << "  -> ERROR: No se puede bloquear el parqueadero " << codigo << " mientras esta ocupado." << endl;
        }
    }

    // Método para habilitar el parqueadero
    void habilitar() {
        estaBloqueado = false;
        cout << "  -> Parqueadero " << codigo << " habilitado." << endl;
    }

    // Método para mostrar el estado actual del parqueadero
    void mostrarEstado() const {
        cout << "Codigo: " << codigo
             << ", Tipo: " << tipoPermitido
             << ", Ocupado: " << (estaOcupado ? "Si" : "No")
             << ", Bloqueado: " << (estaBloqueado ? "Si" : "No");
        if (estaOcupado && vehiculoEstacionado) {
            cout << ", Vehiculo: ";
            vehiculoEstacionado->mostrarInformacion(); // Usa el polimorfismo para mostrar info del vehiculo
        } else {
            cout << endl; // Si no hay vehículo, solo un salto de línea
        }
    }
};

// --- Clase Principal: SistemaParqueadero ---
class SistemaParqueadero {
public:
    map<string, Parqueadero> espaciosParqueadero; // Colección de parqueaderos
    map<string, Vehiculo*> vehiculosEstacionados; // Mapa para saber qué vehículos están dentro por placa

    // Constructor: Inicializa algunos parqueaderos
    SistemaParqueadero() {
        // Configuramos algunos parqueaderos por defecto para simplificar
        cout << "Configurando parqueaderos iniciales..." << endl;
        espaciosParqueadero.emplace("A1", Parqueadero("A1", "Automovil"));
        espaciosParqueadero.emplace("A2", Parqueadero("A2", "Automovil"));
        espaciosParqueadero.emplace("M1", Parqueadero("M1", "Moto"));
        espaciosParqueadero.emplace("M2", Parqueadero("M2", "Moto"));
        espaciosParqueadero.emplace("X1", Parqueadero("X1", "Mixto")); // ¡Aquí está el parqueadero mixto!
        espaciosParqueadero.emplace("X2", Parqueadero("X2", "Mixto"));
        cout << "Parqueaderos configurados: A1, A2 (Automovil), M1, M2 (Moto), X1, X2 (Mixto)." << endl;
    }

    // Destructor: Libera la memoria de los vehículos restantes si los hay
    ~SistemaParqueadero() {
        for (auto const& [placa, vehiculo] : vehiculosEstacionados) {
            delete vehiculo; // ¡Importante liberar la memoria!
        }
        vehiculosEstacionados.clear();
    }

    // --- Métodos del Sistema ---

    // Muestra el estado de todos los parqueaderos
    void mostrarEstadoParqueaderos() const {
        cout << "\n--- ESTADO ACTUAL DEL PARQUEADERO ---" << endl;
        if (espaciosParqueadero.empty()) {
            cout << "No hay parqueaderos configurados." << endl;
            return;
        }
        for (const auto& par : espaciosParqueadero) {
            par.second.mostrarEstado(); // Llama al método mostrarEstado de cada Parqueadero
        }
        cout << "-------------------------------------" << endl;
    }

    // Verifica la disponibilidad de parqueaderos para un tipo de vehículo
    void verificarDisponibilidad(const string& tipoVehiculo) const {
        int count = 0;
        cout << "\nVerificando disponibilidad para " << tipoVehiculo << "..." << endl;
        for (const auto& par : espaciosParqueadero) {
            if (!par.second.estaOcupado && !par.second.estaBloqueado) { // Si está disponible
                // La clave: un parqueadero mixto puede aceptar cualquier tipo
                if (par.second.tipoPermitido == tipoVehiculo || par.second.tipoPermitido == "Mixto") {
                    count++;
                    cout << "  - " << par.second.codigo << " (Tipo: " << par.second.tipoPermitido << ") esta disponible." << endl;
                }
            }
        }
        cout << "Total de espacios disponibles para " << tipoVehiculo << ": " << count << endl;
    }

    // Ingresar un vehículo al parqueadero
    void ingresarVehiculo(const string& placa, const string& tipoVehiculo) {
        // Verificar si la placa ya está estacionada
        if (vehiculosEstacionados.count(placa)) {
            cout << "ERROR: El vehiculo con placa " << placa << " ya esta estacionado." << endl;
            return;
        }

        // Crear el objeto Vehiculo (Automovil o Moto)
        Vehiculo* nuevoVehiculo = nullptr;
        if (tipoVehiculo == "Automovil") {
            nuevoVehiculo = new Automovil(placa);
        } else if (tipoVehiculo == "Moto") {
            nuevoVehiculo = new Moto(placa);
        } else {
            cout << "ERROR: Tipo de vehiculo invalido. Use 'Automovil' o 'Moto'." << endl;
            return;
        }

        // Buscar un parqueadero disponible que acepte este tipo de vehículo
        for (auto& par : espaciosParqueadero) { // 'auto&' para poder modificar el objeto Parqueadero
            if (!par.second.estaOcupado && !par.second.estaBloqueado) {
                // Si el parqueadero es del tipo correcto O es Mixto
                if (par.second.tipoPermitido == tipoVehiculo || par.second.tipoPermitido == "Mixto") {
                    par.second.ocupar(nuevoVehiculo); // Ocupar el parqueadero
                    vehiculosEstacionados[placa] = nuevoVehiculo; // Guardar el vehículo en la lista de activos
                    cout << "Vehiculo " << placa << " ingresado con exito." << endl;
                    return; // Terminar la función una vez que se estaciona
                }
            }
        }
        cout << "ERROR: No hay parqueaderos disponibles para un " << tipoVehiculo << " en este momento." << endl;
        delete nuevoVehiculo; // Si no se pudo estacionar, liberar la memoria del vehículo creado
    }

    // Sacar un vehículo del parqueadero
    void salirVehiculo(const string& placa) {
        // Buscar el vehículo en la lista de estacionados
        auto it = vehiculosEstacionados.find(placa);
        if (it == vehiculosEstacionados.end()) {
            cout << "ERROR: El vehiculo con placa " << placa << " no se encuentra estacionado." << endl;
            return;
        }

        Vehiculo* vehiculoASacar = it->second; // Obtener el puntero al vehículo

        // Buscar el parqueadero donde está este vehículo
        for (auto& par : espaciosParqueadero) {
            if (par.second.vehiculoEstacionado == vehiculoASacar) { // Si este parqueadero tiene nuestro vehículo
                par.second.desocupar(); // Desocupar el parqueadero (esto borrará el vehículo)
                vehiculosEstacionados.erase(it); // Eliminar de la lista de vehículos activos
                vehiculoASacar->calcularTarifa(); // Llamar al método de tarifa (polimorfismo)
                cout << "Vehiculo " << placa << " ha salido con exito." << endl;
                return;
            }
        }
        cout << "ERROR INTERNO: No se encontro el parqueadero del vehiculo " << placa << "." << endl;
    }

    // Bloquear un parqueadero específico por su código
    void bloquearParqueadero(const string& codigo) {
        auto it = espaciosParqueadero.find(codigo);
        if (it != espaciosParqueadero.end()) {
            it->second.bloquear();
        } else {
            cout << "ERROR: Parqueadero con codigo " << codigo << " no encontrado." << endl;
        }
    }

    // Habilitar un parqueadero específico por su código
    void habilitarParqueadero(const string& codigo) {
        auto it = espaciosParqueadero.find(codigo);
        if (it != espaciosParqueadero.end()) {
            it->second.habilitar();
        } else {
            cout << "ERROR: Parqueadero con codigo " << codigo << " no encontrado." << endl;
        }
    }
};

// --- Funciones de Menú ---

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenuPrincipal() {
    cout << "\n--- SIMULADOR DE PARQUEADERO (SENCILLO) ---" << endl;
    cout << "1. Mostrar estado de los parqueaderos" << endl;
    cout << "2. Verificar disponibilidad de parqueadero" << endl;
    cout << "3. Ingresar vehiculo" << endl;
    cout << "4. Sacar vehiculo" << endl;
    cout << "5. Bloquear parqueadero (Admin)" << endl;
    cout << "6. Habilitar parqueadero (Admin)" << endl;
    cout << "7. Salir" << endl;
    cout << "Ingrese su opcion: ";
}

// --- Funcion Principal (main) ---
int main() {
    SistemaParqueadero miSistema; // Crea una instancia de nuestro sistema de parqueadero

    int opcion;
    do {
        mostrarMenuPrincipal();
        while (!(cin >> opcion)) { // Validar entrada numérica
            cout << "Entrada invalida. Por favor, ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer(); // Limpiar el buffer después de leer el número

        string placa, tipo, codigo;

        switch (opcion) {
            case 1: // Mostrar estado
                miSistema.mostrarEstadoParqueaderos();
                break;
            case 2: // Verificar disponibilidad
                cout << "Tipo de vehiculo (Automovil/Moto): ";
                getline(cin, tipo);
                miSistema.verificarDisponibilidad(tipo);
                break;
            case 3: // Ingresar vehiculo
                cout << "Placa del vehiculo: ";
                getline(cin, placa);
                cout << "Tipo de vehiculo (Automovil/Moto): ";
                getline(cin, tipo);
                miSistema.ingresarVehiculo(placa, tipo);
                break;
            case 4: // Sacar vehiculo
                cout << "Placa del vehiculo a sacar: ";
                getline(cin, placa);
                miSistema.salirVehiculo(placa);
                break;
            case 5: // Bloquear parqueadero (Admin)
                cout << "Codigo del parqueadero a bloquear (ej. A1, M1, X1): ";
                getline(cin, codigo);
                miSistema.bloquearParqueadero(codigo);
                break;
            case 6: // Habilitar parqueadero (Admin)
                cout << "Codigo del parqueadero a habilitar: ";
                getline(cin, codigo);
                miSistema.habilitarParqueadero(codigo);
                break;
            case 7: // Salir
                cout << "Saliendo del simulador. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}