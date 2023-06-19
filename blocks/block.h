#ifndef BLOCK_H
#define BLOCK_H

#include <ctime>
#include <sstream>
#include <string>
#include "../structures/heap.h"
#include "../structures/avl.h"
#include "../structures/doubleList.h"
#include "../utils/SHA256.h"
#include "transaction.h"

using namespace std;

typedef DoubleList<Transaction> TxList;
typedef AVLTree<Transaction> TxAVL;
typedef NodeList<Transaction> TxNode;

typedef std::function<bool(const Transaction&, const Transaction&)> CompTx;

const CompTx mayor_amount = [](const Transaction& a, const Transaction& b) { return a.amount < b.amount; };
const CompTx minor_amount = [](const Transaction& a, const Transaction& b) { return a.amount > b.amount; };

// compare las fechas en formato Unix de tipo int
const CompTx mayor_date = [](const Transaction& a, const Transaction& b) { return dateToUnix(a.date) < dateToUnix(b.date); };
const CompTx minor_date = [](const Transaction& a, const Transaction& b) { return dateToUnix(a.date) > dateToUnix(a.date); };


// Definición de la estructura del bloque
class Block {
private:
    int index;                          // Índice del bloque en la cadena
    string timestamp;              // Marca de tiempo en la que se crea el bloque
    int cantTransactions = 0;           // Cantidad de transacciones
    
    TxList* list_data = new TxList;
    TxAVL* tree_amount = new TxAVL(minor_amount, mayor_amount);
    TxAVL* tree_date = new TxAVL(minor_date, mayor_date);
    
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
        delete tree_amount;
        delete tree_date;
    }


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
            nodetemp = nodetemp->next;
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

    int get_cantTx() { return cantTransactions; }

    // Imprimer el bloque con la información de las transacciones en consola
    void printBlock(){
        std::cout << "┌----------------------------┐" << endl;
        std::cout << " ---------------------------- " << endl;
        std::cout << "Block Index N: " << index << " ----- Nonce: " << nonce << endl;;
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

        std::cout << " ---------------------------- " << endl;
        std::cout << "└----------------------------┘" << endl;
        delete nodetemp;
    }


    // Inserta una nueva transaccion
    void insert(Transaction transaction) {
        list_data->push_back(transaction);
        tree_amount->insert(transaction);
        tree_date->insert(transaction);
        this->hash = calculateHash();
        mineBlock();
        ++cantTransactions;
    }


    // actualiza una transaccion espacífica
    void updateTx(Transaction changed, string place, int amount, string date) {
        Transaction newer(changed.client, place, date, amount);
        tree_amount->update(changed, newer);
        tree_date->update(changed, newer);
        list_data->update(changed, newer);
        // rehashea
        this->hash = calculateHash();
    }


    // remover una transaccion
    void removeTransaction(int indexTx) {
        Transaction transaction = list_data->operator[](indexTx);
        list_data->remove(indexTx);
        tree_amount->remove(transaction);
        tree_date->remove(transaction);
        // rehashea
        this->hash = calculateHash();
        --cantTransactions;
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
        return tree_amount->maxValue();
    }

    // -- La transaccion con menor monto
    Transaction minAmount() {
        return tree_amount->minValue();
    }

    // -- La transaccion con la fecha mas reciente
    Transaction maxDate() {
        return tree_date->maxValue();
    }

    // -- La transaccion con la fecha mas antigua
    Transaction minDate() {
        return tree_date->minValue();
    }

    TxList* rangeDate(string date1, string date2); 

    TxList* rangeAmount(float amount1, float amount2); 
    
};

#endif // BLOCK_COMPONENT_H