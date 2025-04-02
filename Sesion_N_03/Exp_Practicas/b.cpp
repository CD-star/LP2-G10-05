#include <iostream>
#include <string>

using namespace std;

// Interfaz para notificacion
class INotificador {
public:
    virtual void enviar_notificacion(string mensaje) = 0;
    virtual ~INotificador() = default;
};

// Implementacion de notificador por email
class NotificadorEmail : public INotificador {
public:
    void enviar_notificacion(string mensaje) override {
        cout << "Enviando email: " << mensaje << endl;
    }
};

// Implementacion de notificador por SMS
class NotificadorSMS : public INotificador {
public:
    void enviar_notificacion(string mensaje) override {
        cout << "Enviando SMS: " << mensaje << endl;
    }
};

// Clase Gestor de tareas, dependiente de la interfaz INotificador
class GestorTareas {
    INotificador* notificador;

public:
    GestorTareas(INotificador* n) : notificador(n) {}

    void asignar_tarea(string tarea) {
        cout << "Asignando tarea: " << tarea << endl;
        notificador->enviar_notificacion("Tarea '" + tarea + "' asignada.");
    }
};

int main() {
    NotificadorEmail notificadorEmail;
    GestorTareas gestor(&notificadorEmail);
    gestor.asignar_tarea("Desarrollar aplicacion");

    NotificadorSMS notificadorSMS;
    gestor = GestorTareas(&notificadorSMS);
    gestor.asignar_tarea("Desarrollar aplicacion");
}
