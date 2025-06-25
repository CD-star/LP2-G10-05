#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string nombreArchivo;

    cout << "Ingrese el nombre del archivo (ej. texto.txt): ";
    cin >> nombreArchivo;

    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "Error: No se pudo abrir el archivo \"" << nombreArchivo << "\".\n";
        return 1;
    }

    cout << "\nContenido del archivo:\n\n";
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
    return 0;
}