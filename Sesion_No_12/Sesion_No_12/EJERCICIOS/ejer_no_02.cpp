#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <limits> // Necesario para numeric_limits

using namespace std;

class Invitado {
private:
    string nombre;
public:
    Invitado(const string& nombre) : nombre(nombre) {}
    string getNombre() const {
        return nombre;
    }
};

class Evento {
private:
    string nombreEvento;
    string fechaEvento;
    list<Invitado> invitados;
public:
    Evento() : nombreEvento(""), fechaEvento("") {}
    Evento(const string& nombre, const string& fecha) : nombreEvento(nombre), fechaEvento(fecha) {}

    void agregarInvitado(const string& nombre) {
        invitados.emplace_back(nombre);
        cout << "Invitado '" << nombre << "' agregado al evento '" << nombreEvento << "'.\n";
    }

    void mostrarInvitados() const {
        cout << "\n--- Lista de invitados para el evento '" << nombreEvento << "' ---\n";
        if (invitados.empty()) {
            cout << "No hay invitados registrados para este evento.\n";
            return;
        }

        list<Invitado> invitados_copia = invitados;
        invitados_copia.sort([](const Invitado& a, const Invitado& b) {
            return a.getNombre() < b.getNombre();
        });

        for (const auto& invitado : invitados_copia) {
            cout << "- " << invitado.getNombre() << endl;
        }
        cout << "-----------------------------------------------------\n";
    }

    void setNombre(const string& nombre) {
        nombreEvento = nombre;
    }

    void setFecha(const string& fecha) {
        fechaEvento = fecha;
    }

    string getNombre() const {
        return nombreEvento;
    }

    string getFecha() const {
        return fechaEvento;
    }
};

class Organizador_Eventos {
private:
    list<Evento> eventos;
public:
    void agregarEvento(const Evento& evento) {
        eventos.push_back(evento);
        cout << "Evento '" << evento.getNombre() << "' agregado al organizador.\n";
    }

    void agregarInvitadoAEvento(const string& nombreEvento, const string& nombreInvitado) {
        for (auto& evento : eventos) {
            if (evento.getNombre() == nombreEvento) {
                evento.agregarInvitado(nombreInvitado);
                return;
            }
        }
        cout << "Evento '" << nombreEvento << "' no encontrado.\n";
    }

    void mostrarInvitadosDeEventoOrdenado(const string& nombreEvento) const {
        for (const auto& evento : eventos) {
            if (evento.getNombre() == nombreEvento) {
                evento.mostrarInvitados();
                return;
            }
        }
        cout << "Evento '" << nombreEvento << "' no encontrado.\n";
    }

    void buscarEventoPorFecha(const string& fecha) const {
        auto it = find_if(eventos.begin(), eventos.end(), [&fecha](const Evento& evento) {
            return evento.getFecha() == fecha;
        });

        if (it != eventos.end()) {
            cout << "\nEvento encontrado:\n";
            cout << "Nombre: " << it->getNombre() << "\nFecha: " << it->getFecha() << endl;
        } else {
            cout << "\nEvento con fecha '" << fecha << "' no encontrado.\n";
        }
    }

    void mostrarEventos() const {
        cout << "\n--- Lista de todos los eventos ---\n";
        if (eventos.empty()) {
            cout << "No hay eventos registrados.\n";
            return;
        }
        for (const auto& evento : eventos) {
            cout << "Evento: " << evento.getNombre() << ", Fecha: " << evento.getFecha() << endl;
        }
        cout << "----------------------------------\n";
    }
};

int main() {
    Organizador_Eventos organizador;
    int opcion = 0;
    string inputNombre, inputFecha, inputInvitado;

    while(opcion != 6){
        cout << "\n--- MENU ORGANIZADOR DE EVENTOS ---\n";
        cout << "1. Agregar evento\n";
        cout << "2. Agregar invitado a evento\n";
        cout << "3. Mostrar invitados de evento (ordenado)\n";
        cout << "4. Buscar evento por fecha\n";
        cout << "5. Mostrar todos los eventos\n";
        cout << "6. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                cout << "Ingrese el nombre del evento: ";
                getline(cin, inputNombre);
                cout << "Ingrese la fecha del evento (DD/MM/AAAA): ";
                getline(cin, inputFecha);
                Evento nuevoEvento(inputNombre, inputFecha);
                organizador.agregarEvento(nuevoEvento);
                break;
            }
            case 2: {
                cout << "Ingrese el nombre del evento al que agregar invitado: ";
                getline(cin, inputNombre);
                cout << "Ingrese el nombre del invitado: ";
                getline(cin, inputInvitado);
                organizador.agregarInvitadoAEvento(inputNombre, inputInvitado);
                break;
            }
            case 3: {
                cout << "Ingrese el nombre del evento para mostrar sus invitados: ";
                getline(cin, inputNombre);
                organizador.mostrarInvitadosDeEventoOrdenado(inputNombre);
                break;
            }
            case 4: {
                cout << "Ingrese la fecha del evento a buscar (DD/MM/AAAA): ";
                getline(cin, inputFecha);
                organizador.buscarEventoPorFecha(inputFecha);
                break;
            }
            case 5: {
                organizador.mostrarEventos();
                break;
            }
            case 6:
                cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                break;
        }
    }

    return 0;
}