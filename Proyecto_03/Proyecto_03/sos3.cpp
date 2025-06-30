
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>   // Para std::shared_ptr
#include <stdexcept> // Para excepciones estandar
#include <iomanip>  // Para std::fixed, std::setprecision, std::setfill, std::setw
#include <limits>   // Para std::numeric_limits
#include <algorithm> // Para std::transform
#include <fstream>  // Para std::ofstream
#include <sstream>  // Para std::stringstream

// --- Excepciones Personalizadas ---
class ExcepcionPlacaDuplicada : public std::runtime_error {
public:
    explicit ExcepcionPlacaDuplicada(const std::string& placa)
        : std::runtime_error("Error: La placa '" + placa + "' ya se encuentra en el parqueadero.") {}
};

class ExcepcionParqueaderoInvalido : public std::runtime_error {
public:
    explicit ExcepcionParqueaderoInvalido(const std::string& mensaje)
        : std::runtime_error("Error de Parqueadero: " + mensaje) {}
};

class ExcepcionVehiculoNoEncontrado : public std::runtime_error {
public:
    explicit ExcepcionVehiculoNoEncontrado(const std::string& placa)
        : std::runtime_error("Error: Vehiculo con placa '" + placa + "' no encontrado.") {}
};

class ExcepcionAutenticacion : public std::runtime_error {
public:
    explicit ExcepcionAutenticacion(const std::string& mensaje)
        : std::runtime_error("Error de autenticacion: " + mensaje) {}
};

using namespace std;

// --- Clases de Vehiculos ---
class Vehiculo {
public:
    string placa;
    string tipoVehiculo; // "Automovil" o "Moto" (Necesario para la logica del parqueadero)

    Vehiculo(const string& placa, const string& tipoVehiculo)
        : placa(placa), tipoVehiculo(tipoVehiculo) {}

    // Destructor virtual para asegurar que las clases derivadas se destruyan correctamente
    virtual ~Vehiculo() = default; 

    // Metodo virtual para mostrar informacion
    virtual void Informacion() const = 0;
    // Metodo virtual para calcular tarifa (recibe horas y tarifa por hora)
    virtual double CalcularTarifa(double horas, double tarifaPorHora) const = 0;

    string getPlaca() const { return placa; }
    string getTipoVehiculo() const { return tipoVehiculo; }
};

class Automovil : public Vehiculo {
private:
    int numeroPuertas;
public:
    Automovil(const string& placa, int numeroPuertas)
        : Vehiculo(placa, "Automovil"), numeroPuertas(numeroPuertas) {}

    void Informacion() const override {
        cout << "Placa: " << placa
           << ", Tipo: " << tipoVehiculo
           << ", Puertas: " << numeroPuertas; // Sin endl, para que la clase Parqueadero lo controle
    }

    double CalcularTarifa(double horas, double tarifaPorHora) const override {
        // Tarifa simple: horas * tarifa_por_hora
        return horas * tarifaPorHora;
    }
    int getNumeroPuertas() const { return numeroPuertas; }
};

class Moto : public Vehiculo {
private:
    double cilindrada;
public:
    Moto(const string& placa, double cilindrada)
        : Vehiculo(placa, "Moto"), cilindrada(cilindrada) {}

    void Informacion() const override {
        cout << "Placa: " << placa
           << ", Tipo: " << tipoVehiculo
           << ", Cilindrada: " << cilindrada << "cc"; // Sin endl
    }

    double CalcularTarifa(double horas, double tarifaPorHora) const override {
        // Tarifa simple: horas * tarifa_por_hora
        return horas * tarifaPorHora;
    }
    double getCilindrada() const { return cilindrada; }
};

// --- Clase Usuario ---
class Usuario {
private:
    string nombreUsuario;
    string password;
    string placaVehiculoAsociada; // Placa asociada al usuario para facilitar el proceso
public:
    Usuario(const string& user = "", const string& pass = "", const string& placa = "")
        : nombreUsuario(user), password(pass), placaVehiculoAsociada(placa) {}

    // Getters
    string getNombreUsuario() const { return nombreUsuario; }
    string getPassword() const { return password; }
    string getPlacaVehiculoAsociada() const { return placaVehiculoAsociada; }

    // Setters (para actualizar datos del usuario)
    void setPlacaVehiculoAsociada(const string& newPlaca) { placaVehiculoAsociada = newPlaca; }
    void setPassword(const string& newPass) { password = newPass; } // Permitir cambio de contrasena

    void mostrarInformacionUsuario() const {
        cout << "Usuario: " << nombreUsuario
           << ", Placa Asociada: " << placaVehiculoAsociada << endl;
    }
};

// --- Clase Administrador ---
class Administrador {
private:
    string nombreUsuario;
    string contrasena;
public:
    Administrador(const string& user = "", const string& pass = "") : nombreUsuario(user), contrasena(pass) {}

    string getNombreUsuario() const { return nombreUsuario; }
    string getContrasena() const { return contrasena; }

    void mostrarInformacionAdmin() const {
        cout << "Admin Usuario: " << nombreUsuario << endl;
    }
    // Los metodos de funcionalidad del administrador se manejaran a traves de SistemaParqueadero
    // para que tengan acceso a la logica y datos del parqueadero.
};

// --- Clase Parqueadero (Espacio de Estacionamiento) ---
class Parqueadero {
private:
    string codigo; // Ej. "A1", "M2", "X3"
    string tipoPermitido; // "Automovil", "Moto", "Mixto"
    bool estaOcupado;
    bool estaBloqueado;
    shared_ptr<Vehiculo> vehiculoEstacionado; // Puntero inteligente al vehiculo que lo ocupa
    // Para la simulacion de tiempo
    int horaEntradaSimulada;
    int minutoEntradaSimulada;

public:
    Parqueadero(const string& codigo, const string& tipoPermitido)
        : codigo(codigo), tipoPermitido(tipoPermitido), estaOcupado(false),
          estaBloqueado(false), vehiculoEstacionado(nullptr),
          horaEntradaSimulada(-1), minutoEntradaSimulada(-1) {}

    // Getters
    string getCodigo() const { return codigo; }
    string getTipoPermitido() const { return tipoPermitido; }
    bool estaDisponible() const { return !estaOcupado && !estaBloqueado; }
    bool getEstaOcupado() const { return estaOcupado; }
    bool getEstaBloqueado() const { return estaBloqueado; }
    shared_ptr<Vehiculo> getVehiculoEstacionado() const { return vehiculoEstacionado; }
    int getHoraEntradaSimulada() const { return horaEntradaSimulada; }
    int getMinutoEntradaSimulada() const { return minutoEntradaSimulada; }

    void ocupar(shared_ptr<Vehiculo> vehiculo, int horaActual, int minutoActual) {
        if (!estaDisponible()) {
            throw ExcepcionParqueaderoInvalido("El parqueadero " + codigo + " no esta disponible.");
        }
        estaOcupado = true;
        vehiculoEstacionado = vehiculo; // Asigna el shared_ptr
        horaEntradaSimulada = horaActual;
        minutoEntradaSimulada = minutoActual;
        cout << "Parqueadero " << codigo << " ocupado por " << vehiculo->getPlaca() << endl;
    }

    shared_ptr<Vehiculo> desocupar() {
        if (!estaOcupado) {
            throw ExcepcionParqueaderoInvalido("El parqueadero " + codigo + " ya esta vacio.");
        }
        estaOcupado = false;
        horaEntradaSimulada = -1; // Reiniciar
        minutoEntradaSimulada = -1; // Reiniciar
        shared_ptr<Vehiculo> vehiculoQueSalio = vehiculoEstacionado; // Retorna el vehiculo que estaba estacionado
        vehiculoEstacionado = nullptr; // Desvincula el shared_ptr del parqueadero
        cout << "Parqueadero " << codigo << " desocupado." << endl;
        return vehiculoQueSalio;
    }

    void bloquear() {
        if (estaOcupado) {
            throw ExcepcionParqueaderoInvalido("No se puede bloquear el parqueadero " + codigo + " mientras esta ocupado.");
        }
        estaBloqueado = true;
        cout << "Parqueadero " << codigo << " bloqueado." << endl;
    }

    void habilitar() {
        estaBloqueado = false;
        cout << "Parqueadero " << codigo << " habilitado." << endl;
    }

    void mostrarEstadoParqueadero() const {
        cout << "Codigo: " << codigo
           << ", Tipo: " << tipoPermitido
           << ", Ocupado: " << (estaOcupado ? "Si" : "No")
           << ", Bloqueado: " << (estaBloqueado ? "Si" : "No");
        if (estaOcupado && vehiculoEstacionado) {
            cout << ", Vehiculo: [";
            vehiculoEstacionado->Informacion(); // Llama al metodo de informacion del vehiculo
            cout << "], Entrada (simulada): " << setfill('0') << setw(2) << horaEntradaSimulada
               << ":" << setfill('0') << setw(2) << minutoEntradaSimulada;
        }
        cout << endl;
    }
};

// --- Estructura de Registro de Transaccion para Reportes ---
struct RegistroTransaccion {
    string placa;
    string tipoVehiculo;
    string codigoParqueadero;
    int horaEntradaSimulada;
    int minutoEntradaSimulada;
    int horaSalidaSimulada;
    int minutoSalidaSimulada;
    double horasEstacionado;
    double montoPagado;

    void mostrarRegistro() const {
        cout << "Placa: " << placa
           << ", Tipo: " << tipoVehiculo
           << ", Codigo Parqueadero: " << codigoParqueadero
           << ", Entrada (simulada): " << setfill('0') << setw(2) << horaEntradaSimulada
           << ":" << setfill('0') << setw(2) << minutoEntradaSimulada
           << ", Salida (simulada): " << setfill('0') << setw(2) << horaSalidaSimulada
           << ":" << setfill('0') << setw(2) << minutoSalidaSimulada
           << ", Horas: " << fixed << setprecision(2) << horasEstacionado
           << ", Pago: $" << fixed << setprecision(2) << montoPagado << endl;
    }
};


// --- Clase Principal del Sistema de Parqueadero ---
class SistemaParqueadero {
private:
    map<string, Usuario> usuariosRegistrados;
    map<string, Administrador> administradoresRegistrados;
    map<string, Parqueadero> espaciosParqueadero; // Almacena los espacios individuales
    map<string, shared_ptr<Vehiculo>> vehiculosActivos; // Vehiculos actualmente estacionados (mapa placa -> vehiculo)
    map<string, double> tarifasPorTipo; // "Automovil" -> tarifa, "Moto" -> tarifa
    vector<RegistroTransaccion> historialTransacciones;

    int nextCarParkingCode; // Contadores para generar codigos de parqueadero
    int nextMotoParkingCode;
    int nextMixedParkingCode;
    int reportCounter; // Contador para nombres de archivo de reporte (para evitar ctime)

    // Helper para generar codigos unicos de parqueadero
    string generarCodigoParqueadero(const string& tipo) {
        if (tipo == "Automovil") {
            return "A" + to_string(nextCarParkingCode++);
        } else if (tipo == "Moto") {
            return "M" + to_string(nextMotoParkingCode++);
        } else if (tipo == "Mixto") {
            return "X" + to_string(nextMixedParkingCode++);
        }
        return "INV"; // Tipo invalido
    }

    // Helper para escribir reportes en archivo
    void escribirReporteEnArchivo(const string& contenido, const string& nombreArchivo) const {
        ofstream archivoSalida(nombreArchivo);
        if (!archivoSalida.is_open()) {
            throw ExcepcionParqueaderoInvalido("No se pudo abrir o crear el archivo: " + nombreArchivo);
        }
        archivoSalida << contenido;
        archivoSalida.close();
    }

public:
    SistemaParqueadero() : nextCarParkingCode(1), nextMotoParkingCode(1), nextMixedParkingCode(1), reportCounter(0) {
        // Administrador por defecto
        administradoresRegistrados.emplace("admin", Administrador("admin", "admin123"));
        // Tarifas iniciales por defecto (se pueden cambiar por el admin)
        tarifasPorTipo["Automovil"] = 0.0; // Se estableceran al inicio por el usuario
        tarifasPorTipo["Moto"] = 0.0;     // Se estableceran al inicio por el usuario
    }

    // --- Gestion General de Acceso y Usuarios ---
    bool registrarUsuario(const string& user, const string& pass, const string& placa) {
        if (usuariosRegistrados.count(user)) {
            cout << "El nombre de usuario '" << user << "' ya existe." << endl;
            return false;
        }
        usuariosRegistrados.emplace(user, Usuario(user, pass, placa));
        cout << "Usuario '" << user << "' registrado exitosamente." << endl;
        return true;
    }

    Usuario* autenticarUsuario(const string& user, const string& pass) {
        auto it = usuariosRegistrados.find(user);
        if (it != usuariosRegistrados.end() && it->second.getPassword() == pass) {
            return &(it->second); // Retorna un puntero al objeto Usuario
        }
        return nullptr; // Autenticacion fallida
    }

    Administrador* autenticarAdministrador(const string& user, const string& pass) {
        auto it = administradoresRegistrados.find(user);
        if (it != administradoresRegistrados.end() && it->second.getContrasena() == pass) {
            return &(it->second); // Retorna un puntero al objeto Administrador
        }
        return nullptr; // Autenticacion fallida
    }

    void actualizarDatosUsuario(Usuario& usuario, const string& nuevaPlaca) {
        usuario.setPlacaVehiculoAsociada(nuevaPlaca);
        cout << "Placa asociada del usuario " << usuario.getNombreUsuario() << " actualizada." << endl;
    }

    // --- Funcionalidad del Administrador ---
    void establecerCantidadYTipoParqueaderos(int numAutomoviles, int numMotos, int numMixtos) {
        espaciosParqueadero.clear(); // Limpia los parqueaderos existentes
        // Reinicia contadores para nuevos codigos
        nextCarParkingCode = 1;
        nextMotoParkingCode = 1;
        nextMixedParkingCode = 1;

        for (int i = 0; i < numAutomoviles; ++i) {
            string codigo = generarCodigoParqueadero("Automovil");
            espaciosParqueadero.emplace(codigo, Parqueadero(codigo, "Automovil"));
        }
        for (int i = 0; i < numMotos; ++i) {
            string codigo = generarCodigoParqueadero("Moto");
            espaciosParqueadero.emplace(codigo, Parqueadero(codigo, "Moto"));
        }
        for (int i = 0; i < numMixtos; ++i) {
            string codigo = generarCodigoParqueadero("Mixto");
            espaciosParqueadero.emplace(codigo, Parqueadero(codigo, "Mixto"));
        }
        cout << "Parqueaderos inicializados: " << numAutomoviles << " Automovil(es), "
             << numMotos << " Moto(s), " << numMixtos << " Mixto(s)." << endl;
    }

    void establecerTarifaPorHoraYTipo(const string& tipoVehiculo, double tarifa) {
        // Asegurarse de que el tipo de vehiculo sea valido
        if (tipoVehiculo == "Automovil" || tipoVehiculo == "Moto") {
            tarifasPorTipo[tipoVehiculo] = tarifa;
            cout << "Tarifa para " << tipoVehiculo << " establecida a $" << fixed << setprecision(2) << tarifa << "/hora." << endl;
        } else {
            cout << "Tipo de vehiculo '" << tipoVehiculo << "' no valido. Use 'Automovil' o 'Moto'." << endl;
        }
    }

    void bloquearParqueaderoPorCodigo(const string& codigo) {
        auto it = espaciosParqueadero.find(codigo);
        if (it != espaciosParqueadero.end()) {
            it->second.bloquear(); // Llama al metodo de la clase Parqueadero
        } else {
            throw ExcepcionParqueaderoInvalido("El parqueadero '" + codigo + "' no existe.");
        }
    }

    void habilitarParqueaderoPorCodigo(const string& codigo) {
        auto it = espaciosParqueadero.find(codigo);
        if (it != espaciosParqueadero.end()) {
            it->second.habilitar(); // Llama al metodo de la clase Parqueadero
        } else {
            throw ExcepcionParqueaderoInvalido("El parqueadero '" + codigo + "' no existe.");
        }
    }

    // Helper para formatear doubles con precision para strings (para reportes en archivo)
    string fixed_double_precision(double value, int precision) const {
        stringstream ss;
        ss << fixed << setprecision(precision) << value;
        return ss.str();
    }

    void generarReportes(const string& tipoReporte) {
        string contenidoReporte;
        string nombreArchivo;
        reportCounter++; // Incrementa el contador para el nombre del archivo

        // No se usa ctime, solo un contador para el nombre del archivo
        string reportId = to_string(reportCounter);

        if (tipoReporte == "estado_actual") {
            nombreArchivo = "reporte_estado_actual_" + reportId + ".txt";
            contenidoReporte += "--- Reporte de Estado Actual del Parqueadero ---\n";
            contenidoReporte += "ID del Reporte: " + reportId + "\n\n";

            contenidoReporte += "Tarifas Actuales:\n";
            for (const auto& par : tarifasPorTipo) {
                contenidoReporte += "  " + par.first + ": $" + fixed_double_precision(par.second, 2) + "/hora\n";
            }
            contenidoReporte += "\nParqueaderos:\n";
            if (espaciosParqueadero.empty()) {
                contenidoReporte += "  No hay parqueaderos configurados.\n";
            } else {
                for (const auto& par : espaciosParqueadero) {
                    contenidoReporte += "  Codigo: " + par.second.getCodigo() +
                                       ", Tipo: " + par.second.getTipoPermitido() +
                                       ", Ocupado: " + (par.second.getEstaOcupado() ? "Si" : "No") +
                                       ", Bloqueado: " + (par.second.getEstaBloqueado() ? "Si" : "No");
                    if (par.second.getEstaOcupado() && par.second.getVehiculoEstacionado()) {
                        contenidoReporte += ", Vehiculo: " + par.second.getVehiculoEstacionado()->getPlaca();
                        contenidoReporte += ", Entrada (simulada): " + to_string(par.second.getHoraEntradaSimulada()) +
                                            ":" + to_string(par.second.getMinutoEntradaSimulada());
                    }
                    contenidoReporte += "\n";
                }
            }
            
            contenidoReporte += "\nVehiculos actualmente estacionados (seguimiento interno):\n";
            if (vehiculosActivos.empty()) {
                contenidoReporte += "  Ningun vehiculo estacionado actualmente.\n";
            } else {
                for (const auto& par : vehiculosActivos) {
                    contenidoReporte += "  " + par.second->getPlaca() + " (" + par.second->getTipoVehiculo() + ")\n";
                }
            }


        } else if (tipoReporte == "transacciones_historicas") {
            nombreArchivo = "reporte_transacciones_historicas_" + reportId + ".txt";
            contenidoReporte += "--- Reporte de Transacciones Historicas ---\n";
            contenidoReporte += "ID del Reporte: " + reportId + "\n\n";
            if (historialTransacciones.empty()) {
                contenidoReporte += "No hay transacciones registradas.\n";
            } else {
                for (const auto& reg : historialTransacciones) {
                    contenidoReporte += "Placa: " + reg.placa +
                                        ", Tipo: " + reg.tipoVehiculo +
                                        ", Codigo Parqueadero: " + reg.codigoParqueadero +
                                        ", Entrada (simulada): " + to_string(reg.horaEntradaSimulada) + ":" + to_string(reg.minutoEntradaSimulada) +
                                        ", Salida (simulada): " + to_string(reg.horaSalidaSimulada) + ":" + to_string(reg.minutoSalidaSimulada) +
                                        ", Horas: " + fixed_double_precision(reg.horasEstacionado, 2) +
                                        ", Pago: $" + fixed_double_precision(reg.montoPagado, 2) + "\n";
                }
            }
        } else {
            cout << "Tipo de reporte no reconocido." << endl;
            return;
        }

        try {
            escribirReporteEnArchivo(contenidoReporte, nombreArchivo);
            cout << "Reporte '" << tipoReporte << "' generado en '" << nombreArchivo << "'." << endl;
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }

    void mostrarEstadoParqueaderos() const {
        cout << "\n--- Estado Actual de los Parqueaderos ---" << endl;
        if (espaciosParqueadero.empty()) {
            cout << "No hay parqueaderos configurados." << endl;
            return;
        }
        for (const auto& pair : espaciosParqueadero) {
            pair.second.mostrarEstadoParqueadero();
        }
    }

    // --- Funcionalidad del Usuario ---
    int verificarDisponibilidad(const string& tipoVehiculo) const {
        int count = 0;
        for (const auto& par : espaciosParqueadero) {
            if (par.second.estaDisponible()) {
                // Un parqueadero mixto puede aceptar ambos tipos
                if (par.second.getTipoPermitido() == tipoVehiculo || par.second.getTipoPermitido() == "Mixto") {
                    count++;
                }
            }
        }
        return count;
    }

    string ingresarVehiculo(shared_ptr<Vehiculo> vehiculo, int horaActual, int minutoActual) {
        if (vehiculosActivos.count(vehiculo->getPlaca())) {
            throw ExcepcionPlacaDuplicada(vehiculo->getPlaca());
        }

        for (auto& pair : espaciosParqueadero) {
            Parqueadero& p = pair.second; // Obtener una referencia mutable al objeto Parqueadero
            if (p.estaDisponible() && (p.getTipoPermitido() == vehiculo->getTipoVehiculo() || p.getTipoPermitido() == "Mixto")) {
                p.ocupar(vehiculo, horaActual, minutoActual);
                vehiculosActivos.emplace(vehiculo->getPlaca(), vehiculo); // Anadir a vehiculos activos
                return p.getCodigo(); // Retorna el codigo del parqueadero asignado
            }
        }
        throw ExcepcionParqueaderoInvalido("No hay parqueaderos disponibles para el tipo '" + vehiculo->getTipoVehiculo() + "'.");
    }

    double salirVehiculo(const string& placa, int horaSalida, int minutoSalida) {
        auto itVehiculo = vehiculosActivos.find(placa);
        if (itVehiculo == vehiculosActivos.end()) {
            throw ExcepcionVehiculoNoEncontrado(placa);
        }

        shared_ptr<Vehiculo> vehiculoQueSale = itVehiculo->second;
        string codigoParqueaderoOcupado = "";

        // Buscar el parqueadero donde esta el vehiculo
        for (auto& pair : espaciosParqueadero) {
            Parqueadero& p = pair.second;
            if (p.getEstaOcupado() && p.getVehiculoEstacionado() && p.getVehiculoEstacionado()->getPlaca() == placa) {
                codigoParqueaderoOcupado = p.getCodigo();

                int horaEntrada = p.getHoraEntradaSimulada();
                int minutoEntrada = p.getMinutoEntradaSimulada();

                // Calcular tiempo estacionado
                double totalMinutosEntrada = horaEntrada * 60 + minutoEntrada;
                double totalMinutosSalida = horaSalida * 60 + minutoSalida;

                double minutosEstacionado = totalMinutosSalida - totalMinutosEntrada;
                // Manejar el caso si la salida es al dia siguiente (simulado)
                if (minutosEstacionado < 0) {
                    minutosEstacionado += (24 * 60); // Asume que paso a la medianoche (24 horas despues)
                }
                // Si el tiempo es 0 o negativo (ej. entra y sale en el mismo minuto), cobra al menos por un minuto
                if (minutosEstacionado < 1) minutosEstacionado = 1; 

                double horasEstacionado = minutosEstacionado / 60.0;

                double tarifaPorHora = tarifasPorTipo[vehiculoQueSale->getTipoVehiculo()];
                double montoAPagar = vehiculoQueSale->CalcularTarifa(horasEstacionado, tarifaPorHora);

                // Registrar la transaccion
                RegistroTransaccion transaccion;
                transaccion.placa = placa;
                transaccion.tipoVehiculo = vehiculoQueSale->getTipoVehiculo();
                transaccion.codigoParqueadero = codigoParqueaderoOcupado;
                transaccion.horaEntradaSimulada = horaEntrada;
                transaccion.minutoEntradaSimulada = minutoEntrada;
                transaccion.horaSalidaSimulada = horaSalida;
                transaccion.minutoSalidaSimulada = minutoSalida;
                transaccion.horasEstacionado = horasEstacionado;
                transaccion.montoPagado = montoAPagar;
                historialTransacciones.push_back(transaccion);

                p.desocupar(); // Desocupa el parqueadero
                vehiculosActivos.erase(itVehiculo); // Elimina de la lista de vehiculos activos

                cout << "Vehiculo con placa " << placa << " ha salido de " << codigoParqueaderoOcupado << ". ";
                cout << "Horas estacionado: " << fixed << setprecision(2) << horasEstacionado << "h. ";
                cout << "Monto a pagar: $" << fixed << setprecision(2) << montoAPagar << endl;
                return montoAPagar;
            }
        }
        throw ExcepcionParqueaderoInvalido("Error interno: Parqueadero del vehiculo '" + placa + "' no encontrado.");
    }
};

// --- Funciones de Menu y Helpers Globales ---

// Funcion para limpiar el buffer de entrada despues de cin >>
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Funcion para validar la hora y el minuto
bool validarHoraMinuto(int hora, int minuto) {
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        cout << "Hora o minuto invalido. Ingrese valores entre [0-23] para hora y [0-59] para minuto." << endl;
        return false;
    }
    return true;
}

void menu_principal() {
    cout << "1. Registrarse" << endl;
    cout << "2. Iniciar Sesion como Usuario" << endl;
    cout << "3. Iniciar Sesion como Administrador" << endl;
    cout << "4. Salir" << endl;
}

int menu_usuario() {
    int opc = 0;
    cout << endl;
    cout << "----------------------" << endl;
    cout << "Menu Usuario" << endl;
    cout << "1. Actualizar mi placa asociada" << endl;
    cout << "2. Verificar Disponibilidad de Parqueadero" << endl;
    cout << "3. Ingresar mi Vehiculo" << endl;
    cout << "4. Salir mi Vehiculo y Pagar" << endl;
    cout << "5. Cerrar Sesion" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opc;
    return opc;
}

int menu_administrador() {
    int opc = 0;
    cout << endl;
    cout << "----------------------" << endl;
    cout << "Menu Administrador" << endl;
    cout << "1. Establecer cantidad y tipo de parqueaderos" << endl;
    cout << "2. Bloquear parqueadero por codigo" << endl;
    cout << "3. Habilitar parqueadero por codigo" << endl;
    cout << "4. Establecer tarifa por hora y por tipo de vehiculo" << endl;
    cout << "5. Generar reportes" << endl;
    cout << "6. Mostrar Estado Actual de Parqueaderos" << endl;
    cout << "7. Cerrar Sesion" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opc;
    return opc;
}

// --- Funcion Principal ---
int main() {
    // Instancia del sistema de parqueadero
    SistemaParqueadero sistemaParqueadero;

    cout << "--- Configuracion Inicial del Parqueadero ---" << endl;
    int numAutos, numMotos, numMixtos;
    double tarifaAuto, tarifaMoto;

    cout << "Ingrese la cantidad de parqueaderos para AUTOMOVILES: ";
    cin >> numAutos;
    cout << "Ingrese la cantidad de parqueaderos para MOTOS: ";
    cin >> numMotos;
    cout << "Ingrese la cantidad de parqueaderos MIXTOS: ";
    cin >> numMixtos;
    limpiarBuffer(); // Limpiar el buffer despues de leer enteros
    sistemaParqueadero.establecerCantidadYTipoParqueaderos(numAutos, numMotos, numMixtos);

    cout << "Establecer tarifa por hora para AUTOMOVILES: $";
    cin >> tarifaAuto;
    cout << "Establecer tarifa por hora para MOTOS: $";
    cin >> tarifaMoto;
    limpiarBuffer(); // Limpiar el buffer
    sistemaParqueadero.establecerTarifaPorHoraYTipo("Automovil", tarifaAuto);
    sistemaParqueadero.establecerTarifaPorHoraYTipo("Moto", tarifaMoto);
    cout << "Configuracion inicial completa." << endl;


    int opc_principal = 0;
    while (opc_principal != 4) {
        cout << endl;
        cout << "----------------------" << endl;
        menu_principal();
        cout << "Ingrese una opcion: ";
        cin >> opc_principal;
        limpiarBuffer(); // Limpiar el buffer despues de leer la opcion principal

        switch (opc_principal) {
            case 1: { // Registrarse
                string user, pass, placa;
                cout << "--- REGISTRO DE NUEVO USUARIO ---" << endl;
                cout << "Ingrese nombre de usuario: "; getline(cin, user);
                cout << "Ingrese contrasena: "; getline(cin, pass);
                cout << "Ingrese la placa de su vehiculo (ej. ABC-123, opcional): "; getline(cin, placa);
                sistemaParqueadero.registrarUsuario(user, pass, placa);
                break;
            }
            case 2: { // Iniciar Sesion como Usuario
                string user, pass;
                cout << "--- INICIO DE SESION DE USUARIO ---" << endl;
                cout << "Usuario: "; getline(cin, user);
                cout << "Contrasena: "; getline(cin, pass);

                Usuario* usuarioLogueado = sistemaParqueadero.autenticarUsuario(user, pass);
                if (usuarioLogueado) {
                    cout << "Sesion iniciada como usuario: " << usuarioLogueado->getNombreUsuario() << endl;
                    int opc_usuario_sub = 0;
                    while (opc_usuario_sub != 5) { // 5 es "Cerrar Sesion"
                        opc_usuario_sub = menu_usuario();
                        try {
                            switch (opc_usuario_sub) {
                                case 1: { // Actualizar mi placa asociada
                                    string nuevaPlaca;
                                    cout << "Ingrese nueva placa de vehiculo asociada (" << usuarioLogueado->getPlacaVehiculoAsociada() << "): "; getline(cin, nuevaPlaca);
                                    if (nuevaPlaca.empty()) nuevaPlaca = usuarioLogueado->getPlacaVehiculoAsociada(); // Si esta vacio, mantiene el actual
                                    
                                    sistemaParqueadero.actualizarDatosUsuario(*usuarioLogueado, nuevaPlaca);
                                    usuarioLogueado->mostrarInformacionUsuario(); // Mostrar datos actualizados
                                    break;
                                }
                                case 2: { // Verificar Disponibilidad
                                    string tipoVehiculoDisp;
                                    cout << "¿Verificar disponibilidad para 'Automovil' o 'Moto'?: ";
                                    getline(cin, tipoVehiculoDisp);
                                    // Normalizar la entrada a "Automovil" o "Moto"
                                    transform(tipoVehiculoDisp.begin(), tipoVehiculoDisp.end(), tipoVehiculoDisp.begin(), ::tolower);
                                    if (tipoVehiculoDisp == "automovil") tipoVehiculoDisp = "Automovil";
                                    else if (tipoVehiculoDisp == "moto") tipoVehiculoDisp = "Moto";
                                    else { cout << "Tipo de vehiculo invalido." << endl; break; }

                                    int disponibles = sistemaParqueadero.verificarDisponibilidad(tipoVehiculoDisp);
                                    cout << "Parqueaderos disponibles para " << tipoVehiculoDisp << ": " << disponibles << endl;
                                    break;
                                }
                                case 3: { // Ingresar mi Vehiculo
                                    string placa = usuarioLogueado->getPlacaVehiculoAsociada();
                                    if (placa.empty()) {
                                        cout << "Su perfil no tiene una placa de vehiculo asociada. Por favor, actualice sus datos primero (Opcion 1)." << endl;
                                        break;
                                    }
                                    string tipoVehiculo;
                                    cout << "¿Su vehiculo es un 'Automovil' o una 'Moto'?: ";
                                    getline(cin, tipoVehiculo);
                                    transform(tipoVehiculo.begin(), tipoVehiculo.end(), tipoVehiculo.begin(), ::tolower);
                                    if (tipoVehiculo == "automovil") tipoVehiculo = "Automovil";
                                    else if (tipoVehiculo == "moto") tipoVehiculo = "Moto";
                                    else { cout << "Tipo de vehiculo invalido." << endl; break; }

                                    // Se eliminan las solicitudes de marca, modelo y color
                                    int horaEntrada, minutoEntrada;
                                    cout << "Hora de entrada simulada (0-23): "; cin >> horaEntrada;
                                    cout << "Minuto de entrada simulada (0-59): "; cin >> minutoEntrada;
                                    limpiarBuffer(); // Limpiar el buffer

                                    if (!validarHoraMinuto(horaEntrada, minutoEntrada)) {
                                        break;
                                    }

                                    shared_ptr<Vehiculo> nuevoVehiculo;
                                    if (tipoVehiculo == "Automovil") {
                                        int numPuertas;
                                        cout << "Numero de puertas: "; cin >> numPuertas; limpiarBuffer();
                                        nuevoVehiculo = make_shared<Automovil>(placa, numPuertas);
                                    } else { // Moto
                                        double cilindrada;
                                        cout << "Cilindrada (cc): "; cin >> cilindrada; limpiarBuffer();
                                        nuevoVehiculo = make_shared<Moto>(placa, cilindrada);
                                    }
                                    sistemaParqueadero.ingresarVehiculo(nuevoVehiculo, horaEntrada, minutoEntrada);
                                    break;
                                }
                                case 4: { // Salir mi Vehiculo y Pagar
                                    string placaSalir = usuarioLogueado->getPlacaVehiculoAsociada();
                                    if (placaSalir.empty()) {
                                        cout << "Su perfil no tiene una placa de vehiculo asociada para salir. Por favor, actualice sus datos primero (Opcion 1)." << endl;
                                        break;
                                    }
                                    int horaSalida, minutoSalida;
                                    cout << "Hora de salida simulada (0-23): "; cin >> horaSalida;
                                    cout << "Minuto de salida simulada (0-59): "; cin >> minutoSalida;
                                    limpiarBuffer();

                                    if (!validarHoraMinuto(horaSalida, minutoSalida)) {
                                        break;
                                    }
                                    
                                    sistemaParqueadero.salirVehiculo(placaSalir, horaSalida, minutoSalida);
                                    break;
                                }
                                case 5: // Cerrar Sesion
                                    cout << "Cerrando sesion de usuario." << endl;
                                    break;
                                default:
                                    cout << "Opcion no valida, intente de nuevo." << endl;
                            }
                        } catch (const exception& e) {
                            cerr << e.what() << endl; // Captura y muestra errores
                            limpiarBuffer(); // Limpia el buffer despues de un error
                        }
                    }
                } else {
                    cout << "Fallo en la autenticacion. Credenciales incorrectas." << endl;
                }
                break;
            }
            case 3: { // Iniciar Sesion como Administrador
                string user, pass;
                cout << "--- INICIO DE SESION DE ADMINISTRADOR ---" << endl;
                cout << "Usuario: "; getline(cin, user);
                cout << "Contrasena: "; getline(cin, pass);

                Administrador* adminLogueado = sistemaParqueadero.autenticarAdministrador(user, pass);
                if (adminLogueado) {
                    cout << "Sesion iniciada como administrador: " << adminLogueado->getNombreUsuario() << endl;
                    int opc_admin_sub = 0;
                    while (opc_admin_sub != 7) { // 7 es "Cerrar Sesion"
                        opc_admin_sub = menu_administrador();
                        try {
                            switch (opc_admin_sub) {
                                case 1: { // Establecer cantidad y tipo de parqueaderos
                                    int numAutos, numMotos, numMixtos;
                                    cout << "Cantidad de parqueaderos para AUTOMOVILES: "; cin >> numAutos;
                                    cout << "Cantidad de parqueaderos para MOTOS: "; cin >> numMotos;
                                    cout << "Cantidad de parqueaderos MIXTOS: "; cin >> numMixtos;
                                    limpiarBuffer();
                                    sistemaParqueadero.establecerCantidadYTipoParqueaderos(numAutos, numMotos, numMixtos);
                                    break;
                                }
                                case 2: { // Bloquear parqueadero por codigo
                                    string codigoBloquear;
                                    cout << "Ingrese codigo de parqueadero a bloquear (ej. A1, M2, X1): ";
                                    getline(cin, codigoBloquear);
                                    sistemaParqueadero.bloquearParqueaderoPorCodigo(codigoBloquear);
                                    break;
                                }
                                case 3: { // Habilitar parqueadero por codigo
                                    string codigoHabilitar;
                                    cout << "Ingrese codigo de parqueadero a habilitar: ";
                                    getline(cin, codigoHabilitar);
                                    sistemaParqueadero.habilitarParqueaderoPorCodigo(codigoHabilitar);
                                    break;
                                }
                                case 4: { // Establecer tarifa por hora y por tipo de vehiculo
                                    string tipoVehiculoTarifa;
                                    double nuevaTarifa;
                                    cout << "¿Establecer tarifa para 'Automovil' o 'Moto'?: ";
                                    getline(cin, tipoVehiculoTarifa);
                                    transform(tipoVehiculoTarifa.begin(), tipoVehiculoTarifa.end(), tipoVehiculoTarifa.begin(), ::tolower);
                                    if (tipoVehiculoTarifa == "automovil") tipoVehiculoTarifa = "Automovil";
                                    else if (tipoVehiculoTarifa == "moto") tipoVehiculoTarifa = "Moto";
                                    else { cout << "Tipo de vehiculo invalido." << endl; break; }

                                    cout << "Ingrese nueva tarifa por hora: $";
                                    cin >> nuevaTarifa;
                                    limpiarBuffer();
                                    sistemaParqueadero.establecerTarifaPorHoraYTipo(tipoVehiculoTarifa, nuevaTarifa);
                                    break;
                                }
                                case 5: { // Generar reportes
                                    string tipoReporte;
                                    cout << "¿Que tipo de reporte desea? ('estado_actual', 'transacciones_historicas'): ";
                                    getline(cin, tipoReporte);
                                    sistemaParqueadero.generarReportes(tipoReporte);
                                    break;
                                }
                                case 6: { // Mostrar Estado Actual de Parqueaderos
                                    sistemaParqueadero.mostrarEstadoParqueaderos();
                                    break;
                                }
                                case 7: // Cerrar Sesion
                                    cout << "Cerrando sesion de administrador." << endl;
                                    break;
                                default:
                                    cout << "Opcion no valida, intente de nuevo." << endl;
                            }
                        } catch (const exception& e) {
                            cerr << e.what() << endl;
                            limpiarBuffer();
                        }
                    }
                } else {
                    cout << "Credenciales de administrador incorrectas." << endl;
                }
                break;
            }
            case 4:
                cout << "Saliendo del Simulador de Parqueadero Inteligente. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
        }
    }
    
    return 0;
}
