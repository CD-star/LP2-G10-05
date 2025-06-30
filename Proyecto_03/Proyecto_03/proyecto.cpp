#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>   // Para std::shared_ptr
#include <stdexcept> // Para excepciones estándar
#include <iomanip>  // Para std::fixed, std::setprecision, std::setfill, std::setw
#include <limits>   // Para std::numeric_limits
#include <algorithm> // Para std::transform
#include <fstream>  // Para std::ofstream
#include <ctime>    // Para time_t, time, localtime, strftime (solo para el nombre del archivo de reporte)


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
        : std::runtime_error("Error: Vehículo con placa '" + placa + "' no encontrado.") {}
};

class ExcepcionAutenticacion : public std::runtime_error {
public:
    explicit ExcepcionAutenticacion(const std::string& mensaje)
        : std::runtime_error("Error de autenticación: " + mensaje) {}
};

using namespace std;

// --- Clases de Vehículos ---
class Vehiculo {
public:
    string placa;
    string marca;
    string modelo;
    string color;
    string tipoVehiculo; // "Automovil" o "Moto"

    Vehiculo(const string& placa, const string& marca, const string& modelo,
             const string& color, const string& tipoVehiculo)
        : placa(placa), marca(marca), modelo(modelo), color(color), tipoVehiculo(tipoVehiculo) {}

    virtual ~Vehiculo() = default;

    // Método virtual para mostrar información
    virtual void Informacion() const = 0;
    virtual double CalcularTarifa(double horas, double tarifaPorHora) const = 0;

    string getPlaca() const { return placa; }
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    string getColor() const { return color; }
    string getTipoVehiculo() const { return tipoVehiculo; }
};

class Automovil : public Vehiculo {
private:
    int numeroPuertas;
public:
    Automovil(const string& placa, const string& marca, const string& modelo,
              const string& color, int numeroPuertas)
        : Vehiculo(placa, marca, modelo, color, "Automovil"), numeroPuertas(numeroPuertas) {}

    void Informacion() const override {
        cout << "Placa: " << placa
           << ", Tipo: " << tipoVehiculo
           << ", Marca: " << marca
           << ", Modelo: " << modelo
           << ", Color: " << color
           << ", Puertas: " << numeroPuertas << endl;
    }

    double CalcularTarifa(double horas, double tarifaPorHora) const override {
        return horas * tarifaPorHora;
    }
    int getNumeroPuertas() const { return numeroPuertas; }
};

class Moto : public Vehiculo {
private:
    double cilindrada;
public:
    Moto(const string& placa, const string& marca, const string& modelo,
         const string& color, double cilindrada)
        : Vehiculo(placa, marca, modelo, color, "Moto"), cilindrada(cilindrada) {}

    void Informacion() const override {
        cout << "Placa: " << placa
           << ", Tipo: " << tipoVehiculo
           << ", Marca: " << marca
           << ", Modelo: " << modelo
           << ", Color: " << color
           << ", Cilindrada: " << cilindrada << "cc" << endl;
    }

    double CalcularTarifa(double horas, double tarifaPorHora) const override {
        return horas * tarifaPorHora;
    }
    double getCilindrada() const { return cilindrada; }
};

// --- Clase Usuario ---
class Usuario {
private:
    string nombreUsuario;
    string password;
    string nombreCompleto;
    string dni;
    string placaVehiculoAsociada;
public:
    Usuario(const string& user, const string& pass, const string& nombre, const string& dni, const string& placa)
        : nombreUsuario(user), password(pass), nombreCompleto(nombre), dni(dni), placaVehiculoAsociada(placa) {}

    string getNombreUsuario() const { return nombreUsuario; }
    string getPassword() const { return password; }
    string getNombreCompleto() const { return nombreCompleto; }
    string getDni() const { return dni; }
    string getPlacaVehiculoAsociada() const { return placaVehiculoAsociada; }

    void setNombreCompleto(const string& newName) { nombreCompleto = newName; }
    void setDni(const string& newDni) { dni = newDni; }
    void setPlacaVehiculoAsociada(const string& newPlaca) { placaVehiculoAsociada = newPlaca; }
    void setPassword(const string& newPass) { password = newPass; }

    void mostrarInformacionUsuario() const {
        cout << "Usuario: " << nombreUsuario
           << ", Nombre Completo: " << nombreCompleto
           << ", DNI: " << dni
           << ", Placa Asociada: " << placaVehiculoAsociada << endl;
    }
};

// --- Clase Administrador ---
class Administrador {
private:
    string nombreUsuario;
    string contrasena;
public:
    Administrador(const string& user, const string& pass) : nombreUsuario(user), contrasena(pass) {}

    string getNombreUsuario() const { return nombreUsuario; }
    string getContrasena() const { return contrasena; }

    void mostrarInformacionAdmin() const {
        cout << "Admin Usuario: " << nombreUsuario << endl;
    }
};

// --- Clase Parqueadero (Espacio de Estacionamiento) ---
class Parqueadero {
private:
    string codigo;
    string tipoPermitido; // "Automovil", "Moto", "Mixto"
    bool estaOcupado;
    bool estaBloqueado;
    shared_ptr<Vehiculo> vehiculoEstacionado;
    int horaEntradaSimulada;
    int minutoEntradaSimulada;

public:
    Parqueadero(const string& codigo, const string& tipoPermitido)
        : codigo(codigo), tipoPermitido(tipoPermitido), estaOcupado(false),
          estaBloqueado(false), vehiculoEstacionado(nullptr),
          horaEntradaSimulada(-1), minutoEntradaSimulada(-1) {}

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
            throw ExcepcionParqueaderoInvalido("El parqueadero " + codigo + " no está disponible.");
        }
        estaOcupado = true;
        vehiculoEstacionado = vehiculo;
        horaEntradaSimulada = horaActual;
        minutoEntradaSimulada = minutoActual;
        cout << "Parqueadero " << codigo << " ocupado por " << vehiculo->getPlaca() << endl;
    }

    shared_ptr<Vehiculo> desocupar() {
        if (!estaOcupado) {
            throw ExcepcionParqueaderoInvalido("El parqueadero " + codigo + " ya está vacío.");
        }
        estaOcupado = false;
        horaEntradaSimulada = -1;
        minutoEntradaSimulada = -1;
        shared_ptr<Vehiculo> vehiculoQueSalio = vehiculoEstacionado;
        vehiculoEstacionado = nullptr;
        cout << "Parqueadero " << codigo << " desocupado." << endl;
        return vehiculoQueSalio;
    }

    void bloquear() {
        if (estaOcupado) {
            throw ExcepcionParqueaderoInvalido("No se puede bloquear el parqueadero " + codigo + " mientras está ocupado.");
        }
        estaBloqueado = true;
        cout << "Parqueadero " << codigo << " bloqueado." << endl;
    }

    void habilitar() {
        estaBloqueado = false;
        cout << "Parqueadero " << codigo << " habilitado." << endl;
    }

    void mostrarEstadoParqueadero() const {
        cout << "Código: " << codigo
           << ", Tipo: " << tipoPermitido
           << ", Ocupado: " << (estaOcupado ? "Sí" : "No")
           << ", Bloqueado: " << (estaBloqueado ? "Sí" : "No");
        if (estaOcupado && vehiculoEstacionado) {
            cout << ", Vehículo: [";
            vehiculoEstacionado->Informacion(); // Llama al método de información del vehículo
            cout << "], Entrada (simulada): " << setfill('0') << setw(2) << horaEntradaSimulada
               << ":" << setfill('0') << setw(2) << minutoEntradaSimulada;
        }
        cout << endl;
    }
};

// --- Estructura de Registro de Transacción para Reportes ---
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
           << ", Código Parqueadero: " << codigoParqueadero
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
    map<string, Parqueadero> espaciosParqueadero;
    map<string, shared_ptr<Vehiculo>> vehiculosActivos;
    map<string, double> tarifasPorTipo;
    vector<RegistroTransaccion> historialTransacciones;

    int nextCarParkingCode;
    int nextMotoParkingCode;
    int nextMixedParkingCode;

    string generarCodigoParqueadero(const string& tipo) {
        if (tipo == "Automovil") {
            return "A" + to_string(nextCarParkingCode++);
        } else if (tipo == "Moto") {
            return "M" + to_string(nextMotoParkingCode++);
        } else if (tipo == "Mixto") {
            return "X" + to_string(nextMixedParkingCode++);
        }
        return "INV";
    }

    void escribirReporteEnArchivo(const string& contenido, const string& nombreArchivo) const {
        ofstream archivoSalida(nombreArchivo);
        if (!archivoSalida.is_open()) {
            throw ExcepcionParqueaderoInvalido("No se pudo abrir o crear el archivo: " + nombreArchivo);
        }
        archivoSalida << contenido;
        archivoSalida.close();
    }

public:
    SistemaParqueadero() : nextCarParkingCode(1), nextMotoParkingCode(1), nextMixedParkingCode(1) {
        administradoresRegistrados.emplace("admin", Administrador("admin", "admin123"));
        tarifasPorTipo["Automovil"] = 0.0;
        tarifasPorTipo["Moto"] = 0.0;
    }

    // --- Gestión General de Acceso y Usuarios ---
    bool registrarUsuario(const string& user, const string& pass,
                          const string& nombre, const string& dni, const string& placa) {
        if (usuariosRegistrados.count(user)) {
            cout << "El nombre de usuario '" << user << "' ya existe." << endl;
            return false;
        }
        usuariosRegistrados.emplace(user, Usuario(user, pass, nombre, dni, placa));
        cout << "Usuario '" << user << "' registrado exitosamente." << endl;
        return true;
    }

    Usuario* autenticarUsuario(const string& user, const string& pass) {
        auto it = usuariosRegistrados.find(user);
        if (it != usuariosRegistrados.end() && it->second.getPassword() == pass) {
            return &(it->second);
        }
        return nullptr;
    }

    Administrador* autenticarAdministrador(const string& user, const string& pass) {
        auto it = administradoresRegistrados.find(user);
        if (it != administradoresRegistrados.end() && it->second.getContrasena() == pass) {
            return &(it->second);
        }
        return nullptr;
    }

    void actualizarDatosUsuario(Usuario& usuario, const string& nuevoNombre, const string& nuevoDni, const string& nuevaPlaca) {
        usuario.setNombreCompleto(nuevoNombre);
        usuario.setDni(nuevoDni);
        usuario.setPlacaVehiculoAsociada(nuevaPlaca);
        cout << "Datos del usuario " << usuario.getNombreUsuario() << " actualizados." << endl;
    }

    // --- Funcionalidad del Administrador ---
    void establecerCantidadYTipoParqueaderos(int numAutomoviles, int numMotos, int numMixtos) {
        espaciosParqueadero.clear();
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
        cout << "Parqueaderos inicializados: " << numAutomoviles << " Automóvil(es), "
             << numMotos << " Moto(s), " << numMixtos << " Mixto(s)." << endl;
    }

    void establecerTarifaPorHoraYTipo(const string& tipoVehiculo, double tarifa) {
        if (tarifasPorTipo.count(tipoVehiculo)) {
            tarifasPorTipo[tipoVehiculo] = tarifa;
            cout << "Tarifa para " << tipoVehiculo << " establecida a $" << fixed << setprecision(2) << tarifa << "/hora." << endl;
        } else {
            cout << "Tipo de vehículo '" << tipoVehiculo << "' no válido." << endl;
        }
    }

    void bloquearParqueaderoPorCodigo(const string& codigo) {
        auto it = espaciosParqueadero.find(codigo);
        if (it != espaciosParqueadero.end()) {
            it->second.bloquear();
        } else {
            throw ExcepcionParqueaderoInvalido("El parqueadero '" + codigo + "' no existe.");
        }
    }

    void habilitarParqueaderoPorCodigo(const string& codigo) {
        auto it = espaciosParqueadero.find(codigo);
        if (it != espaciosParqueadero.end()) {
            it->second.habilitar();
        } else {
            throw ExcepcionParqueaderoInvalido("El parqueadero '" + codigo + "' no existe.");
        }
    }

    void generarReportes(const string& tipoReporte) {
        string contenidoReporte;
        string nombreArchivo;
        // Para el nombre del archivo, se sigue usando la fecha y hora reales del sistema
        time_t now = time(0);
        char date_buffer[80];
        strftime(date_buffer, sizeof(date_buffer), "%Y%m%d_%H%M%S", localtime(&now));
        string timestamp_str = date_buffer;

        if (tipoReporte == "estado_actual") {
            nombreArchivo = "reporte_estado_actual_" + timestamp_str + ".txt";
            contenidoReporte += "--- Reporte de Estado Actual del Parqueadero ---\n";
            contenidoReporte += "Fecha y Hora de Generación: " + string(date_buffer) + "\n\n";

            contenidoReporte += "Tarifas Actuales:\n";
            for (const auto& par : tarifasPorTipo) {
                contenidoReporte += "  " + par.first + ": $" + to_string(par.second) + "/hora\n";
            }
            contenidoReporte += "\nParqueaderos:\n";
            for (const auto& par : espaciosParqueadero) {
                contenidoReporte += "  Código: " + par.second.getCodigo() +
                                   ", Tipo: " + par.second.getTipoPermitido() +
                                   ", Ocupado: " + (par.second.getEstaOcupado() ? "Sí" : "No") +
                                   ", Bloqueado: " + (par.second.getEstaBloqueado() ? "Sí" : "No");
                if (par.second.getEstaOcupado() && par.second.getVehiculoEstacionado()) {
                    contenidoReporte += ", Vehículo: " + par.second.getVehiculoEstacionado()->getPlaca();
                    contenidoReporte += ", Entrada (simulada): " + to_string(par.second.getHoraEntradaSimulada()) +
                                        ":" + to_string(par.second.getMinutoEntradaSimulada());
                }
                contenidoReporte += "\n";
            }
            contenidoReporte += "\nVehículos actualmente estacionados (seguimiento interno):\n";
            if (vehiculosActivos.empty()) {
                contenidoReporte += "  Ningún vehículo estacionado actualmente.\n";
            } else {
                for (const auto& par : vehiculosActivos) {
                    contenidoReporte += "  " + par.second->getPlaca() + " (" + par.second->getTipoVehiculo() + ")\n";
                }
            }

        } else if (tipoReporte == "transacciones_historicas") {
            nombreArchivo = "reporte_transacciones_historicas_" + timestamp_str + ".txt";
            contenidoReporte += "--- Reporte de Transacciones Históricas ---\n";
            if (historialTransacciones.empty()) {
                contenidoReporte += "No hay transacciones registradas.\n";
            } else {
                for (const auto& reg : historialTransacciones) {
                    // Aquí se construye la cadena para el archivo sin usar el operador <<
                    contenidoReporte += "Placa: " + reg.placa +
                                        ", Tipo: " + reg.tipoVehiculo +
                                        ", Código Parqueadero: " + reg.codigoParqueadero +
                                        ", Entrada (simulada): " + to_string(reg.horaEntradaSimulada) + ":" + to_string(reg.minutoEntradaSimulada) +
                                        ", Salida (simulada): " + to_string(reg.horaSalidaSimulada) + ":" + to_string(reg.minutoSalidaSimulada) +
                                        ", Horas: " + to_string(fixed_double_precision(reg.horasEstacionado, 2)) +
                                        ", Pago: $" + to_string(fixed_double_precision(reg.montoPagado, 2)) + "\n";
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

    // Helper para formatear doubles con precisión para strings
    string fixed_double_precision(double value, int precision) const {
        stringstream ss;
        ss << fixed << setprecision(precision) << value;
        return ss.str();
    }

    void mostrarEstadoParqueaderos() const {
        cout << "\n--- Estado Actual de los Parqueaderos ---" << endl;
        if (espaciosParqueadero.empty()) {
            cout << "No hay parqueaderos configurados." << endl;
            return;
        }
        for (const auto& pair : espaciosParqueadero) {
            pair.second.mostrarEstadoParqueadero(); // Llama al método de cada objeto Parqueadero
        }
    }

    // --- Funcionalidad del Usuario ---
    int verificarDisponibilidad(const string& tipoVehiculo) const {
        int count = 0;
        for (const auto& par : espaciosParqueadero) {
            if (par.second.estaDisponible()) {
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
            Parqueadero& p = pair.second;
            if (p.estaDisponible() && (p.getTipoPermitido() == vehiculo->getTipoVehiculo() || p.getTipoPermitido() == "Mixto")) {
                p.ocupar(vehiculo, horaActual, minutoActual);
                vehiculosActivos.emplace(vehiculo->getPlaca(), vehiculo);
                return p.getCodigo();
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

        for (auto& pair : espaciosParqueadero) {
            Parqueadero& p = pair.second;
            if (p.getEstaOcupado() && p.getVehiculoEstacionado() && p.getVehiculoEstacionado()->getPlaca() == placa) {
                codigoParqueaderoOcupado = p.getCodigo();

                int horaEntrada = p.getHoraEntradaSimulada();
                int minutoEntrada = p.getMinutoEntradaSimulada();

                double totalMinutosEntrada = horaEntrada * 60 + minutoEntrada;
                double totalMinutosSalida = horaSalida * 60 + minutoSalida;

                double minutosEstacionado = totalMinutosSalida - totalMinutosEntrada;
                if (minutosEstacionado < 0) {
                    minutosEstacionado += (24 * 60);
                }
                if (minutosEstacionado < 1) minutosEstacionado = 1;

                double horasEstacionado = minutosEstacionado / 60.0;

                double tarifaPorHora = tarifasPorTipo[vehiculoQueSale->getTipoVehiculo()];
                double montoAPagar = vehiculoQueSale->CalcularTarifa(horasEstacionado, tarifaPorHora);

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

                p.desocupar();
                vehiculosActivos.erase(itVehiculo);
                cout << "Vehículo con placa " << placa << " ha salido de " << codigoParqueaderoOcupado << ". ";
                cout << "Horas estacionado: " << fixed << setprecision(2) << horasEstacionado << "h. ";
                cout << "Monto a pagar: $" << fixed << setprecision(2) << montoAPagar << endl;
                return montoAPagar;
            }
        }
        throw ExcepcionParqueaderoInvalido("Error interno: Parqueadero del vehículo '" + placa + "' no encontrado.");
    }
};

// --- Funciones de Menú ---
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool validarHoraMinuto(int hora, int minuto) {
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        cout << "Hora o minuto inválido. Ingrese valores entre [0-23] para hora y [0-59] para minuto." << endl;
        return false;
    }
    return true;
}

void menu_principal() {
    cout << "1. Iniciar Sesión como Usuario" << endl;
    cout << "2. Iniciar Sesión como Administrador" << endl;
    cout << "3. Registrarse como Usuario" << endl;
    cout << "4. Salir" << endl;
}

int menu_usuario() {
    int opc = 0;
    cout << endl;
    cout << "----------------------" << endl;
    cout << "Menú Usuario" << endl;
    cout << "1. Actualizar mis datos" << endl;
    cout << "2. Verificar Disponibilidad de Parqueadero" << endl;
    cout << "3. Ingresar mi Vehículo" << endl;
    cout << "4. Salir mi Vehículo y Pagar" << endl;
    cout << "5. Cerrar Sesión" << endl;
    cout << "Ingrese una opción: ";
    cin >> opc;
    return opc;
}

int menu_administrador() {
    int opc = 0;
    cout << endl;
    cout << "----------------------" << endl;
    cout << "Menú Administrador" << endl;
    cout << "1. Establecer cantidad y tipo de parqueaderos" << endl;
    cout << "2. Bloquear parqueadero por código" << endl;
    cout << "3. Habilitar parqueadero por código" << endl;
    cout << "4. Establecer tarifa por hora y por tipo de vehículo" << endl;
    cout << "5. Generar reportes" << endl;
    cout << "6. Mostrar Estado Actual de Parqueaderos" << endl;
    cout << "7. Cerrar Sesión" << endl;
    cout << "Ingrese una opción: ";
    cin >> opc;
    return opc;
}

// --- Función Principal ---
int main() {
    SistemaParqueadero sistemaParqueadero;

    cout << "--- Configuración Inicial del Administrador ---" << endl;
    int numAutos, numMotos, numMixtos;
    double tarifaAuto, tarifaMoto;

    cout << "Ingrese cantidad de parqueaderos para AUTOMÓVILES: ";
    cin >> numAutos;
    cout << "Ingrese cantidad de parqueaderos para MOTOS: ";
    cin >> numMotos;
    cout << "Ingrese cantidad de parqueaderos MIXTOS: ";
    cin >> numMixtos;
    limpiarBuffer();
    sistemaParqueadero.establecerCantidadYTipoParqueaderos(numAutos, numMotos, numMixtos);

    cout << "Establecer tarifa por hora para AUTOMÓVILES: $";
    cin >> tarifaAuto;
    cout << "Establecer tarifa por hora para MOTOS: $";
    cin >> tarifaMoto;
    limpiarBuffer();
    sistemaParqueadero.establecerTarifaPorHoraYTipo("Automovil", tarifaAuto);
    sistemaParqueadero.establecerTarifaPorHoraYTipo("Moto", tarifaMoto);
    cout << "Configuración inicial completa." << endl;

    int opc_principal = 0;
    while (opc_principal != 4) {
        cout << endl;
        cout << "----------------------" << endl;
        menu_principal();
        cout << "Ingrese una opción: ";
        cin >> opc_principal;
        limpiarBuffer();

        switch (opc_principal) {
            case 1: { // Iniciar Sesión como Usuario
                string user, pass;
                cout << "--- INICIO DE SESIÓN DE USUARIO ---" << endl;
                cout << "Usuario: "; getline(cin, user);
                cout << "Contraseña: "; getline(cin, pass);

                Usuario* usuarioLogueado = sistemaParqueadero.autenticarUsuario(user, pass);
                if (usuarioLogueado) {
                    cout << "Sesión iniciada como usuario: " << usuarioLogueado->getNombreUsuario() << endl;
                    int opc_usuario_sub = 0;
                    while (opc_usuario_sub != 5) {
                        opc_usuario_sub = menu_usuario();
                        try {
                            switch (opc_usuario_sub) {
                                case 1: { // Actualizar datos
                                    string nuevoNombre, nuevoDni, nuevaPlaca;
                                    cout << "Ingrese nuevo nombre completo: "; getline(cin, nuevoNombre);
                                    cout << "Ingrese nuevo DNI: "; getline(cin, nuevoDni);
                                    cout << "Ingrese nueva placa de vehículo: "; getline(cin, nuevaPlaca);
                                    sistemaParqueadero.actualizarDatosUsuario(*usuarioLogueado, nuevoNombre, nuevoDni, nuevaPlaca);
                                    break;
                                }
                                case 2: { // Verificar Disponibilidad
                                    string tipoVehiculoDisp;
                                    cout << "¿Verificar disponibilidad para 'Automovil' o 'Moto'?: ";
                                    getline(cin, tipoVehiculoDisp);
                                    transform(tipoVehiculoDisp.begin(), tipoVehiculoDisp.end(), tipoVehiculoDisp.begin(), ::tolower);
                                    if (tipoVehiculoDisp == "automovil") tipoVehiculoDisp = "Automovil";
                                    else if (tipoVehiculoDisp == "moto") tipoVehiculoDisp = "Moto";
                                    else { cout << "Tipo de vehículo inválido." << endl; break; }

                                    int disponibles = sistemaParqueadero.verificarDisponibilidad(tipoVehiculoDisp);
                                    cout << "Parqueaderos disponibles para " << tipoVehiculoDisp << ": " << disponibles << endl;
                                    break;
                                }
                                case 3: { // Ingresar Vehículo
                                    string placa = usuarioLogueado->getPlacaVehiculoAsociada();
                                    if (placa.empty()) {
                                        cout << "Su perfil no tiene una placa de vehículo asociada. Por favor, actualice sus datos primero." << endl;
                                        break;
                                    }
                                    string tipoVehiculo;
                                    cout << "¿Su vehículo es un 'Automovil' o una 'Moto'?: ";
                                    getline(cin, tipoVehiculo);
                                    transform(tipoVehiculo.begin(), tipoVehiculo.end(), tipoVehiculo.begin(), ::tolower);
                                    if (tipoVehiculo == "automovil") tipoVehiculo = "Automovil";
                                    else if (tipoVehiculo == "moto") tipoVehiculo = "Moto";
                                    else { cout << "Tipo de vehículo inválido." << endl; break; }

                                    string marca, modelo, color;
                                    int horaEntrada, minutoEntrada;
                                    cout << "Marca: "; getline(cin, marca);
                                    cout << "Modelo: "; getline(cin, modelo);
                                    cout << "Color: "; getline(cin, color);
                                    cout << "Hora de entrada simulada (0-23): "; cin >> horaEntrada;
                                    cout << "Minuto de entrada simulada (0-59): "; cin >> minutoEntrada;
                                    limpiarBuffer();

                                    if (!validarHoraMinuto(horaEntrada, minutoEntrada)) {
                                        break;
                                    }

                                    shared_ptr<Vehiculo> nuevoVehiculo;
                                    if (tipoVehiculo == "Automovil") {
                                        int numPuertas;
                                        cout << "Número de puertas: "; cin >> numPuertas; limpiarBuffer();
                                        nuevoVehiculo = make_shared<Automovil>(placa, marca, modelo, color, numPuertas);
                                    } else {
                                        double cilindrada;
                                        cout << "Cilindrada (cc): "; cin >> cilindrada; limpiarBuffer();
                                        nuevoVehiculo = make_shared<Moto>(placa, marca, modelo, color, cilindrada);
                                    }
                                    sistemaParqueadero.ingresarVehiculo(nuevoVehiculo, horaEntrada, minutoEntrada);
                                    break;
                                }
                                case 4: { // Salir Vehículo y Pagar
                                    string placaSalir = usuarioLogueado->getPlacaVehiculoAsociada();
                                    if (placaSalir.empty()) {
                                        cout << "Su perfil no tiene una placa de vehículo asociada para salir." << endl;
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
                                case 5: // Cerrar Sesión
                                    cout << "Cerrando sesión de usuario." << endl;
                                    break;
                                default:
                                    cout << "Opción no válida, intente de nuevo." << endl;
                            }
                        } catch (const exception& e) {
                            cerr << e.what() << endl;
                            limpiarBuffer();
                        }
                    }
                } else {
                    cout << "Fallo en la autenticación. Credenciales incorrectas." << endl;
                }
                break;
            }
            case 2: { // Iniciar Sesión como Administrador
                string user, pass;
                cout << "--- INICIO DE SESIÓN DE ADMINISTRADOR ---" << endl;
                cout << "Usuario: "; getline(cin, user);
                cout << "Contraseña: "; getline(cin, pass);

                Administrador* adminLogueado = sistemaParqueadero.autenticarAdministrador(user, pass);
                if (adminLogueado) {
                    cout << "Sesión iniciada como administrador: " << adminLogueado->getNombreUsuario() << endl;
                    int opc_admin_sub = 0;
                    while (opc_admin_sub != 7) {
                        opc_admin_sub = menu_administrador();
                        try {
                            switch (opc_admin_sub) {
                                case 1: {
                                    int numAutos, numMotos, numMixtos;
                                    cout << "Cantidad de parqueaderos para AUTOMÓVILES: "; cin >> numAutos;
                                    cout << "Cantidad de parqueaderos para MOTOS: "; cin >> numMotos;
                                    cout << "Cantidad de parqueaderos MIXTOS: "; cin >> numMixtos;
                                    limpiarBuffer();
                                    sistemaParqueadero.establecerCantidadYTipoParqueaderos(numAutos, numMotos, numMixtos);
                                    break;
                                }
                                case 2: {
                                    string codigoBloquear;
                                    cout << "Ingrese código de parqueadero a bloquear (ej. A1, M2, X1): ";
                                    getline(cin, codigoBloquear);
                                    sistemaParqueadero.bloquearParqueaderoPorCodigo(codigoBloquear);
                                    break;
                                }
                                case 3: {
                                    string codigoHabilitar;
                                    cout << "Ingrese código de parqueadero a habilitar: ";
                                    getline(cin, codigoHabilitar);
                                    sistemaParqueadero.habilitarParqueaderoPorCodigo(codigoHabilitar);
                                    break;
                                }
                                case 4: {
                                    string tipoVehiculoTarifa;
                                    double nuevaTarifa;
                                    cout << "¿Establecer tarifa para 'Automovil' o 'Moto'?: ";
                                    getline(cin, tipoVehiculoTarifa);
                                    transform(tipoVehiculoTarifa.begin(), tipoVehiculoTarifa.end(), tipoVehiculoTarifa.begin(), ::tolower);
                                    if (tipoVehiculoTarifa == "automovil") tipoVehiculoTarifa = "Automovil";
                                    else if (tipoVehiculoTarifa == "moto") tipoVehiculoTarifa = "Moto";
                                    else { cout << "Tipo de vehículo inválido." << endl; break; }

                                    cout << "Ingrese nueva tarifa por hora: $";
                                    cin >> nuevaTarifa;
                                    limpiarBuffer();
                                    sistemaParqueadero.establecerTarifaPorHoraYTipo(tipoVehiculoTarifa, nuevaTarifa);
                                    break;
                                }
                                case 5: {
                                    string tipoReporte;
                                    cout << "¿Qué tipo de reporte desea? ('estado_actual', 'transacciones_historicas'): ";
                                    getline(cin, tipoReporte);
                                    sistemaParqueadero.generarReportes(tipoReporte);
                                    break;
                                }
                                case 6: {
                                    sistemaParqueadero.mostrarEstadoParqueaderos();
                                    break;
                                }
                                case 7:
                                    cout << "Cerrando sesión de administrador." << endl;
                                    break;
                                default:
                                    cout << "Opción no válida, intente de nuevo." << endl;
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
            case 3: {
                string user, pass, nombre, dni, placa;
                cout << "--- REGISTRO DE NUEVO USUARIO ---" << endl;
                cout << "Ingrese nombre de usuario: "; getline(cin, user);
                cout << "Ingrese contraseña: "; getline(cin, pass);
                cout << "Ingrese su nombre completo: "; getline(cin, nombre);
                cout << "Ingrese su DNI: "; getline(cin, dni);
                cout << "Ingrese la placa de su vehículo (ej. ABC-123): "; getline(cin, placa);
                sistemaParqueadero.registrarUsuario(user, pass, nombre, dni, placa);
                break;
            }
            case 4:
                cout << "Saliendo del Simulador de Parqueadero Inteligente. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida, intente de nuevo." << endl;
        }
    }

    return 0;
}