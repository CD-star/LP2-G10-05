#include <iostream>
using namespace std;

template <typename T>
void ordenarYMostrar(T arreglo[], int n) {
    // Ordenamiento simple (burbuja)
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

int main() {
    int nums[] = {5, 2, 9, 1};
    ordenarYMostrar(nums, 4);

    float decimales[] = {4.5, 2.1, 3.3};
    ordenarYMostrar(decimales, 3);

    return 0;
}