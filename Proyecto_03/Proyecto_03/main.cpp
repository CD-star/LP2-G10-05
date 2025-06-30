#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Vehiculo {
    public:
        virtual void Informacion() = 0;
        virtual void CalcularTarifa() = 0;
};

class Automovil : public Vehiculo {
    private:
        string placa;
        double tarifaPorHora = 2.5;
    public:
        Automovil(const string& placa) : placa(placa) {}

        void Informacion() override {
            cout << "El automovil con placa " << placa << endl;
        }
        void CalcularTarifa() override {
            cout << "Calcular Tarifa del Automovil" << endl;
        }
        void setTarifaPorHora(double tarifa) {
            tarifaPorHora = tarifa;
        }
};

class Moto : public Vehiculo {
    private:
        string placa;
        double tarifaPorHora = 1.5;
    public:
        Moto(const string& placa) : placa(placa) {}

        void Informacion() override {
            cout << "El moto con placa " << placa << endl;
        }
        void CalcularTarifa() override {
            cout << "Calcular Tarifa de la Moto" << endl;
        }

        void setTarifaPorHora(double tarifa) {
            tarifaPorHora = tarifa;
        }
};

class Usuario {
    private:
        string nombre;
    public:
};

class Administrador {
    private:
        string nombre;
        string contrasena;
    public:
        void EstablecerCantidadYTipoParqueaderos() {
            cout << "Establecer cantidad y tipo de parqueaderos" << endl;
        }
        void BloquearParqueaderoPorCodigo() {
            cout << "Bloquear parqueadero por codigo" << endl;
        }
        void HabilitarParqueaderoPorCodigo() {
            cout << "Habilitar parqueadero por codigo" << endl;
        }
        void EstablecerTarifaPorHoraYTipo() {
            cout << "Establecer tarifa por hora y por tipo de parqueadero" << endl;
            cout << "Ingrese tipo de parqueadero (Automovil/Moto): ";
            string tipo;
            double tarifa;
            cin >> tarifa;
            if (tipo == "Automovil") {
                
            } else if (tipo == "Moto") {
                
            } else {
                cout << "Tipo de parqueadero no valido." << endl;
            }
        }
        void GenerarReportes() {
            cout << "Generar reportes" << endl;
        }
};

class Parqueadero {
    private:
        string nombre;
        string ubicacion;
        int capacidad;
        map<string, Vehiculo*> vehiculos;
    public:
};

class SistemaParqueadero {
    private:
        vector<Usuario> usuarios;
        vector<Administrador> administradores;
        vector<Parqueadero> parqueaderos;
    public:
        void RegistrarUsuario(const Usuario& usuario) {
            usuarios.push_back(usuario);
        }
        void RegistrarAdministrador(const Administrador& administrador) {
            administradores.push_back(administrador);
        }
        void AgregarParqueadero(const Parqueadero& parqueadero) {
            parqueaderos.push_back(parqueadero);
        }

};


void menu_principal() {
    cout << "1. Registrarse" << endl;
    cout << "2. Inicio Usuario" << endl;
    cout << "3. Inicio Aministrador" << endl;
    cout << "4. Salir" << endl;
}

int menu_usuario() {
    int opc = 0;
    cout << endl;
    cout << "----------------------" << endl;
    cout << "Menu Usuario" << endl;
    cout << "1. Ver Datos" << endl;
    cout << "2. Editar Datos" << endl;
    cout << "3. Ingresar " << endl;
    cout << "4. Regresar" << endl;
    cout << "5. Pagar Tarifa" << endl;
    cout << "Ingrese una opcion" << endl;
    cin >> opc;
    return opc;
}

int menu_administrador() {
    int opc = 0;
    cout << endl;
    cout << "----------------------" << endl;
    cout << "Menu Administrador" << endl;
    cout << "1. Establecer cantidad y tipo de parqueaderos " << endl;
    cout << "2. Bloquear parqueadero por codigo" << endl;
    cout << "3. Habilitar parqueadero por codigo" << endl;
    cout << "4. Establecer tarifa por hora y por tipo de parqueadero" << endl;
    cout << "5. Generar reportes" << endl;
    cout << "6. Regresar" << endl;
    cin >> opc;
    return opc;
}

int main(){
    int opc = 0;
    while (opc != 4) {
        cout << endl;
        cout << "----------------------" << endl;
        menu_principal();
        cout << "Ingrese una opcion: ";
        cin >> opc;

        switch (opc) {
            case 1:
                cout << "Registrarse" << endl;
                break;
            case 2: // Inicio Usuario
                opc = menu_usuario();
                switch (opc) {
                    case 1:
                        cout << "Ver Datos" << endl;
                        break;
                    case 2:
                        cout << "Editar Datos" << endl;
                        break;
                    case 3:
                        cout << "Ingresar" << endl;
                        break;
                    case 4:
                        cout << "Regresar" << endl;
                        break;
                    case 5:
                        cout << "Pagar Tarifa" << endl;
                        break;
                    default:
                        cout << "Opcion no valida, intente de nuevo." << endl;
                }
                break;
            case 3: // Inicio Administrador
                opc = menu_administrador();
                switch (opc) {
                    case 1:
                        cout << "Establecer cantidad y tipo de parqueaderos" << endl;
                        break;
                    case 2:
                        cout << "Bloquear parqueadero por codigo" << endl;
                        break;
                    case 3:
                        cout << "Habilitar parqueadero por codigo" << endl;
                        break;
                    case 4:
                        cout << "Establecer tarifa por hora y por tipo de parqueadero" << endl;
                        break;
                    case 5:
                        cout << "Generar reportes" << endl;
                        break;
                    case 6:
                        cout << "Regresar" << endl;
                        break;
                    default:
                        cout << "Opcion no valida, intente de nuevo." << endl;
                }  
                break;
            case 4:
                cout << "Salir" << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
        }
    }
    
    return 0;
}