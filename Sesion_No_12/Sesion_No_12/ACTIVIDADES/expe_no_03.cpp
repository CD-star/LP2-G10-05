#include <iostream>
#include <deque>
#include <string>
#include <cctype> // Para tolower
using namespace std;

// Función para verificar si un carácter es vocal
bool esVocal(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    string cadena;
    deque<char> caracteres;

    // Ingreso de la cadena
    cout << "Ingrese una cadena de texto: ";
    getline(cin, cadena);

    // Almacenar cada carácter en el deque
    for (char c : cadena) {
        caracteres.push_back(c);
    }

    // a) Mostrar caracteres uno por uno usando iterador
    cout << "\nCaracteres usando iterador:\n";
    for (deque<char>::iterator it = caracteres.begin(); it != caracteres.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // b) Reemplazar vocales por '*'
    for (deque<char>::iterator it = caracteres.begin(); it != caracteres.end(); ++it) {
        if (esVocal(*it)) {
            *it = '*';
        }
    }

    // c) Mostrar caracteres en orden inverso usando iterador inverso
    cout << "\nCaracteres en orden inverso (iterador inverso):\n";
    for (deque<char>::reverse_iterator rit = caracteres.rbegin(); rit != caracteres.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    // Mostrar cadena final después de reemplazar vocales
    cout << "\nCadena final después de reemplazar vocales:\n";
    for (char c : caracteres) {
        cout << c;
    }
    cout << endl;

    return 0;
}