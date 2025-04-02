#include <iostream>
#include <string>

using namespace std;

// Interfaz de notificador
class INotificador {
public:
    virtual void enviar_notificacion(string mensaje) = 0;
    virtual ~INotificador() = default;
};

// Clase Gestor de tareas, que depende de la interfaz INotificador
class GestorTareas {
    INotificador* notificador;

public:
    GestorTareas(INotificador* n) : notificador(n) {}

    void asignar_tarea(string tarea) {
        cout << "Asignando tarea: " << tarea << endl;
        notificador->enviar_notificacion("Tarea '" + tarea + "' asignada.");
    }
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

int main() {
    NotificadorEmail notificadorEmail;
    GestorTareas gestor(&notificadorEmail);
    gestor.asignar_tarea("Desarrollar aplicacion");

    NotificadorSMS notificadorSMS;
    gestor = GestorTareas(&notificadorSMS);
    gestor.asignar_tarea("Desarrollar aplicacion");
}
