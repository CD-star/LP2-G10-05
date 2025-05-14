#include <iostream>
#include <string>

using namespace std; // Para no tener que escribir std:: antes de cada elemento estandar

// Clase base Persona
class Persona {
private:
    string nombre;
    int edad;
    double salario; // Atributo general, aunque para Cliente podria no ser directamente "salario"

protected:
    string direccion_correo_electronico; // Miembro protected

public:
    // Constructor de la clase Persona
    Persona(string nombre, int edad, double salario, string correo)
        : nombre(nombre), edad(edad), salario(salario), direccion_correo_electronico(correo) {
        // cout << "Constructor de Persona: " << this->nombre << endl;
    }

    // Destructor virtual (buena practica para clases base con herencia)
    virtual ~Persona() {
        // cout << "Destructor de Persona: " << this->nombre << endl;
    }

    // Getters para los atributos privados
    string get_nombre() const { return nombre; }
    int get_edad() const { return edad; }
    double get_salario() const { return salario; } // Podria ser relevante para Empleado

    // Metodo para establecer un nuevo correo (ejemplo de manipulacion del miembro protected desde la base)
    void set_correo_electronico(const string& nuevo_correo) {
        // Aqui se podria anadir validacion para el formato del correo si se desea
        this->direccion_correo_electronico = nuevo_correo;
    }

    // Metodo virtual para mostrar la informacion
    virtual void mostrar_informacion() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        // El "salario" es un atributo de Persona, su relevancia depende del contexto de la clase derivada
        cout << "Salario (base Persona): $" << salario << endl;
        cout << "Correo Electronico (desde Persona): " << direccion_correo_electronico << endl;
    }
};

// Clase derivada Empleado
class Empleado : public Persona {
private:
    string puesto;
    int id_empleado;

public:
    // Constructor de Empleado, llama al constructor de Persona
    Empleado(string nombre, int edad, double salario, string correo, string puesto, int id_empleado)
        : Persona(nombre, edad, salario, correo), puesto(puesto), id_empleado(id_empleado) {
        // cout << "Constructor de Empleado: " << this->get_nombre() << endl;
    }

    ~Empleado() {
        // cout << "Destructor de Empleado: " << this->get_nombre() << endl;
    }

    // Sobrescribe mostrar_informacion para anadir detalles del empleado
    void mostrar_informacion() const override {
        Persona::mostrar_informacion(); // Muestra la informacion base de Persona
        cout << "ID Empleado: " << id_empleado << endl;
        cout << "Puesto: " << puesto << endl;
        // Acceso al miembro protected heredado:
        cout << "Correo Electronico (verificado por Empleado): " << direccion_correo_electronico << endl;
    }

    // Metodo especifico de Empleado que usa el correo
    void enviar_comunicado_interno(const string& mensaje) const {
        cout << "\nEnviando comunicado interno a " << get_nombre() << " (" << puesto << ") al correo: " << direccion_correo_electronico << endl;
        cout << "Mensaje: " << mensaje << endl;
    }
};

// Clase derivada Cliente
class Cliente : public Persona {
private:
    int numero_cliente;
    string tipo_membresia;

public:
    // Constructor de Cliente, llama al constructor de Persona
    // Para un cliente, el "salario" de Persona podria no ser relevante,
    // se podria pasar 0 o un valor que represente ingresos/capacidad_compra si se adapta el modelo.
    Cliente(string nombre, int edad, string correo, int numero_cliente, string tipo_membresia)
        : Persona(nombre, edad, 0.0, correo), numero_cliente(numero_cliente), tipo_membresia(tipo_membresia) {
        // cout << "Constructor de Cliente: " << this->get_nombre() << endl;
    }

    ~Cliente() {
        // cout << "Destructor de Cliente: " << this->get_nombre() << endl;
    }

    // Sobrescribe mostrar_informacion para anadir detalles del cliente
    // Se omite la informacion de "salario" si no es relevante para Cliente.
    void mostrar_informacion() const override {
        cout << "Nombre Cliente: " << get_nombre() << endl;
        cout << "Edad: " << get_edad() << endl;
        cout << "Numero de Cliente: " << numero_cliente << endl;
        cout << "Tipo de Membresia: " << tipo_membresia << endl;
        // Acceso al miembro protected heredado:
        cout << "Correo Electronico (verificado por Cliente): " << direccion_correo_electronico << endl;
    }

    // Metodo especifico de Cliente que usa el correo
    void enviar_oferta_especial(const string& oferta) const {
        cout << "\nEnviando oferta especial a " << get_nombre() << " al correo: " << direccion_correo_electronico << endl;
        cout << "Oferta: " << oferta << endl;
    }
};

// Funcion principal para demostrar el uso
int main() {
    cout << "--- Creando y mostrando Empleado ---" << endl;
    Empleado emp1("Laura Gomez", 34, 60000.0, "laura.gomez@example.com", "Gerente de Proyectos", 101);
    emp1.mostrar_informacion();
    emp1.enviar_comunicado_interno("Recordatorio: Reunion de equipo manana a las 10 AM.");
    emp1.set_correo_electronico("laura.g.oficial@example.com"); // Empleado puede usar el setter de Persona
    cout << "* Correo de empleado actualizado *" << endl;
    emp1.mostrar_informacion();
    cout << "\n--------------------------------------\n";

    cout << "--- Creando y mostrando Cliente ---" << endl;
    Cliente cli1("Carlos Diaz", 45, "carlos.diaz.cliente@example.net", 7005, "Premium");
    cli1.mostrar_informacion();
    cli1.enviar_oferta_especial("¡20% de descuento en su proxima compra!");
    // Para cambiar el correo del cliente, tambien se usaria el metodo de Persona:
    // cli1.set_correo_electronico("c.diaz.nuevo@example.net");
    // cli1.mostrar_informacion(); // Para ver el cambio
    cout << "\n--------------------------------------\n";

    // Ejemplo de polimorfismo
    cout << "--- Demostracion de Polimorfismo ---" << endl;
    Persona* personas[2];
    personas[0] = new Empleado("Sofia Kent", 28, 48000.0, "sofia.k@example.com", "Analista de Datos", 102);
    personas[1] = new Cliente("Roberto Mora", 52, "roberto.m@example.org", 7006, "Estandar");

    for (int i = 0; i < 2; ++i) {
        personas[i]->mostrar_informacion();
        // Para llamar a metodos especificos de Empleado o Cliente, se necesitaria un dynamic_cast seguro
        if (Empleado* emp = dynamic_cast<Empleado*>(personas[i])) {
            emp->enviar_comunicado_interno("Revision de desempeno la proxima semana.");
        }
        if (Cliente* cli = dynamic_cast<Cliente*>(personas[i])) {
            cli->enviar_oferta_especial("Acceso anticipado a nuevas llegadas.");
        }
        cout << "---" << endl;
    }

    // Liberar memoria
    delete personas[0];
    delete personas[1];

    return 0;
}