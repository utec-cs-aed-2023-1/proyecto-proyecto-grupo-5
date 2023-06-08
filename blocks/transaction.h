#ifndef TRANSATION_COMPONENT_H
#define TRANSATION_COMPONENT_H

#include <iostream>
#include "../utils/unix.h"
using namespace std;

// Definición de la información dentro de la transacción
struct Transaction {
    string client;
    string place;
    float amount;
    string date;
    
    Transaction() = default;
    ~Transaction() = default;

    // constructor a partir de datos formulados
    Transaction(const string& client, const string& place, const string& date, float amount) {
        this->client = client;
        this->place = place;
        this->date = date;
        this->amount = amount;
    } 

    // Función que imprime la transacción en consola.
    void printTransaction() {
        std::cout << "---- Client: " << client << std::endl;
        std::cout << "---- Place: " << place << std::endl;
        std::cout << "---- Date: " << date << std::endl;
        // std::cout << "---- Date: " << unixToTime(date) << std::endl;
        std::cout << "---- Amount: " << amount << std::endl;
    }
};


// Representación textual de una transacción   
ostream &operator<<(ostream &os, const Transaction &tx) {
    os << tx.client << "," << tx.date << "," << tx.amount << "," << dateToUnix(tx.date);
    return os;
}

bool operator==(const Transaction &tx1, const Transaction &tx2) {
    return tx1.client == tx2.client && tx1.amount == tx2.amount && tx1.date == tx2.date && tx1.place == tx2.place;
}

#endif // TRANSATION_COMPONENT_H