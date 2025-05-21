#include <iostream>
using namespace std;

class Figura{
    public:
        virtual double calcularArea()= 0;
        virtual ~Figura(){}
};

class Circulo :public Figura{
    private:
        double radio;
    public:
        Circulo(double r) : radio(r) {}
        
        double calcularArea() override {
            return 3.1416 * radio * radio;
        }
};

class Rectangulo :public Figura{
    private:
        double altura;
        double base;
    
    public:
    
        Rectangulo(double a,double b):altura(a),base(b){}  
    
        double calcularArea() override {
            return altura*base;
        }
};

class Triangulo :public Figura{
    private:
        double altura;
        double base;
    
    public:
    
        Triangulo(double a,double b):altura(a),base(b){}  
    
        double calcularArea() override {
            return altura*base/2;
        }
};

class Cuadrado :public Figura{
    private:
        double lado;
    public:
        Cuadrado(double l) : lado(l) {}
        
        double calcularArea() override {
            return lado * lado;
        }
};

class Pentagono :public Figura{
    private:
        double lado;
        double apotema;
    
    public:
    
        Pentagono(double l,double a):lado(l),apotema(a){}  
    
        double calcularArea() override {
            return 5*lado*apotema/2;
        }
};

int main()
{   
    int op = 0;
    while (true) {
        cout<<"----------Calculadora de Areas----------"<<endl;
        cout<<"Elije una opcion:"<<endl;
        cout<<"0.Salir"<<endl;
        cout<<"1.Area Circulo"<<endl;
        cout<<"2.Area Rectangulo"<<endl;
        cout<<"3.Area Triangulo"<<endl;
        cout<<"4.Area Cuadrado"<<endl;
        cout<<"5.Area Pentagono"<<endl;
        cin>>op;

        if (op == 1){
            double r;
            cout<<"Ingresa el radio: ";
            cin>>r;
            Figura* f1 = new Circulo(r);
            cout << "Area: " << f1->calcularArea() << endl;
            delete f1;
        } 
        else if (op == 2){
            double a,b;
            cout<<"Ingresa la altura: ";
            cin>>a;
            cout<<"Ingresa la base: ";
            cin>>b;
            Figura* f1 = new Rectangulo(a,b);
            cout << "Area: " << f1->calcularArea() << endl;
            delete f1;
        }
        else if (op == 3){
            double a,b;
            cout<<"Ingresa la altura: ";
            cin>>a;
            cout<<"Ingresa la base: ";
            cin>>b;
            Figura* f1 = new Triangulo(a,b);
            cout << "Area: " << f1->calcularArea() << endl;
            delete f1;
        }
        else if (op == 4){
            double r;
            cout<<"Ingresa el lado: ";
            cin>>r;
            Figura* f1 = new Cuadrado(r);
            cout << "Area: " << f1->calcularArea() << endl;
            delete f1;
        } 
        else if (op == 5){
            double a,b;
            cout<<"Ingresa el lado: ";
            cin>>a;
            cout<<"Ingresa el apotema: ";
            cin>>b;
            Figura* f1 = new Pentagono(a,b);
            cout << "Area: " << f1->calcularArea() << endl;
            delete f1;
            
        }
        else if(op == 0){
            cout<<"Saliendo..."<<endl;
            break;
        }
        else {
            cout<<"Opcion no valida"<<endl;
        }
    }
    return 0;
}