#include <iostream>
#include "../blocks/blockchain.h"

using namespace std;

void printMenu() {
    cout << "====== Menu ======" << endl;
    cout << "1. Mostrar cadena de Blocks" << endl;
    cout << "2. Busqueda por igualdad a nombre de usuario" << endl;
    cout << "3. Busqueda por rango en monto" << endl;
    cout << "4. Busqueda por rango en fecha" << endl;
    cout << "5. Usuario inicia con" << endl;
    cout << "6. Lugar inicia con" << endl;
    cout << "7. Esta contenido en el nombre" << endl;
    cout << "8. Esta contenido en el lugar" << endl;
    cout << "9. Buscar minimo por monto" << endl;
    cout << "10. Buscar maximo por monto" << endl;
    cout << "11. Recalculo en cascada" << endl;
    cout << "12. Agregar transaccion" << endl; // o puede ser modificar bloque
    cout << "13. Eliminar bloque o transaccion" << endl;
    cout << "14. Salir" << endl;
    cout << "==================" << endl;
    cout << "Seleccione una opción: ";
}


void Init_Menu(){

    BlockChain* blockchain = new BlockChain;

    int option;
    do {
        printMenu();
        cin >> option;

        switch (option) {
            case 1:
                // Mostrar todas las transacciones
                blockchain->init_blockchain();
                break;
            case 2:
                // Agregar una nueva transacción
                // ...
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }

        cout << endl;
    } while (option != 3);

    delete blockchain;
};