#include <iostream>
using namespace std;

class Vehiculo{
    public:
        virtual void acelerar(){
            cout<<"Acelerando el vehiculo"<<endl;
        }
        virtual ~Vehiculo(){}
};
class Coche :public Vehiculo{
    public:
        void acelerar() override{
            cout<<"Acelerando el coche "<<endl;
        }
        void encenderLuces() {
            cout<<"Luces del coche encendidas"<<endl;
        }
        
};
class Motocicleta :public Vehiculo{
    public:
        void acelerar() override{
            cout<<"Acelerando la motocicleta "<<endl;
        }
};

int main() {
    Vehiculo* f1 = new Coche();  // Aplicando polimorfismo
    Vehiculo* f2 = new Motocicleta();

    f1->acelerar();
    f2->acelerar();

    Coche* cochePtr = dynamic_cast<Coche*>(f1);
    cochePtr->encenderLuces();

    delete f1;
    delete f2;

    return 0;
}