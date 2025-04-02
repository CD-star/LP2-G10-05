#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// INTERFACES
// ==========================================
class IProyecto {
public:
    virtual void crear_proyecto(string nombre, string descripcion, string fecha_inicio, string fecha_fin) = 0;
    virtual void eliminar_proyecto(string nombre) = 0;
    virtual void listar_proyectos() = 0;
    virtual ~IProyecto() = default;
};

class IComentario {
public:
    virtual void agregar_comentario(string autor, string texto, string fecha) = 0;
    virtual void eliminar_comentario(string autor) = 0;
    virtual void listar_comentarios() = 0;
    virtual ~IComentario() = default;
};

class IArchivo {
public:
    virtual void agregar_archivo(string nombre, string tipo, string ruta) = 0;
    virtual void eliminar_archivo(string nombre) = 0;
    virtual void listar_archivos() = 0;
    virtual ~IArchivo() = default;
};

// ==========================================
// CLASES
// ==========================================
class Proyecto {
public:
    string nombre;
    string descripcion;
    string fecha_inicio;
    string fecha_fin;

    Proyecto(string n, string d, string fi, string ff)
        : nombre(n), descripcion(d), fecha_inicio(fi), fecha_fin(ff) {}

    void mostrar() {
        cout << "Proyecto: " << nombre << ", Descripcion: " << descripcion << ", Fecha de inicio: " << fecha_inicio << ", Fecha de fin: " << fecha_fin << endl;
    }
};

class Comentario {
public:
    string autor;
    string texto;
    string fecha;

    Comentario(string a, string t, string f)
        : autor(a), texto(t), fecha(f) {}

    void mostrar() {
        cout << "Comentario de " << autor << ": " << texto << " - Fecha: " << fecha << endl;
    }
};

class Archivo {
public:
    string nombre;
    string tipo;
    string ruta;

    Archivo(string n, string t, string r)
        : nombre(n), tipo(t), ruta(r) {}

    void mostrar() {
        cout << "Archivo: " << nombre << " - Tipo: " << tipo << " - Ruta: " << ruta << endl;
    }
};

// ==========================================
// GESTORES (Implementaciones de Interfaces)
// ==========================================
class GestorProyectos : public IProyecto {
private:
    vector<Proyecto> proyectos;
public:
    void crear_proyecto(string nombre, string descripcion, string fecha_inicio, string fecha_fin) override {
        Proyecto nuevo_proyecto(nombre, descripcion, fecha_inicio, fecha_fin);
        proyectos.push_back(nuevo_proyecto);
        cout << "Proyecto '" << nombre << "' creado exitosamente." << endl;
    }

    void eliminar_proyecto(string nombre) override {
        for (auto it = proyectos.begin(); it != proyectos.end(); ++it) {
            if (it->nombre == nombre) {
                proyectos.erase(it);
                cout << "Proyecto '" << nombre << "' eliminado exitosamente." << endl;
                return;
            }
        }
        cout << "No se encontro el proyecto con el nombre '" << nombre << "'." << endl;
    }

    void listar_proyectos() override {
        if (proyectos.empty()) {
            cout << "No hay proyectos para mostrar." << endl;
            return;
        }
        cout << "Lista de Proyectos:" << endl;
        for (auto& proyecto : proyectos) {
            proyecto.mostrar();
        }
    }
};

class GestorComentarios : public IComentario {
private:
    vector<Comentario> comentarios;
public:
    void agregar_comentario(string autor, string texto, string fecha) override {
        Comentario nuevo_comentario(autor, texto, fecha);
        comentarios.push_back(nuevo_comentario);
        cout << "Comentario de " << autor << " agregado exitosamente." << endl;
    }

    void eliminar_comentario(string autor) override {
        for (auto it = comentarios.begin(); it != comentarios.end(); ++it) {
            if (it->autor == autor) {
                comentarios.erase(it);
                cout << "Comentario de " << autor << " eliminado exitosamente." << endl;
                return;
            }
        }
        cout << "No se encontro un comentario de " << autor << "." << endl;
    }

    void listar_comentarios() override {
        if (comentarios.empty()) {
            cout << "No hay comentarios para mostrar." << endl;
            return;
        }
        cout << "Lista de Comentarios:" << endl;
        for (auto& comentario : comentarios) {
            comentario.mostrar();
        }
    }
};

class GestorArchivos : public IArchivo {
private:
    vector<Archivo> archivos;
public:
    void agregar_archivo(string nombre, string tipo, string ruta) override {
        Archivo nuevo_archivo(nombre, tipo, ruta);
        archivos.push_back(nuevo_archivo);
        cout << "Archivo '" << nombre << "' agregado exitosamente." << endl;
    }

    void eliminar_archivo(string nombre) override {
        for (auto it = archivos.begin(); it != archivos.end(); ++it) {
            if (it->nombre == nombre) {
                archivos.erase(it);
                cout << "Archivo '" << nombre << "' eliminado exitosamente." << endl;
                return;
            }
        }
        cout << "No se encontro el archivo con el nombre '" << nombre << "'." << endl;
    }

    void listar_archivos() override {
        if (archivos.empty()) {
            cout << "No hay archivos para mostrar." << endl;
            return;
        }
        cout << "Lista de Archivos:" << endl;
        for (auto& archivo : archivos) {
            archivo.mostrar();
        }
    }
};

// ==========================================
// FUNCION PRINCIPAL - INTERACTIVA
// ==========================================
void mostrar_menu() {
    cout << "\nMenu de Opciones:" << endl;
    cout << "1. Crear Proyecto" << endl;
    cout << "2. Eliminar Proyecto" << endl;
    cout << "3. Listar Proyectos" << endl;
    cout << "4. Agregar Comentario" << endl;
    cout << "5. Eliminar Comentario" << endl;
    cout << "6. Listar Comentarios" << endl;
    cout << "7. Agregar Archivo" << endl;
    cout << "8. Eliminar Archivo" << endl;
    cout << "9. Listar Archivos" << endl;
    cout << "0. Salir" << endl;
    cout << "Elija una opcion: ";
}

int main() {
    GestorProyectos gestorProyectos;
    GestorComentarios gestorComentarios;
    GestorArchivos gestorArchivos;

    int opcion;
    string nombre, descripcion, fecha_inicio, fecha_fin, autor, texto, fecha, tipo, ruta;

    do {
        mostrar_menu();
        cin >> opcion;
        cin.ignore(); // Para limpiar el buffer del cin

        switch(opcion) {
            case 1:
                cout << "Ingrese el nombre del proyecto: ";
                getline(cin, nombre);
                cout << "Ingrese la descripcion del proyecto: ";
                getline(cin, descripcion);
                cout << "Ingrese la fecha de inicio (dd-mm-yyyy): ";
                getline(cin, fecha_inicio);
                cout << "Ingrese la fecha de fin (dd-mm-yyyy): ";
                getline(cin, fecha_fin);
                gestorProyectos.crear_proyecto(nombre, descripcion, fecha_inicio, fecha_fin);
                break;
            case 2:
                cout << "Ingrese el nombre del proyecto a eliminar: ";
                getline(cin, nombre);
                gestorProyectos.eliminar_proyecto(nombre);
                break;
            case 3:
                gestorProyectos.listar_proyectos();
                break;
            case 4:
                cout << "Ingrese el nombre del autor del comentario: ";
                getline(cin, autor);
                cout << "Ingrese el comentario: ";
                getline(cin, texto);
                cout << "Ingrese la fecha del comentario (dd-mm-yyyy): ";
                getline(cin, fecha);
                gestorComentarios.agregar_comentario(autor, texto, fecha);
                break;
            case 5:
                cout << "Ingrese el autor del comentario a eliminar: ";
                getline(cin, autor);
                gestorComentarios.eliminar_comentario(autor);
                break;
            case 6:
                gestorComentarios.listar_comentarios();
                break;
            case 7:
                cout << "Ingrese el nombre del archivo: ";
                getline(cin, nombre);
                cout << "Ingrese el tipo del archivo: ";
                getline(cin, tipo);
                cout << "Ingrese la ruta del archivo: ";
                getline(cin, ruta);
                gestorArchivos.agregar_archivo(nombre, tipo, ruta);
                break;
            case 8:
                cout << "Ingrese el nombre del archivo a eliminar: ";
                getline(cin, nombre);
                gestorArchivos.eliminar_archivo(nombre);
                break;
            case 9:
                gestorArchivos.listar_archivos();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while(opcion != 0);

    return 0;
}
