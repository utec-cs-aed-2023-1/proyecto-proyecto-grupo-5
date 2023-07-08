#include <iostream>
#include "../blocks/blockchain.h"

using namespace std;

void printMenu() {
    cout << "====== Menu ======" << endl;
    cout << "1. Mostrar cadena de Blocks" << endl;
    cout << "2. Agregar transaccion" << endl;
    cout << "3. Salir" << endl;
    cout << "==================" << endl;
    cout << "Ingrese su opcion: ";
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