#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "block.h"
#include "../structures/node.h"
#include "../structures/doubleList.h"
#include "../structures/chainHash.h"

using namespace std;

typedef DoubleList<Block*> LBlocks;
typedef ChainHash<string, Block*> hashBlock;

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
  void downloadFile(const std::string& path = "./assets/data/datos.txt"); //Mariel
  
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
}


void BlockChain::createUser(const string &username, const string &password){
    string hash = username + "&&" + password;
    Block* block = (cantblocks == 0)? new Block :
        new Block(cantblocks, blocks->end()->data->getHash());
    
    blocks->push_back(block);
    usersHash->set(hash, block);        
    ++cantblocks;
}

bool BlockChain::searchUser(const string &username, const string &password){
    string hash = username + "&&" + password;
    return usersHash->search(hash);
}

void BlockChain::insertTransaction(const string &username, const string &password, const string &place, float amount, const string &date){
    string hash = username + "&&" + password;
    Transaction *transaccion = new Transaction(username,place, date, amount);
    try {
        usersHash->get(hash)->insert(transaccion);
    } catch (string e) {  return;  }
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
    Transaction * transactions = usersHash->get(hash)->maxDate();
    //downloadFile(&transactions);
}

void BlockChain::MinDate(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction * transactions = usersHash->get(hash)->minDate();
    //downloadFile(&transactions);
}

void BlockChain::MaxAmount(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction * transactions = usersHash->get(hash)->maxAmount();
    //downloadFile(&transactions);
}

void BlockChain::MinAmount(const string &username, const string &password){
    string hash = username + "&&" + password;
    Transaction * transactions = usersHash->get(hash)->minAmount();
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
        Block::TxList* tx = usersHash->get_bucket(i)->data->value->getTransactions();
        // file << tx->nombre << " " << tx->string2 << " " << tx->amount << " " << tx->date << std::endl;
    }
    // out.close();
}