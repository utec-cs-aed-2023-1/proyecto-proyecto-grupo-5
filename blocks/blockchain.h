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

  BlockChain(const string &users,const string &transacciones); //Leo
  void createUser(const string &username, const string &password); //Leo
  Block*& operator[](unsigned int);
  bool searchUser(const string &username, const string &password); //Leo
  void insertTransaction(const string &username, const string &password, const string &place, float amount, const string &date); //Leo
  bool searchData(const string &username, const string &password, const string &place, float amount, const string &date); //Leo
  void theTransactions(const std::string &username, const std::string &password); //Noemi
  void date(const std::string &username, const std::string &password); //Noemi
  void Amount(const std::string &username, const std::string &password); //Noemi
  void MaxDate(const std::string &username, const std::string &password); //Noemi
  void MinDate(const std::string &username, const std::string &password); // Mariel
  void MaxAmount(const std::string &username, const std::string &password); // Mariel
  void MinAmount(const std::string &username, const std::string &password); // Mariel
  void cascade(const string &username, const string &password); // Mariel
  void downloadFile(const std::string& path); //Mariel
  
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
    for (int i=0; i<=idx; ++i) {
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

/*
bool BlockChain::searchData(const string &username, const string &password, const string &place, float amount, const string &date){
    string hash = username + "&&" + password;
    auto *transaccion= new Transaction(username, place, date,amount);
    stringstream key;
    key << *(transaccion);
    return usersHash.get(hash)->data->data_hash.search(key.str());
}*/

/*void BlockChain::theTransactions(const string &username, const string &password){
    string hash = username + "&&" + password;
    Block::TxList* userTransactions = usersHash->get(hash)->getTransactions();
    //downloadFile(&userTransactions);
}*/

void BlockChain::MaxDate(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transactions = usersHash->get(hash)->maxDate();
    //downloadFile(&transactions);
}

void BlockChain::MinDate(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transactions = usersHash->get(hash)->minDate();
    //downloadFile(&transactions);
}

void BlockChain::MaxAmount(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transactions = usersHash->get(hash)->maxAmount();
    //downloadFile(&transactions);
}

void BlockChain::MinAmount(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction transactions = usersHash->get(hash)->minAmount();
    //downloadFile(&transactions);
}

/*
void BlockChain::cascade(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction * transactions = this->usersHash.get(hash)->data;
    //downloadFile(&transactions);
}*/


void BlockChain::downloadFile(const std::string& path = "./assets/data/datos.txt") {
    std::ofstream* file = new ofstream(path);
    for (int i=0; i < cantblocks; i++) {
        TxList* tx = usersHash->get_bucket(i)->data.value->getTransactions();
        // file << tx->nombre << " " << tx->string2 << " " << tx->amount << " " << tx->date << std::endl;
    }
    // out.close();
}