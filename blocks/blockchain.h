#include <fstream>
#include <string>
#include "block.h"
#include "../structures/node.h"
#include "../structures/doubleList.h"
#include "../structures/chainHash.h"

using namespace std;
using std::cout;

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
  ~BlockChain() {
      delete blocks, usersHash;
  };

  void init_blockchain();

  BlockChain(const string &usuarios,const string &retiros);
  void crearUsuario(const string &nombreUsuario);
  Block*& operator[](unsigned int);
<<<<<<< HEAD
  bool searchUser(const string &username, const string &password);
  void insertTransaction(const string &username, const string &password, const string &place, float amount, const string &date);
  Transaction MaxDate(const std::string &username, const std::string &password);
  Transaction MinDate(const std::string &username, const std::string &password);
  Transaction MaxAmount(const std::string &username, const std::string &password);
  Transaction MinAmount(const std::string &username, const std::string &password);
  void cascade(const string &username, const string &password);
  void updateTransaction(int indexBlock, const string &username, const string &password, const string& place, float amount, const string& date);
  void downloadFile(const std::string& path);
=======
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
>>>>>>> 0b80a9005ceef1acfc7d41465238e2de096b5a9b
};

BlockChain::BlockChain(const string &archivoUsuarios, const string &archivoRetiros){
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
<<<<<<< HEAD
=======
    // recrea la interfaz en consola del blockchain
    crearUsuario("Ana");
    insertRetiro("Ana", "Lima", 23, "2023-5-1");
    insertRetiro("Ana", "Surco", 9, "2023-2-9");
    crearUsuario("Sebas");
    insertRetiro("Sebas", "Lima", 12, "2022-12-12");
>>>>>>> 0b80a9005ceef1acfc7d41465238e2de096b5a9b
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        iter->data->printBlock();
        iter = iter->next;
    }
}


void BlockChain::crearUsuario(const string &nombreUsuario){
    string hash = nombreUsuario;
    // cout << "crea " << hash << endl;
    Block* block = (cantblocks == 0)? new Block :
        new Block(cantblocks, blocks->end()->data->getHash());
    
    blocks->push_back(block);
    // cout << "push list" << endl;
    usersHash->set(hash, block);
    // cout << "push hash" << endl;
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
    // std::cout << "end\n\n";
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
<<<<<<< HEAD
    file << "client place amount date" << endl;
=======
    file << "client,place,date,amount" << endl;
>>>>>>> 0b80a9005ceef1acfc7d41465238e2de096b5a9b
    
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
