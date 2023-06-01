#ifndef TRANSATION_COMPONENT_H
#define TRANSATION_COMPONENT_H

#include <iostream>
#include <chrono>
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
    void printTransaction() const {
        std::time_t unixTimestamp(std::stol(date));
        string formattedDate = std::asctime(std::localtime(&unixTimestamp));

        std::cout << "Client: " << client << std::endl;
        std::cout << "Place: " << place << std::endl;
        std::cout << "Date: " << formattedDate.substr(0, 24) << std::endl;
        std::cout << "Amount: " << amount << std::endl;
    }
};


// Representación textual de una transacción   
ostream &operator<<(ostream &os, const Transaction &tx) {
    std::time_t unixTimestamp(std::stol(tx.date));
    std::string date = std::asctime(std::localtime(&unixTimestamp));

    os << "(" << tx.client << " , " << tx.date << ", " << tx.amount << ", " << date.substr(0, 24) << ")";
    return os;
}

#endif // TRANSATION_COMPONENT_H