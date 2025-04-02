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
    virtual ~IComentario() = default;
};

class IArchivo {
public:
    virtual void agregar_archivo(string nombre, string tipo, string ruta) = 0;
    virtual void eliminar_archivo(string nombre) = 0;
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
        cout << "Proyecto: " << nombre << ", Fecha de inicio: " << fecha_inicio << ", Fecha de fin: " << fecha_fin << endl;
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
    }

    void eliminar_proyecto(string nombre) override {
        for (auto it = proyectos.begin(); it != proyectos.end(); ++it) {
            if (it->nombre == nombre) {
                proyectos.erase(it);
                break;
            }
        }
    }

    void listar_proyectos() override {
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
    }

    void eliminar_comentario(string autor) override {
        for (auto it = comentarios.begin(); it != comentarios.end(); ++it) {
            if (it->autor == autor) {
                comentarios.erase(it);
                break;
            }
        }
    }

    void listar_comentarios() {
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
    }

    void eliminar_archivo(string nombre) override {
        for (auto it = archivos.begin(); it != archivos.end(); ++it) {
            if (it->nombre == nombre) {
                archivos.erase(it);
                break;
            }
        }
    }

    void listar_archivos() {
        for (auto& archivo : archivos) {
            archivo.mostrar();
        }
    }
};

// ==========================================
// FUNCION PRINCIPAL
// ==========================================
int main() {
    // Crear los gestores
    GestorProyectos gestorProyectos;
    GestorComentarios gestorComentarios;
    GestorArchivos gestorArchivos;

    // Operaciones de Proyectos
    gestorProyectos.crear_proyecto("Proyecto A", "Descripcion del Proyecto A", "01-01-2025", "31-12-2025");
    gestorProyectos.crear_proyecto("Proyecto B", "Descripcion del Proyecto B", "01-03-2025", "30-09-2025");

    // Operaciones de Comentarios
    gestorComentarios.agregar_comentario("Juan", "Este es un comentario sobre el Proyecto A", "02-01-2025");
    gestorComentarios.agregar_comentario("Maria", "Comentario adicional sobre el Proyecto B", "02-01-2025");

    // Operaciones de Archivos
    gestorArchivos.agregar_archivo("documento.txt", "txt", "/archivos/proyectoA/documento.txt");
    gestorArchivos.agregar_archivo("imagen.jpg", "jpg", "/archivos/proyectoB/imagen.jpg");

    // Mostrar Proyectos
    cout << "Proyectos:" << endl;
    gestorProyectos.listar_proyectos();

    // Mostrar Comentarios
    cout << "\nComentarios:" << endl;
    gestorComentarios.listar_comentarios();

    // Mostrar Archivos
    cout << "\nArchivos:" << endl;
    gestorArchivos.listar_archivos();

    // Ejemplo de eliminacion
    gestorProyectos.eliminar_proyecto("Proyecto A");
    gestorComentarios.eliminar_comentario("Juan");
    gestorArchivos.eliminar_archivo("documento.txt");

    // Mostrar despues de eliminacion
    cout << "\nProyectos despues de eliminacion:" << endl;
    gestorProyectos.listar_proyectos();

    cout << "\nComentarios despues de eliminacion:" << endl;
    gestorComentarios.listar_comentarios();

    cout << "\nArchivos despues de eliminacion:" << endl;
    gestorArchivos.listar_archivos();

    return 0;
}
