#include <iostream>
#include <string>

using namespace std;

// Clase base Notificador
class Notificador {
public:
    virtual void enviar_notificacion(string mensaje) {
        cout << "Notificacion general: " << mensaje << endl;
    }

    virtual ~Notificador() = default;
};

// Subclase NotificadorEmail
class NotificadorEmail : public Notificador {
public:
    void enviar_notificacion(string mensaje) override {
        cout << "Enviando email: " << mensaje << endl;
    }
};

// Subclase NotificadorSMS
class NotificadorSMS : public Notificador {
public:
    void enviar_notificacion(string mensaje) override {
        cout << "Enviando SMS: " << mensaje << endl;
    }
};

// Clase GestorTareas que espera una clase hija de Notificador
class GestorTareas {
    Notificador* notificador;

public:
    GestorTareas(Notificador* n) : notificador(n) {}

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
