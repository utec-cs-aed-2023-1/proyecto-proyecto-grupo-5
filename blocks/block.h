#ifndef BLOCK_COMPONENT_H
#define BLOCK_COMPONENT_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <openssl/sha.h> 
#include "../structures/heap.h"
#include "../structures/doubleList.h"
// #include "../structures/chainHash.h"
#include "transaction.h"

using namespace std;
const int DIFFICULTY = 4;       // Número de ceros iniciales requeridos en el hash
const string HashGenesis(64, '0');

// Definición de la estructura del bloque
class Block {
public:
    typedef DoubleList<Transaction*> TxList;
    typedef Heap<Transaction*> TxHeap;

private:
    int index;                          // Índice del bloque en la cadena
    std::string timestamp;              // Marca de tiempo en la que se crea el bloque
    
    TxList* list_data = new TxList;
    TxHeap* minheap_amount = new TxHeap(TxHeap::MIN_HEAP);
    TxHeap* maxheap_amount = new TxHeap;
    TxHeap* minheap_date = new TxHeap(TxHeap::MIN_HEAP);
    TxHeap* maxheap_date = new TxHeap;
    
    std::string previousHash;           // Hash del bloque anterior en la cadena
    std::string hash;                   // Hash del bloque actual
    int nonce = 0;                      // Número utilizado en la Prueba de Trabajo

 public:

    // constructor asignando el hash del bloque anterior como prevHash del actual
    Block(int idx = 0, string prevHash = HashGenesis) {
        this->index = idx;
        this->timestamp = to_string(time(0));
        this->previousHash = prevHash;
        this->hash = calculateHash();
        mineBlock();
    }

    ~Block() {
        delete list_data;
        delete minheap_amount, minheap_date;
        delete maxheap_amount, maxheap_date;
    };


    // constructor copia a partir de otro bloque
    Block(const Block &other) {
        this->index = other.index;
        this->nonce = other.nonce;
        this->previousHash = other.previousHash;
        this->hash = other.hash;
    }


    // Calcula el codigoash con la información del bloque
    std::string calculateHash() {
        std::stringstream ss;
        ss << index << timestamp << previousHash << nonce;
        std::string input = ss.str();

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)input.c_str(), input.length(), hash);

        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashStream << std::hex << (int)hash[i];
        }

        return hashStream.str();
    }


    // Realiza el minado para vakidar la seguridad del bloque por el codigohash
    // * Calcula el hash del bloque actual y se compara con el hash objetivo
    // * Si el hash actual no es igual al hash objetivo, se incrementa el nonce
    void Block::mineBlock() {
        std::string target(DIFFICULTY, '0');
        while (hash.substr(0, DIFFICULTY) != target) {
            nonce++;
            hash = calculateHash();
        }
        std::cout << "Block mined: " << hash << std::endl;
    }


    // Imprimer el bloque con la información de las transacciones en consola
    void printBlock(Block block){
        std::cout << "Block Index N°: " << block.index << std::endl;
        // std::cout << "Timestamp: " << block.timestamp << std::endl; //
        std::cout << "Previous Hash: " << block.previousHash << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << std::endl;
    }

    // Inserta una nueva transaccion
    void insert(Transaction* transaction) {
        list_data->push_back(transaction);
        minheap_amount->push(transaction);
        maxheap_amount->push(transaction);
        minheap_date->push(transaction);
        maxheap_date->push(transaction);
        this->hash = calculateHash();
        mineBlock();
    }

    string getHash() {
        return hash;
    }

    TxList* getTransactions() {
        return list_data;
    } 

    // Valida si se encuentra la transaccion 
    bool search(Transaction* transaction) {
        return list_data->search(transaction);
    } 

    // -- La transaccion con mayor monto
    Transaction* maxAmount() {
        return maxheap_amount->top();
    }

    // -- La transaccion con menor monto
    Transaction* minAmount() {
        return minheap_amount->top();
    }

    // -- La transaccion con la fecha mas reciente
    Transaction* maxDate() {
        return maxheap_date->top();
    }

    // -- La transaccion con la fecha mas antigua
    Transaction* minDate() {
        return minheap_date->top();
    }


    DoubleList<Transaction*> rangeDate(string date1, string date2); 

    DoubleList<Transaction*> rangeAmount(float amount1, float amount2); 
    
};


#endif // BLOCK_COMPONENT_H