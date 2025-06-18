#include <iostream>
using namespace std;

class Ordenador {
public:
    template <typename T>
    void ordenarYMostrar(T arreglo[], int n) {
        for(int i = 0; i < n-1; i++) {
            for(int j = 0; j < n-i-1; j++) {
                if(arreglo[j] > arreglo[j+1]) {
                    T temp = arreglo[j];
                    arreglo[j] = arreglo[j+1];
                    arreglo[j+1] = temp;
                }
            }
        }

        cout << "Arreglo ordenado: ";
        for(int i = 0; i < n; i++)
            cout << arreglo[i] << " ";
        cout << endl;
    }
};

int main() {
    Ordenador o;
    int nums[] = {8, 4, 2, 6};
    o.ordenarYMostrar(nums, 4);

    double reales[] = {2.5, 1.1, 3.7};
    o.ordenarYMostrar(reales, 3);

    return 0;
}
