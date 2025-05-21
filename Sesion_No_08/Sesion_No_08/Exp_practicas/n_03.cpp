#include <iostream>
using namespace std;

class Animal{
    public:
        virtual void hacerSonido()= 0;
        virtual ~Animal(){}
};
class Perro :public Animal{
    public:
        void hacerSonido() override{
            cout<<"Gua Gua Gua "<<endl;
        }
};
class Gato :public Animal{
    public:
        void hacerSonido() override{
            cout<<"Miau Miau Miau "<<endl;
        }
};
class Vaca :public Animal{
    public:
        void hacerSonido() override{
            cout<<"Muuu Muuu Muuu"<<endl;
        }
};

int main() {
    Animal* f1 = new Perro();
    Animal* f3 = new Gato(); // Aplicando polimorfismo
    Animal* f2 = new Vaca();

    f1->hacerSonido();
    f3->hacerSonido();
    f2->hacerSonido();

    delete f1;
    delete f3;
    delete f2;

    return 0;

}