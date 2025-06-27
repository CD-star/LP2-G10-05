#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <cctype> // Para toupper
using namespace std;

// Función para convertir una palabra a mayúsculas
string aMayusculas(string palabra) {
    transform(palabra.begin(), palabra.end(), palabra.begin(), ::toupper);
    return palabra;
}

int main() {
    list<string> palabras;
    int cantidad;
    string entrada; 

    // a) Leer palabras y almacenarlas en list
    cout << "¿Cuántas palabras deseas ingresar?: ";
    cin >> cantidad;
    cin.ignore(); // Limpiar el salto de línea

    cout << "Ingrese " << cantidad << " palabras:\n";
    for (int i = 0; i < cantidad; ++i) {
        getline(cin, entrada);
        palabras.push_back(entrada);
    }

    // b) Ordenar alfabéticamente
    palabras.sort();

    // c) Contar cuántas veces aparece una palabra específica
    cout << "\nIngrese la palabra que desea contar: ";
    string palabraBuscar;
    getline(cin, palabraBuscar);
    int cantidadApariciones = count(palabras.begin(), palabras.end(), palabraBuscar);

    // d) Convertir todas las palabras a mayúsculas
    for (string& palabra : palabras) {
        palabra = aMayusculas(palabra);
    }

    // e) Mostrar lista final
    cout << "\nLista de palabras en mayúsculas y ordenadas:\n";
    for (const string& palabra : palabras) {
        cout << palabra << endl;
    }

    cout << "\nLa palabra '" << palabraBuscar << "' aparece " << cantidadApariciones << " veces.\n";

    return 0;
}