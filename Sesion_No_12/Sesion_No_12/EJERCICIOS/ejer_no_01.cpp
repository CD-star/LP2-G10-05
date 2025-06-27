#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Producto{
private:
    int id;
    string descripcion;
    int cantidad;

public:
    Producto(int id, string descripcion, int cantidad)
        : id(id), descripcion(descripcion), cantidad(cantidad) {}

    void mostrarInformacion()const {
        cout << "ID: " << id << endl;
        cout << "Descripcion: " << descripcion << endl;
        cout << "Cantidad: " << cantidad << endl;
    }

    int getID() const {
        return id;
    }

    void setCantidad(int nuevaCantidad) {
        cantidad = nuevaCantidad;
    }
    ~Producto() {
        cout << "Destructor de Producto llamado: " << descripcion << endl;
    }
};
class Gestor{
private:
    vector<Producto> productos; 
public:
    void agregarProducto(const Producto& producto)
    {
        productos.push_back(producto);
    }

    void mostrarProductos()
    {
        for (const auto& producto : productos) {
            producto.mostrarInformacion();
            cout << "------------------------" << endl;
        }
    }

    void actualizarCantidad(int id, int nuevaCantidad){
        auto it = find_if(productos.begin(), productos.end(), [id](const Producto& producto) {
            return producto.getID() == id;
        });

        if (it != productos.end()) {
            it->setCantidad(nuevaCantidad);
            cout << "Cantidad actualizada para el producto con ID " << id << endl;
        } else {
            cout << "Producto con ID " << id << " no encontrado." << endl;
        }
    }

    void buscarProductoPorID(int id)
    {
        auto it = find_if(productos.begin(), productos.end(), [id](const Producto& producto) {
            return producto.getID() == id;
        });

        if (it != productos.end()) {
            cout << "Producto encontrado:" << endl;
            it->mostrarInformacion();
        } else {
            cout << "Producto con ID " << id << " no encontrado." << endl;
        }
    }

    void ordenarProductosPorID()
    {
        sort(productos.begin(), productos.end(), [](const Producto& a, const Producto& b) {
            return a.getID() < b.getID();
        });
    }

    ~Gestor() {
        cout << "Destructor de Gestor llamado" << endl;
    }
};

int main()
{
    Gestor gestor;
    int op;
    while(op!=5){
        cout << endl;
        cout << "----------------------------------" << endl;
        cout << "Menu de opciones:" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Actualizar cantidad de producto" << endl;
        cout << "3. Buscar producto por ID" << endl;
        cout << "4. Mostrar productos ordenados" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op) {
        case 1: {
            int id, cantidad;
            string descripcion;
            cout << "Ingrese ID del producto: ";
            cin >> id;
            cout << "Ingrese descripcion del producto: ";
            cin.ignore();
            getline(cin, descripcion);
            cout << "Ingrese cantidad del producto: ";
            cin >> cantidad;
            gestor.agregarProducto(Producto(id, descripcion, cantidad));
            break;
        }
        case 2: {
            int id, nuevaCantidad;
            cout << "Ingrese ID del producto a actualizar: ";
            cin >> id;
            cout << "Ingrese nueva cantidad: ";
            cin >> nuevaCantidad;
            gestor.actualizarCantidad(id, nuevaCantidad);
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del producto a buscar: ";
            cin >> id;
            gestor.buscarProductoPorID(id);
            break;
        }
        case 4:
            gestor.ordenarProductosPorID();
            gestor.mostrarProductos();
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

    } while (op != 5);
    cout << "Saliendo del sistema..." << endl;

    return 0;
}