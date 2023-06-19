#ifndef CHAINHASH_H
#define CHAINHASH_H

#include <sstream>
#include "doubleList.h"
#include "constants.h"
#include <cmath>
using namespace std;

template<typename TK, typename TV>
class ChainHash {
private:    
    struct Entry {
        TK key;
        TV value;
        Entry(const TK& key, TV value): key(key), value(value) {}

        bool operator==(const Entry pair2) {
            return this->key == pair2.key && this->value == pair2.value;
        }
        
        ~Entry() = default;
    };

public:
    friend ostream& operator<<(ostream& os, Entry* pair) {
        os << "(" << pair.key << "," << pair.value << ") ";
        return os;
    }

private:
    Entry** buckets;
    int capacity;              //tamanio del buckets
    int size = 0;              //cantidad de elementos totales

public:

    ChainHash(): capacity(capacityHashDEF) {
        buckets = new Entry*[capacityHashDEF];
        for (short i=0; i<capacityHashDEF; ++i) {
            buckets[i] = nullptr;
        }
    }

    ~ChainHash() {
        for (short i=0; i<capacity; ++i) {
            delete buckets[i];
        }
        delete[] buckets;
    };
    
    ChainHash(int capacity): capacity(capacity) {
        buckets = new Entry*[capacity];
        for (short i=0; i<capacity; ++i) {
            buckets[i] = nullptr;
        }
    }

    void set(TK key, TV& value){
        if (fillFactor() >= maxFillFactor) rehashing();

        size_t index = hashFunction(key);
        buckets[index] = new Entry(key, value);
    }

    TV& get(TK key){
        size_t index = hashFunction(key);
        if (buckets[index] != nullptr)
            return buckets[index]->value;
        throw std::out_of_range("key unbound in hashtable");
    }

    void viewHash() {
        for (int i=0; i<capacity; ++i) {
            cout << "Bucket " << i+1 << " size: " << bucket_size(i) << "\n -- ";
            if (!buckets[i] == nullptr)
                cout << buckets[i] << " ";
        } cout << endl;
    }

    bool search(TK key) {
        size_t index = hashFunction(key);
        if (buckets[index] != nullptr)
            return true;
        return false;
    }

    int bucket_count() const {
        return capacity;
    }

    int bucket_size(unsigned int pos) const {
        return buckets[pos]->size();
    };

private:
    double fillFactor() const {
        return static_cast<double>(size) / (capacity * maxColision);
    }

    void rehashing(){
        // Aumentar la capacidad del arreglo original
        capacity *= 2;
        Entry** newbuckets = new Entry*[capacity];

        // Insertar todos los elementos del arreglo original en el nuevo arreglo
        size_t index;
        for (short i=0; i<(int)capacity/2; ++i) {
            index = hashFunction(buckets[i]->key);
            newbuckets[index] = move(buckets[i]);
        }
        buckets = newbuckets;
    }

    size_t hashFunction(TK key) {
        stringstream skey;   skey << key;          // se llama a operator << para pasar a string
        string strkey = skey.str();
        int sum = 0;

        // algoritmo Rolling polynomial
        for (int i = 0; i < (int) strkey.size(); i++) {
            int res = (int)strkey[i] * (int)pow(PRIMECONST, i);
            sum += res % capacity;
        }

        return sum % capacity;
    }
};

#endif