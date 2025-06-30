#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip> // Para setprecision
#include <limits>  // Para numeric_limits
#include <sstream> // Para stringstream (reportes)

using namespace std;

// --- Funciones Auxiliares ---
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// --- Clase Base: Vehiculo ---
class Vehiculo {
public:
    string placa;
    string tipoVehiculo; // "Automovil" o "Moto"
    int horaEntradaSimulada; // Hora de entrada en nuestra simulación simple

    Vehiculo(const string& _placa, const string& _tipoVehiculo, int _horaEntrada)
        : placa(_placa), tipoVehiculo(_tipoVehiculo), horaEntradaSimulada(_horaEntrada) {}

    virtual ~Vehiculo() {}

    virtual void Informacion() const = 0;
    virtual double CalcularTarifa(int horaSalidaSimulada, double tarifaBasePorHora) const = 0;
    
    string getPlaca() const { return placa; }
    string getTipoVehiculo() const { return tipoVehiculo; } // Añadido para el Sistema
};

// --- Clase Derivada: Automovil ---
class Automovil : public Vehiculo {
public:
    Automovil(const string& placa, int horaEntrada)
        : Vehiculo(placa, "Automovil", horaEntrada) {}

    void Informacion() const override {
        cout << "Automovil con placa " << placa << endl;
    }
    double CalcularTarifa(int horaSalidaSimulada, double tarifaBasePorHora) const override {
        int horasEstacionado = horaSalidaSimulada - horaEntradaSimulada;
        if (horasEstacionado < 0) horasEstacionado = 0; // Evitar horas negativas
        return static_cast<double>(horasEstacionado) * tarifaBasePorHora;
    }
};

// --- Clase Derivada: Moto ---
class Moto : public Vehiculo {
public:
    Moto(const string& placa, int horaEntrada)
        : Vehiculo(placa, "Moto", horaEntrada) {}

    void Informacion() const override {
        cout << "Moto con placa " << placa << endl;
    }
    double CalcularTarifa(int horaSalidaSimulada, double tarifaBasePorHora) const override {
        int horasEstacionado = horaSalidaSimulada - horaEntradaSimulada;
        if (horasEstacionado < 0) horasEstacionado = 0; // Evitar horas negativas
        return static_cast<double>(horasEstacionado) * tarifaBasePorHora;
    }
};

// --- Clase: Usuario ---
class Usuario {
private:
    string nombre;
    string dni;
    string placaRegistrada;
    string tipoVehiculoRegistrado;

public:
    Usuario(const string& _nombre, const string& _dni)
        : nombre(_nombre), dni(_dni) {}

    string getNombre() const { return nombre; }
    string getDNI() const { return dni; }
    string getPlacaRegistrada() const { return placaRegistrada; }
    string getTipoVehiculoRegistrado() const { return tipoVehiculoRegistrado; }

    void setNombre(const string& newNombre) { nombre = newNombre; }
    void setPlacaRegistrada(const string& placa) { placaRegistrada = placa; }
    void setTipoVehiculoRegistrado(const string& tipo) { tipoVehiculoRegistrado = tipo; }

    void mostrarInfo() const {
        cout << "Nombre: " << nombre << ", DNI: " << dni;
        if (!placaRegistrada.empty()) {
            cout << ", Vehiculo Registrado: " << placaRegistrada << " (" << tipoVehiculoRegistrado << ")";
        }
        cout << endl;
    }
};

// --- Clase: Parqueadero ---
class Parqueadero {
private:
    string codigo;
    bool estaOcupado;
    bool estaBloqueado;
    Vehiculo* vehiculoEstacionado;

public:
    Parqueadero(const string& _codigo)
        : codigo(_codigo), estaOcupado(false), estaBloqueado(false), vehiculoEstacionado(nullptr) {}

    ~Parqueadero() {
        if (vehiculoEstacionado) {
            delete vehiculoEstacionado;
            vehiculoEstacionado = nullptr;
        }
    }

    string getCodigo() const { return codigo; }
    bool isOcupado() const { return estaOcupado; }
    bool isBloqueado() const { return estaBloqueado; }
    Vehiculo* getVehiculoEstacionado() const { return vehiculoEstacionado; }

    void ocupar(Vehiculo* vehiculo) {
        if (!estaOcupado && !estaBloqueado) {
            estaOcupado = true;
            vehiculoEstacionado = vehiculo;
            cout << "Parqueadero " << codigo << " ocupado por " << vehiculo->getPlaca() << endl;
        } else {
            cout << "ERROR: Parqueadero " << codigo << " no disponible o bloqueado." << endl;
        }
    }

    Vehiculo* desocupar() {
        if (estaOcupado) {
            Vehiculo* tempVehiculo = vehiculoEstacionado;
            vehiculoEstacionado = nullptr;
            estaOcupado = false;
            cout << "Parqueadero " << codigo << " desocupado." << endl;
            return tempVehiculo;
        } else {
            cout << "ERROR: Parqueadero " << codigo << " ya esta vacio." << endl;
            return nullptr;
        }
    }

    void bloquear() {
        if (!estaOcupado) {
            estaBloqueado = true;
            cout << "Parqueadero " << codigo << " bloqueado." << endl;
        } else {
            cout << "ERROR: No se puede bloquear parqueadero " << codigo << " mientras esta ocupado." << endl;
        }
    }

    void habilitar() {
        estaBloqueado = false;
        cout << "Parqueadero " << codigo << " habilitado." << endl;
    }

    void mostrarEstado() const {
        cout << "Parqueadero " << codigo << ": "
             << (estaOcupado ? "Ocupado" : "Disponible")
             << (estaBloqueado ? " (Bloqueado)" : "");
        if (estaOcupado && vehiculoEstacionado) {
            cout << " por ";
            vehiculoEstacionado->Informacion();
        } else {
            cout << endl;
        }
    }
};

// --- Clase: Administrador (definición simple por ahora) ---
class Administrador {
private:
    string nombre;
    string contrasena;

public:
    Administrador(const string& _nombre, const string& _contrasena)
        : nombre(_nombre), contrasena(_contrasena) {}

    string getNombre() const { return nombre; }
    string getContrasena() const { return contrasena; }
};


// --- Clase Principal: SistemaParqueadero ---
class SistemaParqueadero {
private:
    map<string, Usuario> usuarios; // map<DNI, Usuario>
    map<string, Administrador> administradores; // map<NombreUsuario, Administrador>
    map<string, Parqueadero> parqueaderos; // map<CodigoParqueadero, Parqueadero>
    map<string, Vehiculo*> vehiculosEstacionados; // map<Placa, Vehiculo*>

    double tarifaAutomovilPorHora;
    double tarifaMotoPorHora;

    // --- NUEVA VARIABLE DE TIEMPO SIMULADO ---
    int horaActualSimulacion; // Representa la hora actual en la simulación

    // Estructura para registros de reportes
    struct RegistroEstacionamiento {
        string placa;
        string tipoVehiculo;
        string codigoParqueadero;
        int horaEntradaSimulada;
        int horaSalidaSimulada;
        double tarifaPagada;
        string dniUsuario;

        // Para reportes diarios (simplificado a solo el día)
        string getDiaSimulado() const {
            // Asumimos que cada 24 horas simuladas es un día nuevo.
            // Esto es una simplificación extrema, un día real requeriría más lógica.
            return "Dia " + to_string(horaEntradaSimulada / 24 + 1);
        }
    };
    vector<RegistroEstacionamiento> historialEstacionamientos;

public:
    SistemaParqueadero() : tarifaAutomovilPorHora(0.0), tarifaMotoPorHora(0.0), horaActualSimulacion(0) {
        administradores.emplace("admin", Administrador("admin", "adminpass"));
        cout << "Sistema inicializado. Admin 'admin' creado con contrasena 'adminpass'." << endl;
        cout << "La hora actual de la simulacion es: " << horaActualSimulacion << endl;
    }

    ~SistemaParqueadero() {
        for (auto const& [placa, vehiculo_ptr] : vehiculosEstacionados) {
            delete vehiculo_ptr;
        }
    }

    // --- Autenticacion ---
    void registrarUsuario(const string& nombre, const string& dni) {
        if (usuarios.count(dni)) {
            cout << "ERROR: Ya existe un usuario con DNI " << dni << "." << endl;
        } else {
            usuarios.emplace(dni, Usuario(nombre, dni));
            cout << "Usuario " << nombre << " (DNI: " << dni << ") registrado con exito." << endl;
        }
    }

    Usuario* autenticarUsuario(const string& dni) {
        auto it = usuarios.find(dni);
        if (it != usuarios.end()) {
            cout << "Bienvenido, " << it->second.getNombre() << "!" << endl;
            return &it->second;
        }
        cout << "ERROR: Usuario con DNI " << dni << " no encontrado." << endl;
        return nullptr;
    }

    Administrador* autenticarAdministrador(const string& nombre, const string& contrasena) {
        auto it = administradores.find(nombre);
        if (it != administradores.end() && it->second.getContrasena() == contrasena) {
            cout << "Bienvenido, Administrador " << it->second.getNombre() << "!" << endl;
            return &it->second;
        }
        cout << "ERROR: Credenciales de administrador incorrectas." << endl;
        return nullptr;
    }

    // --- Métodos de Usuario ---
    void actualizarDatosUsuario(Usuario* user) {
        if (!user) return;
        cout << "Actualizar datos para " << user->getNombre() << ":" << endl;
        cout << "Nuevo nombre (dejar vacio para no cambiar): ";
        string newName;
        getline(cin, newName);
        if (!newName.empty()) {
            user->setNombre(newName);
        }
        cout << "Placa de su vehiculo (dejar vacio para no cambiar): ";
        string newPlaca;
        getline(cin, newPlaca);
        if (!newPlaca.empty()) {
            user->setPlacaRegistrada(newPlaca);
            cout << "Tipo de vehiculo (Automovil/Moto): ";
            string newTipo;
            getline(cin, newTipo);
            user->setTipoVehiculoRegistrado(newTipo);
        }
        cout << "Datos actualizados." << endl;
    }

    void verificarDisponibilidadParqueaderos() const {
        int disponibles = 0;
        cout << "\n--- Disponibilidad de Parqueaderos ---" << endl;
        for (const auto& par : parqueaderos) {
            if (!par.second.isOcupado() && !par.second.isBloqueado()) {
                disponibles++;
                cout << "  - " << par.second.getCodigo() << " (Disponible)" << endl;
            }
        }
        cout << "Total de parqueaderos disponibles: " << disponibles << endl;
        cout << "------------------------------------" << endl;
    }

    void ingresarVehiculo(Usuario* user) {
        if (!user) return;
        if (user->getPlacaRegistrada().empty()) {
            cout << "ERROR: Por favor, actualice sus datos de usuario para registrar la placa y tipo de vehiculo primero." << endl;
            return;
        }
        string placa = user->getPlacaRegistrada();
        string tipo = user->getTipoVehiculoRegistrado();

        if (vehiculosEstacionados.count(placa)) {
            cout << "ERROR: El vehiculo con placa " << placa << " ya esta estacionado." << endl;
            return;
        }

        Vehiculo* nuevoVehiculo = nullptr;
        if (tipo == "Automovil") {
            nuevoVehiculo = new Automovil(placa, horaActualSimulacion); // Pasa la hora actual
        } else if (tipo == "Moto") {
            nuevoVehiculo = new Moto(placa, horaActualSimulacion); // Pasa la hora actual
        } else {
            cout << "ERROR: Tipo de vehiculo invalido en el registro del usuario." << endl;
            return;
        }

        for (auto& parEntry : parqueaderos) {
            Parqueadero& p = parEntry.second;
            if (!p.isOcupado() && !p.isBloqueado()) {
                p.ocupar(nuevoVehiculo);
                vehiculosEstacionados[placa] = nuevoVehiculo;
                cout << "Vehiculo " << placa << " ingresado al parqueadero " << p.getCodigo()
                     << " a la hora simulada: " << horaActualSimulacion << " con exito." << endl;
                return;
            }
        }
        cout << "ERROR: No hay parqueaderos disponibles en este momento." << endl;
        delete nuevoVehiculo;
    }

    void salirVehiculo(Usuario* user) {
        if (!user) return;
        string placa = user->getPlacaRegistrada();
        if (placa.empty() || !vehiculosEstacionados.count(placa)) {
            cout << "ERROR: El vehiculo asociado a este usuario no esta estacionado o no ha sido registrado." << endl;
            return;
        }

        Vehiculo* vehiculoEnParqueadero = vehiculosEstacionados[placa];
        string codigoParqueadero = "";

        for (auto& parEntry : parqueaderos) {
            if (parEntry.second.getVehiculoEstacionado() == vehiculoEnParqueadero) {
                codigoParqueadero = parEntry.second.getCodigo();
                break;
            }
        }

        if (codigoParqueadero.empty()) {
            cout << "ERROR INTERNO: No se encontro el parqueadero del vehiculo " << placa << "." << endl;
            return;
        }

        // Calcula la tarifa con la hora actual simulada
        double tarifaBase = (vehiculoEnParqueadero->getTipoVehiculo() == "Automovil") ? tarifaAutomovilPorHora : tarifaMotoPorHora;
        double costo = vehiculoEnParqueadero->CalcularTarifa(horaActualSimulacion, tarifaBase);

        // Registra el historial ANTES de liberar la memoria del vehículo
        historialEstacionamientos.push_back({
            placa, vehiculoEnParqueadero->getTipoVehiculo(), codigoParqueadero,
            vehiculoEnParqueadero->horaEntradaSimulada, horaActualSimulacion, costo, user->getDNI()
        });

        parqueaderos.at(codigoParqueadero).desocupar();
        vehiculosEstacionados.erase(placa);

        cout << "Vehiculo " << placa << " ha salido con exito." << endl;
        cout << "Hora de salida simulada: " << horaActualSimulacion << endl;
        cout << "Tarifa a pagar: S/ " << fixed << setprecision(2) << costo << endl;
    }

    // --- Métodos de Administrador ---
    void establecerCantidadParqueaderos(int cantidad) {
        parqueaderos.clear();
        for (int i = 1; i <= cantidad; ++i) {
            string codigo = "P" + to_string(i);
            parqueaderos.emplace(codigo, Parqueadero(codigo));
        }
        cout << "Se han configurado " << cantidad << " parqueaderos genericos (P1-P" << cantidad << ")." << endl;
    }

    void bloquearParqueaderoPorCodigo(const string& codigo) {
        auto it = parqueaderos.find(codigo);
        if (it != parqueaderos.end()) {
            it->second.bloquear();
        } else {
            cout << "ERROR: Parqueadero con codigo " << codigo << " no encontrado." << endl;
        }
    }

    void habilitarParqueaderoPorCodigo(const string& codigo) {
        auto it = parqueaderos.find(codigo);
        if (it != parqueaderos.end()) {
            it->second.habilitar();
        } else {
            cout << "ERROR: Parqueadero con codigo " << codigo << " no encontrado." << endl;
        }
    }

    void establecerTarifaPorHoraYTipo(const string& tipo, double tarifa) {
        if (tipo == "Automovil") {
            tarifaAutomovilPorHora = tarifa;
            cout << "Tarifa de Automovil establecida en S/ " << fixed << setprecision(2) << tarifa << " por hora." << endl;
        } else if (tipo == "Moto") {
            tarifaMotoPorHora = tarifa;
            cout << "Tarifa de Moto establecida en S/ " << fixed << setprecision(2) << tarifa << " por hora." << endl;
        } else {
            cout << "Tipo de vehiculo no valido. Use 'Automovil' o 'Moto'." << endl;
        }
    }

    // --- NUEVA FUNCION PARA AUMENTAR EL TIEMPO ---
    void aumentarTiempoSimulacion(int horas) {
        if (horas > 0) {
            horaActualSimulacion += horas;
            cout << "El tiempo de simulacion ha avanzado " << horas << " horas." << endl;
            cout << "La hora actual de la simulacion es: " << horaActualSimulacion << endl;
        } else {
            cout << "ERROR: La cantidad de horas a aumentar debe ser positiva." << endl;
        }
    }

    void generarReportes(int tipoReporte) {
        cout << "\n--- GENERANDO REPORTE ---" << endl;
        if (historialEstacionamientos.empty()) {
            cout << "No hay registros de estacionamiento para generar reportes." << endl;
            return;
        }

        switch (tipoReporte) {
            case 1: { // Ingresos por día (simplificado al día simulado)
                map<string, double> ingresosPorDia;
                for (const auto& reg : historialEstacionamientos) {
                    ingresosPorDia[reg.getDiaSimulado()] += reg.tarifaPagada;
                }
                cout << "Reporte de Ingresos por Dia Simulado:" << endl;
                for (const auto& entry : ingresosPorDia) {
                    cout << "  " << entry.first << " - Ingreso Total: S/ " << fixed << setprecision(2) << entry.second << endl;
                }
                break;
            }
            case 2: { // Ingresos por vehículo
                map<string, double> ingresosPorVehiculo;
                for (const auto& reg : historialEstacionamientos) {
                    ingresosPorVehiculo[reg.placa] += reg.tarifaPagada;
                }
                cout << "Reporte de Ingresos por Vehiculo:" << endl;
                for (const auto& entry : ingresosPorVehiculo) {
                    cout << "  Placa: " << entry.first << " - Ingreso Total: S/ " << fixed << setprecision(2) << entry.second << endl;
                }
                break;
            }
            case 3: { // Ver parqueaderos ocupados / disponibles
                cout << "Estado actual de Parqueaderos:" << endl;
                verificarDisponibilidadParqueaderos();
                cout << "Parqueaderos Ocupados:" << endl;
                for (const auto& par : parqueaderos) {
                    if (par.second.isOcupado()) {
                        par.second.mostrarEstado();
                    }
                }
                break;
            }
            case 4: { // Mostrar detalle de usuario por placa
                cout << "Ingrese la placa del vehiculo para buscar el usuario: ";
                string placaBuscada;
                getline(cin, placaBuscada);
                string dniEncontrado = "";
                for (const auto& reg : historialEstacionamientos) {
                    if (reg.placa == placaBuscada) {
                        dniEncontrado = reg.dniUsuario;
                        break;
                    }
                }
                if (!dniEncontrado.empty()) {
                    auto it = usuarios.find(dniEncontrado);
                    if (it != usuarios.end()) {
                        cout << "Detalle del Usuario para placa " << placaBuscada << ":" << endl;
                        it->second.mostrarInfo();
                    } else {
                        cout << "Usuario no encontrado para DNI: " << dniEncontrado << endl;
                    }
                } else {
                    cout << "Placa no encontrada en el historial de estacionamientos." << endl;
                }
                break;
            }
            case 5: { // Mostrar detalle de auto por dni de usuario
                cout << "Ingrese el DNI del usuario para buscar el auto: ";
                string dniBuscado;
                getline(cin, dniBuscado);
                auto it = usuarios.find(dniBuscado);
                if (it != usuarios.end()) {
                    if (!it->second.getPlacaRegistrada().empty()) {
                        cout << "Detalle del Vehiculo para DNI " << dniBuscado << ":" << endl;
                        cout << "  Placa: " << it->second.getPlacaRegistrada()
                             << ", Tipo: " << it->second.getTipoVehiculoRegistrado() << endl;
                    } else {
                        cout << "El usuario con DNI " << dniBuscado << " no tiene un vehiculo registrado." << endl;
                    }
                } else {
                    cout << "Usuario con DNI " << dniBuscado << " no encontrado." << endl;
                }
                break;
            }
            default:
                cout << "Tipo de reporte no valido." << endl;
                break;
        }
        cout << "-----------------------------------" << endl;
    }
};

// --- Variables Globales para Usuario/Admin Autenticado ---
Usuario* currentUsuario = nullptr;
Administrador* currentAdministrador = nullptr;

// --- Declaraciones de Funciones de Menú ---
void menu_principal();
void menu_usuario_loop(SistemaParqueadero& sistema);
void menu_administrador_loop(SistemaParqueadero& sistema);

// --- Función Principal ---
int main() {
    SistemaParqueadero miSistema;

    int opc_principal = 0;
    while (opc_principal != 4) {
        cout << endl;
        cout << "----------------------" << endl;
        menu_principal();
        cout << "Ingrese una opcion: ";
        while (!(cin >> opc_principal)) {
            cout << "Entrada invalida. Por favor, ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer();

        string nombre, dni, contrasena;

        switch (opc_principal) {
            case 1: { // Registrarse
                cout << "--- REGISTRO ---" << endl;
                cout << "Tipo de registro (usuario/administrador): ";
                string tipoRegistro;
                getline(cin, tipoRegistro);

                if (tipoRegistro == "usuario") {
                    cout << "Ingrese su nombre: ";
                    getline(cin, nombre);
                    cout << "Ingrese su DNI: ";
                    getline(cin, dni);
                    miSistema.registrarUsuario(nombre, dni);
                } else if (tipoRegistro == "administrador") {
                    cout << "Ingrese nombre de administrador: ";
                    getline(cin, nombre);
                    cout << "Ingrese contrasena de administrador: ";
                    getline(cin, contrasena);
                    miSistema.administradores.emplace(nombre, Administrador(nombre, contrasena));
                    cout << "Administrador " << nombre << " registrado." << endl;
                } else {
                    cout << "Tipo de registro no valido." << endl;
                }
                break;
            }
            case 2: { // Inicio Usuario
                cout << "--- INICIO DE SESION (USUARIO) ---" << endl;
                cout << "Ingrese su DNI: ";
                getline(cin, dni);
                currentUsuario = miSistema.autenticarUsuario(dni);
                if (currentUsuario) {
                    menu_usuario_loop(miSistema);
                    currentUsuario = nullptr;
                }
                break;
            }
            case 3: { // Inicio Administrador
                cout << "--- INICIO DE SESION (ADMINISTRADOR) ---" << endl;
                cout << "Ingrese nombre de usuario: ";
                getline(cin, nombre);
                cout << "Ingrese contrasena: ";
                getline(cin, contrasena);
                currentAdministrador = miSistema.autenticarAdministrador(nombre, contrasena);
                if (currentAdministrador) {
                    menu_administrador_loop(miSistema);
                    currentAdministrador = nullptr;
                }
                break;
            }
            case 4:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
        }
    }

    return 0;
}

// --- Implementaciones de Funciones de Menú ---
void menu_principal() {
    cout << "1. Registrarse" << endl;
    cout << "2. Inicio Sesion Usuario" << endl;
    cout << "3. Inicio Sesion Administrador" << endl;
    cout << "4. Salir" << endl;
}

void menu_usuario_loop(SistemaParqueadero& sistema) {
    int opc_usuario = 0;
    while (opc_usuario != 5) {
        cout << endl;
        cout << "----------------------" << endl;
        cout << "Menu Usuario" << endl;
        cout << "1. Actualizar datos" << endl;
        cout << "2. Verificar Disponibilidad" << endl;
        cout << "3. Ingresar vehiculo" << endl;
        cout << "4. Salir vehiculo y Pagar Tarifa" << endl;
        cout << "5. Regresar al Menu Principal" << endl;
        cout << "Ingrese una opcion: ";
        while (!(cin >> opc_usuario)) {
            cout << "Entrada invalida. Por favor, ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer();

        switch (opc_usuario) {
            case 1: sistema.actualizarDatosUsuario(currentUsuario); break;
            case 2: sistema.verificarDisponibilidadParqueaderos(); break;
            case 3: sistema.ingresarVehiculo(currentUsuario); break;
            case 4: sistema.salirVehiculo(currentUsuario); break;
            case 5: cout << "Regresando al menu principal..." << endl; break;
            default: cout << "Opcion no valida, intente de nuevo." << endl;
        }
    }
}

void menu_administrador_loop(SistemaParqueadero& sistema) {
    int opc_admin = 0;
    while (opc_admin != 7) { // Agregamos una opción para aumentar el tiempo
        cout << endl;
        cout << "----------------------" << endl;
        cout << "Menu Administrador" << endl;
        cout << "1. Establecer cantidad de parqueaderos" << endl;
        cout << "2. Bloquear parqueadero por codigo" << endl;
        cout << "3. Habilitar parqueadero por codigo" << endl;
        cout << "4. Establecer tarifa por hora y por tipo" << endl;
        cout << "5. Generar reportes" << endl;
        cout << "6. Aumentar tiempo de simulacion" << endl; // Nueva opción
        cout << "7. Regresar al Menu Principal" << endl;
        cout << "Ingrese una opcion: ";
        while (!(cin >> opc_admin)) {
            cout << "Entrada invalida. Por favor, ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer();

        string codigo, tipo;
        int cantidad;
        double tarifa;
        int tipoReporte;
        int horasAumentar; // Para la nueva opción

        switch (opc_admin) {
            case 1:
                cout << "Ingrese la cantidad de parqueaderos a establecer: ";
                while (!(cin >> cantidad)) { cout << "Entrada invalida. Ingrese un numero: "; cin.clear(); limpiarBuffer(); }
                limpiarBuffer();
                sistema.establecerCantidadParqueaderos(cantidad);
                break;
            case 2:
                cout << "Ingrese el codigo del parqueadero a bloquear: ";
                getline(cin, codigo);
                sistema.bloquearParqueaderoPorCodigo(codigo);
                break;
            case 3:
                cout << "Ingrese el codigo del parqueadero a habilitar: ";
                getline(cin, codigo);
                sistema.habilitarParqueaderoPorCodigo(codigo);
                break;
            case 4:
                cout << "Ingrese tipo de vehiculo (Automovil/Moto): ";
                getline(cin, tipo);
                cout << "Ingrese la nueva tarifa por hora: ";
                while (!(cin >> tarifa)) { cout << "Entrada invalida. Ingrese un numero: "; cin.clear(); limpiarBuffer(); }
                limpiarBuffer();
                sistema.establecerTarifaPorHoraYTipo(tipo, tarifa);
                break;
            case 5:
                cout << "--- Opciones de Reporte ---" << endl;
                cout << "1. Ingresos por dia" << endl;
                cout << "2. Ingresos por vehiculo" << endl;
                cout << "3. Ver parqueaderos ocupados / disponibles" << endl;
                cout << "4. Mostrar detalle de usuario por placa" << endl;
                cout << "5. Mostrar detalle de auto por DNI de usuario" << endl;
                cout << "Ingrese el tipo de reporte: ";
                while (!(cin >> tipoReporte)) { cout << "Entrada invalida. Ingrese un numero: "; cin.clear(); limpiarBuffer(); }
                limpiarBuffer();
                sistema.generarReportes(tipoReporte);
                break;
            case 6: // Nueva opción: Aumentar tiempo
                cout << "Ingrese cuantas horas desea avanzar la simulacion: ";
                while (!(cin >> horasAumentar)) { cout << "Entrada invalida. Ingrese un numero: "; cin.clear(); limpiarBuffer(); }
                limpiarBuffer();
                sistema.aumentarTiempoSimulacion(horasAumentar);
                break;
            case 7:
                cout << "Regresando al menu principal..." << endl;
                return;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
        }
    }
}