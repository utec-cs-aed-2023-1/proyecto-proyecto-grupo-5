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
    LBlocks* blocks =new LBlocks;                  // lista de bloques enlazados
    hashBlock* usersHash = new hashBlock;        //hashtable de par (usuario,bloque)
    int cantblocks =0;                             // cantidad de bloques
    
public:
 
  BlockChain(const string path);
  int get_cantBlocks() { return cantblocks; }
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
  void cascada(const string &nombreUsuario);
  void downloadFile(const string& path);
};

BlockChain::BlockChain(const string path="./assets/data/datamin.csv"){
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    cout << "Archivo abierto" << endl;

    string line;
    
    DoubleList<string> data;
    while(getline(file, line)) {
        stringstream ss(line);
        string word;
        while(getline(ss, word, ','))
            data.push_back(word);

        auto b = data.begin(), e = data.end();
        string username = b->data;
        string place = b->next->data;
        string date = e->prev->data;
        float amount = stof(e->data);
        // en caso no existe el usuario, crearlo
        if (!usersHash->search(username)) {
            crearUsuario(username);
        }


        insertRetiro(username, place, amount, date);
        data.clear();
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
    string key = nombreUsuario;
    Block* block = (cantblocks == 0)? new Block :
    new Block(cantblocks, blocks->end()->data->hash);
    
    blocks->push_back(block);
    usersHash->set(key, block);
    ++cantblocks;
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
        return usersHash->get(key)->data->value;
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
    auto findblock = usersHash->get(key);
    cout << "fine" << endl;
    findblock->data->value->insert(transaccion);
}

Transaction BlockChain::MaxFecha(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->value->maxDate();
    return transaction;
}

Transaction BlockChain::MinFecha(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->value->minDate();
    return transaction;
}

Transaction BlockChain::MaxMonto(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->value->maxAmount();
    return transaction;
}

Transaction BlockChain::MinMonto(const string &nombreUsuario){
    string key = nombreUsuario;
    Transaction transaction = usersHash->get(key)->data->value->minAmount();
    return transaction;
}

void BlockChain::cascada(const string &nombreUsuario){
    string hash = nombreUsuario;
    usersHash->get(hash)->data->value->mineBlock();
    auto i = usersHash->get(hash)->next;
    while (i != nullptr) {
        i->data->value->previousHash = i->prev->data->value->hash;
        i->data->value->mineBlock();
        i = i->next;
    }
}
