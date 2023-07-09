#include <iostream>
#include "../blocks/blockchain.h"
#include "../blocks/block.h"

using namespace std;

void printMenu() {
    cout << "====== Menu ======" << endl;
    cout << "1. Mostrar cadena de Blocks" << endl;
    cout << "2. Busqueda por igualdad a nombre de usuario" << endl;
    cout << "3. Busqueda por rango en monto" << endl;
    cout << "4. Busqueda por rango en fecha" << endl; // no seguro
    cout << "5. Usuario inicia con" << endl;
    cout << "6. Lugar inicia con" << endl;
    cout << "7. Patron contenido en el nombre" << endl;
    cout << "8. Patron contenido en el lugar" << endl;  //////////////////////////
    cout << "9. Buscar minimo por monto" << endl;
    cout << "10. Buscar maximo por monto" << endl;
    cout << "11. Recalculo en cascada" << endl;
    cout << "12. Agregar transaccion" << endl; // o puede ser modificar bloque
    cout << "13. Actualizar transaccion" << endl;
    cout << "14. Eliminar bloque o transaccion" << endl; ////////////////////////////
    cout << "15. Salir" << endl;
    cout << "==================" << endl;
    cout << "Seleccione una opcion: ";
}


void Init_Menu(){

    BlockChain* blockchain = new BlockChain;

    int option;
   

    do {
        printMenu();
        cin >> option;
        cout << endl;

    switch (option) {
        case 1:
        {
            // Mostrar todas las transacciones
            blockchain->init_blockchain();
            break;
        }
        case 2:
        {
            // Búsqueda por igualdad a nombre de usuario
            string nombre_igual;
            cout<<"Ingrese el nombre el nombre que quiere buscar";
            cin>>nombre_igual;
            blockchain->buscandoBloquexKey(nombre_igual);
        }
            break;
        case 3:
        {
            //Busqueda por rango en monto 
            break;
        }
        case 4:
        {
            //Busqueda por rango en fecha
            break;  
        } 
        case 5:
        {
            // Nombre inicia con
            std::string a_nombre;
            std::cout << "Ingrese la letra del nombre con la que quiere iniciar: " << endl;
            std::cin >> a_nombre;
            blockchain->empieza_nombre_T(a_nombre);
        }
            break;                             
        case 6:
        {
            // Lugar inicia con
            std::string a_lugar;
            std::cout << "Ingrese la letra del lugar con la que quiere iniciar: " << endl;
            std::cin >> a_lugar;
            blockchain->empieza_lugar_T(a_lugar);
        }
            break;                
        case 7:
        {
            // Verificar si está contenido en un nombre
            std::string a_patron;
            std::cout << "Ingrese el patron: " << endl;
            std::cin >> a_patron;
            blockchain->contiene_nombre_T(a_patron);
        }
            break;  
        case 8:
        {
            // Verificar si está contenido en el lugar
            std::string a_lugar_buscar;
            cout << "Ingrese el lugar a buscar: ";
            cin >> a_lugar_buscar;
            blockchain->contiene_lugar_T(a_lugar_buscar);     
        }
            break;
        case 9:
        {
            // Buscar el monto mínimo
            std::string monto_min_nombre;
            cout << "Ingrese el nombre del Usuario en el cual quisiera encontrar su monto minimo: ";
            cin >> monto_min_nombre;
            blockchain->MinMonto(monto_min_nombre);
        }
            break; 
        case 10:
        {
            // Buscar el monto máximo
            std::string monto_max_nombre;
            cout << "Ingrese el nombre del Usuario en el cual quisiera encontrar su monto maximo: ";
            cin >> monto_max_nombre;
            blockchain->MaxMonto(monto_max_nombre);
        }
            break; 
        case 11:
        {
            // Agregar aquí la lógica para el recálculo en cascada
            std::string nombre;
            cout << "Introduce el nombre de usuario donde se quisiera hacer el recalculo en cascada: ";
            cin >> nombre;
            blockchain->cascada(nombre);
        }
            break;
        case 12:
        {
            // Agregar aquí la lógica para agregar una transacción
            std::string nombreUsuario;
            cout << "Introduce el nombre de usuario donde se quisiera hacer un retiro: ";
            cin >> nombreUsuario;
            
            std::string lugar;
            cout << "Introduce el lugar donde realiza el retiro: ";
            cin >> lugar;
            
            float monto;
            cout<< "Introduce el monto a retirar"<<endl;
            cin>> monto;

            std::string fecha;
            cout << "Introduce la fecha en la que se realiza el retiro: ";
            cin >> fecha;
            blockchain->insertRetiro(nombreUsuario,lugar,monto,fecha);
        }
            break;
        case 13:
        {
            // Agregar aquí la lógica para actualizar una transacción
            // void updateTx(Transaction changed, string place, int amount, string date) 
            Block* block = new Block;
           //FALTA AFINAR block->updateTx();
            break;  
        }


        case 14:
        {
            // Agregar aquí la lógica para eliminar una transacción
            
            break;  
        }   
        case 15:
        {
            cout << "Saliendo del programa..." << endl;
        }
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;

    }

    cout << endl;
} while (option != 15);


    delete blockchain;
};