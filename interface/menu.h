#include <iostream>
#include "../blocks/blockchain.h"
#include "../blocks/block.h"

using namespace std;

void printMenu() {
    std::cout << "====== Menu ======" << endl;
    cout << "1. Mostrar cadena de Blocks" << endl;
    cout << "2. Busqueda por igualdad a nombre de usuario" << endl;
    cout << "3. Busqueda por rango en monto" << endl;
    cout << "4. Busqueda por rango en fecha" << endl;
    cout << "5. Usuario inicia con" << endl;
    cout << "6. Lugar inicia con" << endl;
    cout << "7. Patron contenido en el nombre" << endl;
    cout << "8. Patron contenido en el lugar" << endl;
    cout << "9. Buscar minimo por monto" << endl;
    cout << "10. Buscar maximo por monto" << endl;
    cout << "11. Salir" << endl;
    cout << "==================" << endl;
    cout << "Seleccione una opcion: ";
}

void Init_Menu() {

    BlockChain* blockchain = new BlockChain;

    int option;
 // Variable para almacenar el usuario con la transacción máxima

    do {
        printMenu();
        cin >> option;
        cout << endl;

        switch (option) {
            case 1: {
                // Mostrar todas las transacciones
                blockchain->init_blockchain();
                break;
            }


            case 2: {
                // Búsqueda por igualdad a nombre de usuario
                string nombreCompleto;
                cout << "Ingrese el nombre completo del usuario que desea buscar: ";
                cin.ignore();
                getline(cin, nombreCompleto);
                Block* block = blockchain->buscandoBloquexKey(nombreCompleto);
                if (block != nullptr) {
                    cout << "Datos del usuario encontrado:" << endl;
                    block->printBlock();
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                break;
            }


            case 3: {
                // Busqueda por rango en monto
                // Implementar lógica aquí
                break;
            }
            case 4: {
                // Busqueda por rango en fecha
                // Implementar lógica aquí
                break;
            }
            case 5: {
                // Nombre inicia con
                string a_nombre;
                cout << "Ingrese la letra del nombre con la que quiere iniciar: ";
                cin >> a_nombre;
                blockchain->empieza_nombre_T(a_nombre);
                break;
            }
            case 6: {
                // Lugar inicia con
                string a_lugar;
                cout << "Ingrese la letra del lugar con la que quiere iniciar: ";
                cin >> a_lugar;
                blockchain->empieza_lugar_T(a_lugar);
                break;
            }
            case 7: {
                // Verificar si está contenido en un nombre
                string a_patron;
                cout << "Ingrese el patrón: ";
                cin >> a_patron;
                blockchain->contiene_nombre_T(a_patron);
                break;
            }
            case 8: {
                // Verificar si está contenido en el lugar
                string a_lugar_buscar;
                cout << "Ingrese el lugar a buscar: ";
                cin >> a_lugar_buscar;
                blockchain->contiene_lugar_T(a_lugar_buscar);
                break;
            }


            case 9: {
                    // Buscar el monto mínimo
                    string nombreUsuario1 = blockchain->getMinUser(); // Obtener el valor de minUser de la instancia de BlockChain
                    Transaction minTransaction = blockchain->MinMonto(nombreUsuario1);
                    cout << "La transaccion minimo de " << nombreUsuario1 << " es: " << endl;
                    minTransaction.printTransaction();
                    break;
                }
                case 10: {
                    // Buscar el monto máximo
                    string nombreUsuario = blockchain->getMaxUser(); // Obtener el valor de maxUser de la instancia de BlockChain
                    Transaction maxTransaction = blockchain->MaxMonto(nombreUsuario);
                    cout << "La transaccion maximo de " << nombreUsuario << " es: " << endl;
                    maxTransaction.printTransaction();
                    break;
                }

                case 11: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }   
        cout << endl;
    } while (option != 11);

    delete blockchain;
}
