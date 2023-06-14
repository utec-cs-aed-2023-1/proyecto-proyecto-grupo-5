#ifndef BLOCK_COMPONENT_H
#define BLOCK_COMPONENT_H

#include <ctime>
#include <sstream>
#include <string>
#include "../structures/heap.h"
#include "../structures/doubleList.h"
#include "../utils/SHA256.h"
#include "transaction.h"

using namespace std;

typedef std::function<bool(const Transaction&, const Transaction&)> CompTx;
typedef std::function<void(Transaction&, const string&)> ChangeTx;

typedef DoubleList<Transaction> TxList;
typedef Heap<Transaction> TxHeap;
typedef NodeList<Transaction> TxNode;

const CompTx mayorAmount = [](const Transaction& a, const Transaction& b) { return a.amount > b.amount; };
const CompTx mayorDate = [](const Transaction& a, const Transaction& b) { return dateToUnix(a.date) > dateToUnix(b.date); };

// Definición de la estructura del bloque
class Block {
private:
    int index;                          // Índice del bloque en la cadena
    string timestamp;              // Marca de tiempo en la que se crea el bloque
    
    TxList* list_data = new TxList;
    TxHeap* minheap_amount = new TxHeap(mayorAmount, TxHeap::MIN_HEAP);
    
    TxHeap* maxheap_amount = new TxHeap(mayorAmount);
    TxHeap* minheap_date = new TxHeap(mayorDate, TxHeap::MIN_HEAP); 
    
    TxHeap* maxheap_date = new TxHeap(mayorDate);
    
    string previousHash;           // Hash del bloque anterior en la cadena
    string hash;                   // Hash del bloque actual
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
    string calculateHash() {
        stringstream ss;
        // agregamos la metadata 
        ss << index << timestamp << previousHash << nonce;

        // agregamos las transacciones
        TxNode* nodetemp = getTransactions()->begin();
        while (nodetemp != nullptr) {
            ss << nodetemp->data;
        }

        return sha256(ss.str());
    }


    // Realiza el minado para vakidar la seguridad del bloque por el codigohash
    // * Calcula el hash del bloque actual y se compara con el hash objetivo
    // * Si el hash actual no es igual al hash objetivo, se incrementa el nonce
    void mineBlock() {
        string target(DIFFICULTY, '0');
        while (hash.substr(0, DIFFICULTY) != target) {
            nonce++;
            hash = calculateHash();
        }
        // std::cout << "Block mined: " << hash << endl;
    }


    // Imprimer el bloque con la información de las transacciones en consola
    void printBlock(){
        std::cout << "------------------------------" << endl;
        std::cout << "------------------------------" << endl;
        std::cout << "Block Index N°: " << index << endl;
        std::cout << "-- Created at: " << unixToDate(timestamp) << endl;
        std::cout << "-- Previous Hash: " << previousHash << endl;
        std::cout << "-- Hash: " << hash << endl;
        std::cout << "-- Transactions :" << endl;
        TxNode* nodetemp = getTransactions()->begin();
        while (nodetemp != nullptr) {
            std::cout << "---------" << endl;
            nodetemp->data.printTransaction();
            std::cout << "---------" << endl;
            nodetemp = nodetemp->next;
        }

        std::cout << "------------------------------" << endl;
        std::cout << "------------------------------" << endl;
        delete nodetemp;
    }


    // Inserta una nueva transaccion
    void insert(Transaction transaction) {
        list_data->push_back(transaction);
        minheap_amount->push(transaction);
        maxheap_amount->push(transaction);
        minheap_date->push(transaction);
        maxheap_date->push(transaction);
        this->hash = calculateHash();
        mineBlock();
    }

    // actualiza una transaccion espacífica
    void updateTx(Transaction changed, string place, int amount, string date) {
        Transaction newer(changed.client, place, changed.date, amount);
        minheap_amount->update(changed, newer);
        maxheap_amount->update(changed, newer);
        minheap_date->update(changed, newer);
        minheap_date->update(changed, newer);
        list_data->update(changed, newer);
        // rehashea
        this->hash = calculateHash();
    }

    // remover una transaccion
    void removeTransaction(int indexTx) {
        Transaction transaction = list_data->operator[](indexTx);
        list_data->remove(indexTx);
        minheap_amount->remove(transaction);
        maxheap_amount->remove(transaction);
        minheap_date->remove(transaction);
        minheap_date->remove(transaction);
        // rehashea
        this->hash = calculateHash();
    }

    // devuelve el hashcode en lectura
    string getHash() {
        return hash;
    }

    // devuelve la lista de transacciones
    TxList* getTransactions() {
        return list_data;
    } 

    // Valida si se encuentra la transaccion 
    bool search(Transaction transaction) {
        return list_data->search(transaction);
    } 

    // -- La transaccion con mayor monto
    Transaction maxAmount() {
        return maxheap_amount->top();
    }

    // -- La transaccion con menor monto
    Transaction minAmount() {
        return minheap_amount->top();
    }

    // -- La transaccion con la fecha mas reciente
    Transaction maxDate() {
        return maxheap_date->top();
    }

    // -- La transaccion con la fecha mas antigua
    Transaction minDate() {
        return minheap_date->top();
    }

    TxList* rangeDate(string date1, string date2); 

    TxList* rangeAmount(float amount1, float amount2); 
    
};


#endif // BLOCK_COMPONENT_H