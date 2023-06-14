#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
    // Faltaria el b+tree;
    hashBlock* usersHash = new hashBlock;          // hashtable de par (usuario,bloque)
    int cantblocks =0;                             // cantidad de bloques
    

public:
 
  BlockChain() = default;
  ~BlockChain() {
      delete blocks, usersHash;
  };

  void init_blockchain();

  BlockChain(const string &users,const string &transacciones);
  void createUser(const string &username, const string &password);
  Block*& operator[](unsigned int);
  bool searchUser(const string &username, const string &password);
  void insertTransaction(const string &username, const string &password, const string &place, float amount, const string &date);
  bool searchData(const string &username, const string &password, const string &place, float amount, const string &date);
  void theTransactions(const std::string &username, const std::string &password);
  Transaction MaxDate(const std::string &username, const std::string &password);
  Transaction MinDate(const std::string &username, const std::string &password);
  Transaction MaxAmount(const std::string &username, const std::string &password);
  Transaction MinAmount(const std::string &username, const std::string &password);
  void cascade(const string &username, const string &password);
  void updateTransaction(int indexBlock, const string &username, const string &password, const string& place, float amount, const string& date);
  void downloadFile(const std::string& path);
};

BlockChain::BlockChain(const string &fileUsers, const string &fileTransactions){
    string line;
    auto *file = new ifstream(fileUsers);
    getline(*file, line,'\n');
    
    string username,password;
    while((*file) >> username >> password){
        createUser(username,password);
    }
    file->close();

    file = new ifstream(fileTransactions);
    getline(*file,line,'\n');
    
    string amount,place,date;
    while((*file) >> username >> password >> date >> place >> amount){
        insertTransaction(username,password,place,stof(amount),date);
    }
    file->close();
}


void BlockChain::init_blockchain() {
    // recrea la interfaz en consola del blockchain
    createUser("Ana", "sedest");
    insertTransaction("Ana", "sedest", "Lima", 23, "2023-5-1");
    insertTransaction("Ana", "sedest", "Surco", 9, "2023-2-9");
    createUser("Sebas", "caigua");
    insertTransaction("Sebas", "caigua", "Lima", 12, "2022-12-12");
    NodeB* iter = blocks->begin();
    while (iter != nullptr) {
        iter->data->printBlock();
        iter = iter->next;
    }
}


void BlockChain::createUser(const string &username, const string &password){
    string hash = username + "&&" + password;
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

bool BlockChain::searchUser(const string &username, const string &password){
    string hash = username + "&&" + password;
    return usersHash->search(hash);
}

void BlockChain::insertTransaction(const string &username, const string &password, const string &place, float amount, const string &date){
    string hash = username + "&&" + password;
    if (!usersHash->search(hash)) {
        std::cout << "---- Usuario no registrado ----" << endl;
        return;
    }
    Transaction transaccion(username,place, date, amount);
    usersHash->get(hash)->insert(transaccion);
    // std::cout << "end\n\n";
}

Transaction BlockChain::MaxDate(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transaction = usersHash->get(hash)->maxDate();
    return transaction;
}

Transaction BlockChain::MinDate(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transaction = usersHash->get(hash)->minDate();
    return transaction;
}

Transaction BlockChain::MaxAmount(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transaction = usersHash->get(hash)->maxAmount();
    return transaction;
}

Transaction BlockChain::MinAmount(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transaction = usersHash->get(hash)->minAmount();
    return transaction;
}

void BlockChain::cascade(const string &username, const string &password) {
    // identifica al hash no valido y procede a minar en cascada
}

void BlockChain::updateTransaction(int indexBlock, const string &username, const string &password, const string& place, float amount, const string& date){
    string hash = username + "&&" + password;
    Block* tx = usersHash->get(hash);
    Transaction toChange(username,place, date, amount);
    tx->updateTx(toChange, place, amount, date);
}


void BlockChain::downloadFile(const std::string& path = "./assets/data/datos.txt") {
    std::ofstream file(path);
    file << "client,place,amount,date" << endl;
    
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