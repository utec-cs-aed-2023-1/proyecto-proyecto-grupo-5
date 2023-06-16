#include <fstream>
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
 
  BlockChain() = default;
  int get_cantBlocks() { return cantblocks; }
  ~BlockChain() {
      delete blocks, usersHash;
  };

  void init_blockchain();

  BlockChain(const string &usuarios,const string &retiros);
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
};

BlockChain::BlockChain(const string &archivoUsuarios, const string &archivoRetiros){
    // CAMBIAR LOGICA

    string line;
    auto *file = new ifstream(archivoUsuarios);
    getline(*file, line,'\n');
    
    string username;
    while((*file) >> username){
        crearUsuario(username);
    }
    file->close();

    file = new ifstream(archivoRetiros);
    getline(*file,line,'\n');
    
    string amount,place,date;
    while((*file) >> username >> date >> place >> amount){
        insertRetiro(username,place,stof(amount),date);
    }
    file->close();
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
    for (int i=0; i<idx; ++i) {
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
}
