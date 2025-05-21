#include <iostream>
using namespace std;

class Forma{
    public:
        virtual double calcularPerimetro()= 0;
        virtual ~Forma(){}
};
class Circulo :public Forma{
    private:
        double radio;
    public:
        Circulo(double r) : radio(r) {}
        
        double calcularPerimetro() override {
            return 3.1416 * radio * 2;
        }
};

class Rectangulo :public Forma{
    private:
        double altura;
        double base;
    
    public:
    
        Rectangulo(double a,double b):altura(a),base(b){}  
    
        double calcularPerimetro() override {
            return (altura*2)+(base*2);
        }
};

class Triangulo :public Forma{
    private:
        double lado1;
        double lado2;
        double lado3;
    
    public:
    
        Triangulo(double l1,double l2,double l3):lado1(l1),lado2(l2),lado3(l3){}  
    
        double calcularPerimetro() override {
            return lado1+lado2+lado3;
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
        cin>>op;

        if (op == 1){
            double r;
            cout<<"Ingrese el radio: ";
            cin>>r;
            Forma* f1 = new Circulo(r);
            cout << "Perimetro: " << f1->calcularPerimetro() << endl;
            delete f1;
        } 
        else if (op == 2){
            double a,b;
            cout<<"Ingrese altura: ";
            cin>>a;
            cout<<"Ingrese ancho: ";
            cin>>b;
            Forma* f1 = new Rectangulo(a,b);
            cout << "Perimetro: " << f1->calcularPerimetro() << endl;
            delete f1;
        }
        else if (op == 3){
            double a,b,c;
            cout<<"Ingrese lado 1: ";
            cin>>a;
            cout<<"Ingrese lado 2: ";
            cin>>b;
            cout<<"Ingrese lado 3: ";
            cin>>c;
            Forma* f1 = new Triangulo(a,b,c);
            cout << "Area: " << f1->calcularPerimetro() << endl;
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