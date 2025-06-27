#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Contacto {
private:
    string nombre;
    string telefono;
    string email;
public:
    Contacto(const string& nombre, const string& telefono, const string& email)
        : nombre(nombre), telefono(telefono), email(email) {}

    void mostrarInformacion() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "Email: " << email << endl;
    }

    string getNombre() const {
        return nombre;
    }
};

class Agenda {
private:
    vector<Contacto> contactos;
public:
    void agregarContacto(const Contacto& contacto) {
        contactos.push_back(contacto);
        cout << "Contacto '" << contacto.getNombre() << "' agregado a la agenda.\n";
    }
    void buscarContactoPorNombre(const string& nombre) const {
        auto it = find_if(contactos.begin(), contactos.end(), [&nombre](const Contacto& contacto) {
            return contacto.getNombre() == nombre;
        });

        if (it != contactos.end()) {
            cout << "Contacto encontrado:\n";
            it->mostrarInformacion();
        } else {
            cout << "Contacto con nombre '" << nombre << "' no encontrado.\n";
        }
    }
    void actualizarContacto(const string& nombre, const string& telefono, const string& email) {
        auto it = find_if(contactos.begin(), contactos.end(), [&nombre](const Contacto& contacto) {
            return contacto.getNombre() == nombre;
        });

        if (it != contactos.end()) {
            *it = Contacto(nombre, telefono, email);
            cout << "Contacto '" << nombre << "' actualizado.\n";
        } else {
            cout << "Contacto con nombre '" << nombre << "' no encontrado.\n";
        }
    }
    void mostrarContactosOrdenados() const {
        if (contactos.empty()) {
            cout << "No hay contactos registrados.\n";
            return;
        }
        vector<Contacto> contactosOrdenados = contactos;
        sort(contactosOrdenados.begin(), contactosOrdenados.end(), [](const Contacto& a, const Contacto& b) {
            return a.getNombre() < b.getNombre();
        });
        cout << "\n--- Lista de contactos ordenada por nombre ---\n";
        for (const auto& contacto : contactosOrdenados) {
            contacto.mostrarInformacion();
            cout << "----------------------------------\n";
        }
    }
    ~Agenda() {
        cout << "Destructor de Agenda llamado. Todos los contactos han sido eliminados.\n";
    }
};

int main() {
    Agenda agenda;
    int opcion = 0;

    while (opcion != 6) {
        cout << "\n--- MENU AGENDA ---\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Buscar contacto por nombre\n";
        cout << "3. Actualizar contacto\n";
        cout << "4. Mostrar contactos ordenados\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                string nombre, telefono, email;
                cout << "Ingrese el nombre del contacto: ";
                getline(cin, nombre);
                cout << "Ingrese el telefono del contacto: ";
                getline(cin, telefono);
                cout << "Ingrese el email del contacto: ";
                getline(cin, email);
                agenda.agregarContacto(Contacto(nombre, telefono, email));
                break;
            }
            case 2: {
                string nombre;
                cout << "Ingrese el nombre del contacto a buscar: ";
                getline(cin, nombre);
                agenda.buscarContactoPorNombre(nombre);
                break;
            }
            case 3: {
                string nombre, telefono, email;
                cout << "Ingrese el nombre del contacto a actualizar: ";
                getline(cin, nombre);
                cout << "Ingrese el nuevo telefono del contacto: ";
                getline(cin, telefono);
                cout << "Ingrese el nuevo email del contacto: ";
                getline(cin, email);
                agenda.actualizarContacto(nombre, telefono, email);
                break;
            }
            case 4: {
                agenda.mostrarContactosOrdenados();
                break;
            }
            case 5:
                cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                break;
        }
    }

    return 0;
}
