#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Clase Tarea - Responsabilidad de gestionar las tareas
class Tarea {
public:
    string titulo;
    string descripcion;
    string fecha_limite;
    string estado;
    string prioridad;

    Tarea(string t, string d, string f, string e, string p)
        : titulo(t), descripcion(d), fecha_limite(f), estado(e), prioridad(p) {}

    void mostrar() {
        cout << "Tarea: " << titulo << " - Estado: " << estado << endl;
    }
};

// Clase Usuario - Responsabilidad de gestionar usuarios
class Usuario {
public:
    string nombre;
    string correo;
    vector<Tarea> tareas;

    Usuario(string n, string c) : nombre(n), correo(c) {}

    void asignar_tarea(Tarea tarea) {
        tareas.push_back(tarea);
    }

    void mostrar_tareas() {
        for (auto& tarea : tareas) {
            tarea.mostrar();
        }
    }
};

// Clase Seguimiento - Responsabilidad de actualizar el progreso de tareas
class Seguimiento {
public:
    void actualizar_estado(Tarea& tarea, string nuevo_estado) {
        tarea.estado = nuevo_estado;
    }
};

// Clase Notificador - Responsabilidad de enviar notificaciones
class Notificador {
public:
    void enviar_notificacion(Usuario& usuario, string mensaje) {
        cout << "Notificacion enviada a " << usuario.nombre << ": " << mensaje << endl;
    }
};

int main() {
    Usuario usuario("Juan", "juan@example.com");
    Tarea tarea("Desarrollar aplicacion", "Crear la aplicacion de gestion de tareas", "2025-05-01", "Pendiente", "Alta");
    
    usuario.asignar_tarea(tarea);
    usuario.mostrar_tareas();

    Seguimiento seguimiento;
    seguimiento.actualizar_estado(tarea, "Completada");

    Notificador notificador;
    notificador.enviar_notificacion(usuario, "Tarea '" + tarea.titulo + "' asignada y completada.");
}
