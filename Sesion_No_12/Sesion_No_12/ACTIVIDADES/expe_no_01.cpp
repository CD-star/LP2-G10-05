#include <iostream>
#include <vector>
#include <algorithm>  // Para sort, remove_if, min_element, max_element
using namespace std;

int main() {
    vector<int> numeros;
    int n, entrada;

    // Ingreso de datos
    cout << "¿Cuántos números desea ingresar?: ";
    cin >> n;

    cout << "Ingrese " << n << " números enteros:\n";
    for (int i = 0; i < n; ++i) {
        cin >> entrada;
        numeros.push_back(entrada);
    }

    // a) Calcular la suma
    int suma = 0;
    for (int num : numeros) {
        suma += num;
    }

    // b) Encontrar máximo y mínimo 
    int maximo = *max_element(numeros.begin(), numeros.end());
    int minimo = *min_element(numeros.begin(), numeros.end());

    // c) Ordenar ascendentemente
    sort(numeros.begin(), numeros.end());

    // d) Eliminar números pares
    numeros.erase(remove_if(numeros.begin(), numeros.end(), [](int x) {
        return x % 2 == 0;
    }), numeros.end());

    // Mostrar resultados
    cout << "\nRESULTADOS:\n";
    cout << "Suma de los números: " << suma << endl;
    cout << "Número máximo: " << maximo << endl;
    cout << "Número mínimo: " << minimo << endl;
    cout << "Vector final (sin números pares y ordenado): ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
