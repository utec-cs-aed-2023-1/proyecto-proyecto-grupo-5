#include <fstream>
#include <iostream>
#include <string>
#include "block.h"
#include "../structures/node.h"
#include "../structures/doubleList.h"
#include "../structures/chainHash.h"
#include "../structures/heap.h"

using namespace std;

typedef DoubleList<Block*> LBlocks;
typedef ChainHash<string, NodeList<Block *> *> hashBlock;
typedef NodeList<Block*> NodeB;

class BlockChain {
private:
    LBlocks* blocks =new LBlocks;                  // lista de bloques enlazados
    hashBlock* usersHash = new hashBlock;        //hashtable de par (usuario,bloque)
    int cantblocks =0;
    string maxUser;                             // cantidad de bloques
    
public:
 
  BlockChain(const string path);
  int get_cantBlocks() { return cantblocks; }
  string getMaxUser() const { return maxUser; }
  ~BlockChain() {
      //delete usersHash;
  };

  void init_blockchain();
  void crearUsuario(const string &nombreUsuario);
  Block*& operator[](unsigned int);
  Block* buscandoBloquexKey(const string &nombreUsuario); // primera busqueda
  void insertRetiro(const string &nombreUsuario, const string &lugar, float monto, const string &fecha);
  Transaction MaxFecha(const std::string &nombreUsuario);
  Transaction MinFecha(const std::string &nombreUsuario);
  Transaction MaxMonto(const std::string &nombreUsuario);

  Transaction MinMonto(const std::string &nombreUsuario);
  void empieza_nombre_T(const string &prefijo);
  void contiene_nombre_T(const string &patron);
  void empieza_lugar_T(const string &prefijo);
  void contiene_lugar_T(const string &patron);
  void cascada(const string &nombreUsuario);
  void downloadFile(const string& path);
};

BlockChain::BlockChain(const string path = "../assets/data/datamin.csv") {
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    cout << "Archivo abierto" << endl;

    string line;
    float maxTransaction = 0.0; // Guarda la transacción máxima // Guarda el usuario con la transacción máxima

    while (getline(file, line)) {
        vector<string> data;
        stringstream ss(line);
        string word;

        while (getline(ss, word, ',')) {
            data.push_back(word);
        }

        string username = data[0];
        string place = data[1];
        float amount = stof(data[3]);
        string date = data[2];

        crearUsuario(username);
        insertRetiro(username, place, amount, date);

        // Si la transacción actual es más grande que la transacción máxima, actualizar la transacción y el usuario máximos
        if (amount > maxTransaction) {
            maxTransaction = amount;
            maxUser = username; // Actualizar el valor de maxUser
        }
    }
    file.close();

    // Imprimir la transacción máxima y el usuario correspondiente
    //cout << maxUser << endl;
}


void BlockChain::init_blockchain() {
    // recrea la interfaz en consola del blockchain
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        iter->data->printBlock();
        iter = iter->next;
    }
}


void BlockChain::crearUsuario(const string &nombreUsuario){
    /*
    string key = nombreUsuario;
    Block* block = (cantblocks == 0)? new Block :
    new Block(cantblocks, blocks->end()->data->getHash());
    
    blocks->push_back(block);
    usersHash->set(key, blocks->begin());
    ++cantblocks;*/

    if(blocks->is_empty()){
        Block* block = new Block;
        blocks->push_back(block);
        usersHash->set(nombreUsuario, blocks->begin());
        ++cantblocks;
    }
    else{
        Block* block = new Block(cantblocks, blocks->end()->data->hash);
        blocks->push_back(block);
        usersHash->set(nombreUsuario, blocks->end());
        ++cantblocks;
    }
}

Block*& BlockChain::operator[](unsigned int idx) {
    NodeB* iter = blocks->begin();
    for (int i=0; i<(int) idx; ++i) {
        iter = iter->next;
    }
    return iter->data;
}

// implementando primera busqueda ------------------------------
Block* BlockChain::buscandoBloquexKey(const string& nombreUsuario){
    string key = nombreUsuario;
    if (usersHash->search(key)){ //--
        return usersHash->get(key)->data;
    }
    return nullptr;
  }

void BlockChain::insertRetiro(const string &nombreUsuario, const string &lugar, float monto, const string &fecha){
    string key = nombreUsuario;
    if (!usersHash->search(key)) {
        std::cout << "---- Usuario no registrado ----" << endl;
        return;
    }
    Transaction transaccion(nombreUsuario,lugar, fecha, monto);
    usersHash->get(key)->data->insert(transaccion);
    usersHash->get(key)->data->hash = usersHash->get(key)->data->calculateHash();

    auto i = usersHash->get(key);
    i = i->next;
    while (i != nullptr) {
        i->data->previousHash = i->prev->data->hash;
        i->data->hash = i->data->calculateHash();
        i = i->next;
    }
}

Transaction BlockChain::MaxFecha(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->maxDate();
    return transaction;
}

Transaction BlockChain::MinFecha(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->minDate();
    return transaction;
}


/*
Transaction BlockChain::MaxMonto(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->maxAmount();
    return transaction;
}
*/

Transaction BlockChain::MaxMonto(const string& nombreUsuario) {
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->maxAmount();

    // Actualizar el valor de maxUser con el usuario correspondiente a la transacción máxima
    maxUser = nombreUsuario;

    return transaction;
}


Transaction BlockChain::MinMonto(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->minAmount();
    return transaction;
}


void BlockChain::empieza_nombre_T(const string &prefijo){
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        for (const auto& user : iter->data->searchFirst_nombre(prefijo)) {
            cout << user <<endl;
        }
        iter = iter->next;
    }
}

void BlockChain::contiene_nombre_T(const string &patron){
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        for (const auto& user : iter->data->searchContent_nombre(patron)) {
            cout << user <<endl;
        }
        iter = iter->next;
    }
}

void BlockChain::empieza_lugar_T(const string &prefijo){
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        for (const auto& place : iter->data->searchFirst_lugar(prefijo)) {
            cout << place <<endl;
        }
        iter = iter->next;
   }
}

void BlockChain::contiene_lugar_T(const string &patron){
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        for (const auto& place : iter->data->searchContent_lugar(patron)) {
              cout << place <<endl;
        }
        iter = iter->next;
   }
}




void BlockChain::cascada(const string &nombreUsuario){
    string hash = nombreUsuario;
    usersHash->get(hash)->data->mineBlock();
    auto i = usersHash->get(hash);
    i = i->next;
    while (i != nullptr) {
        i->data->previousHash = i->prev->data->hash;
        i->data->mineBlock();
        i = i->next;
    }
}
