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
typedef ChainHash<string, Block*> hashBlock;
typedef NodeList<Block*> NodeB;

class BlockChain {
private:
    LBlocks* blocks = new LBlocks;                  // lista de bloques enlazados
    hashBlock* usersHash = new hashBlock;          // hashtable de par (usuario,bloque)
    int cantblocks =0;                             // cantidad de bloques
    
public:
 
  BlockChain(const string path);
  int get_cantBlocks() { return cantblocks; }
  ~BlockChain() {
      delete blocks;
      delete usersHash;
  };

  void init_blockchain();
  void crearUsuario(const string &nombreUsuario);
  Block*& operator[](unsigned int);
  bool buscandoUsuario(const string &nombreUsuario);
  void insertRetiro(const string &nombreUsuario, const string &lugar, float monto, const string &fecha);
  bool buscandoData(const string &nombreUsuario, const string &lugar, float monto, const string &fecha);
  void losRetiros(const std::string &nombreUsuario);
  Transaction MaxFecha(const std::string &nombreUsuario);
  Transaction MinFecha(const std::string &nombreUsuario);
  Transaction MaxMonto(const std::string &nombreUsuario);
  Transaction MinMonto(const std::string &nombreUsuario);
  void cascada(const string &nombreUsuario);
  void trayendoArchivo(const std::string& path);
  void updateTransaction(int indexBlock, const string &username, const string& place, float amount, const string& date);
};

BlockChain::BlockChain(const string path="../assets/data/data.csv"){
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    cout << "Archivo abierto" << endl;

    string line;
    
    while(getline(file, line)) {
        vector<string> data;
        stringstream ss(line);
        string word;

        while(getline(ss, word, ',')) {
            data.push_back(word);
        }


        string username = data[0];
        string place = data[1];
        float amount = stof(data[3]);
        string date = data[2];

        crearUsuario(username);
        insertRetiro(username, place, amount, date);

    }
    file.close();


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
    string hash = nombreUsuario;
    Block* block = (cantblocks == 0)? new Block :
        new Block(cantblocks, blocks->end()->data->getHash());
    
    blocks->push_back(block);
    usersHash->set(hash, block);
    ++cantblocks;
}

Block*& BlockChain::operator[](unsigned int idx) {
    NodeB* iter = blocks->begin();
    for (int i=0; i<(int) idx; ++i) {
        iter = iter->next;
    }
    return iter->data;
}

bool BlockChain::buscandoUsuario(const string &nombreUsuario){
    string hash = nombreUsuario;
    return usersHash->search(hash);
}

void BlockChain::insertRetiro(const string &nombreUsuario, const string &lugar, float monto, const string &fecha){
    string hash = nombreUsuario;
    if (!usersHash->search(hash)) {
        std::cout << "---- Usuario no registrado ----" << endl;
        return;
    }
    Transaction transaccion(nombreUsuario,lugar, fecha, monto);
    usersHash->get(hash)->insert(transaccion);
}

Transaction BlockChain::MaxFecha(const string &nombreUsuario){
    string hash = nombreUsuario;
    Transaction transaction = usersHash->get(hash)->maxDate();
    return transaction;
}

Transaction BlockChain::MinFecha(const string &nombreUsuario){
    string hash = nombreUsuario;
    Transaction transaction = usersHash->get(hash)->minDate();
    return transaction;
}

Transaction BlockChain::MaxMonto(const string &nombreUsuario){
    string hash = nombreUsuario;
    Transaction transaction = usersHash->get(hash)->maxAmount();
    return transaction;
}

Transaction BlockChain::MinMonto(const string &nombreUsuario){
    string hash = nombreUsuario;
    Transaction transaction = usersHash->get(hash)->minAmount();
    return transaction;
}

void BlockChain::cascada(const string &nombreUsuario) {
    // identifica al hash no valido y procede a minar en cascada
}

/*
void BlockChain::trayendoArchivo(const std::string& path = "./assets/data/500DATA.csv") {
    std::ofstream file(path);
    file << "client,place,date,amount" << endl;
    
    for (int i=0; i < cantblocks; i++) {
        TxList* tx = blocks->operator[](i)->getTransactions();
        TxNode* temp = tx->begin();
        while (temp != nullptr) {
            file << temp->data << std::endl;
            temp = temp->next;
        }
    }
    file.close();
}*/

void BlockChain::updateTransaction(int indexBlock, const string &username, const string& place, float amount, const string& date){
    string hash = username ;
    Block* tx = usersHash->get(hash);
    Transaction toChange(username,place, date, amount);
    tx->updateTx(toChange, place, amount, date);
}