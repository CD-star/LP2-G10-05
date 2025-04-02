#include <iostream>
#include <string>

using namespace std;

// Interfaz para notificador por email
class INotificadorEmail {
public:
    virtual void enviar_email(string mensaje) = 0;
    virtual ~INotificadorEmail() = default;
};

// Interfaz para notificador por SMS
class INotificadorSMS {
public:
    virtual void enviar_sms(string mensaje) = 0;
    virtual ~INotificadorSMS() = default;
};

// Implementacion para notificador por email
class NotificadorEmail : public INotificadorEmail {
public:
    void enviar_email(string mensaje) override {
        cout << "Enviando email: " << mensaje << endl;
    }
};

// Implementacion para notificador por SMS
class NotificadorSMS : public INotificadorSMS {
public:
    void enviar_sms(string mensaje) override {
        cout << "Enviando SMS: " << mensaje << endl;
    }
};

int main() {
    NotificadorEmail notificadorEmail;
    notificadorEmail.enviar_email("Tarea asignada por email");

    NotificadorSMS notificadorSMS;
    notificadorSMS.enviar_sms("Tarea asignada por SMS");
}
