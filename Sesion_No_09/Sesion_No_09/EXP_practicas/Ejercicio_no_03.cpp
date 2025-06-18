#include <iostream>
using namespace std;

template <typename T>
class Recipiente {
private:
    T* arreglo;
    int tam;

public:
    Recipiente(T arr[], int n) {
        tam = n;
        arreglo = new T[tam];
        for(int i = 0; i < tam; i++) {
            arreglo[i] = arr[i];
        }
    }

    void mostrar() {
        for(int i = 0; i < tam; i++)
            cout << arreglo[i] << " ";
        cout << endl;
    }

    ~Recipiente() {
        delete[] arreglo;
    }
};

int main() {
    int nums[] = {1, 2, 3, 4};
    Recipiente<int> r1(nums, 4);
    r1.mostrar();

    string palabras[] = {"hola", "mundo"};
    Recipiente<string> r2(palabras, 2);
    r2.mostrar();

    return 0;
}
