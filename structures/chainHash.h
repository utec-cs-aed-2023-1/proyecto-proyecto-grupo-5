#ifndef CHAINHASH_H
#define CHAINHASH_H

#include <sstream>
#include "doubleList.h"
#include "constants.h"
#include "../utils/SHA256.h"
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

    DoubleList<Entry*>** buckets;
    int capacity;              //tamanio del buckets
    int size = 0;              //cantidad de elementos totales

public:
    ChainHash(int capacity = capacityHashDEF): capacity(capacity) {
        buckets = new DoubleList<Entry*>*[capacity];
        for (short i=0; i<capacity; ++i) {
            buckets[i] = nullptr;
        }
    }

    ~ChainHash() {
        for (short i=0; i<capacity; ++i) {
            delete buckets[i];
        }
        delete[] buckets;
    };
    

    void set(TK key, TV& value){
        if (fillFactor() >= maxFillFactor) rehashing();

        size_t index = hashFunction(key);
        if (buckets[index] == nullptr)
            buckets[index] = new DoubleList<Entry*>;

        buckets[index]->push_back(new Entry(key, value));
    }

    NodeList<Entry*>* get(TK key){
        size_t index = hashFunction(key);
        NodeList<Entry*>* it = buckets[index]->begin();
        while (it != nullptr) {
            if (it->data->key == key)   break;
            it = it->next;
        }
        return it;
        
    }

    // Entry*& find(NodeList<Entry*>*& node, TK key) {
    //     while (node != nullptr && node->data->key != key) {
    //         node = node->next;
    //     }
    //     return node;
    // }

    void viewHash() {
        for (int i=0; i<capacity; ++i) {
            if (buckets[i] != nullptr) {
                auto it = buckets[i]->begin();
                while (it != nullptr) {
                    cout << it->data << " ";
                    it = it->next;
                }
            }
            cout << buckets[i] << " ";
        } cout << endl;
    }

    bool search(TK key) {
        size_t index = hashFunction(key);
        if (buckets[index] != nullptr) {
            auto it = buckets[index]->begin();
            while (it != nullptr) {
                if (it->data->key == key)
                    return true;
                it = it->next;
            }
        }
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
        DoubleList<Entry*>** newbuckets = new DoubleList<Entry*>*[capacity];
        for (short i=0; i<capacity; ++i) {
            buckets[i] = nullptr;
        }

        // Insertar todos los elementos del arreglo original en el nuevo arreglo
        size_t new_i;
        for (short i=0; i<(int)capacity/2; ++i) {
            
            if (buckets[i] != nullptr) {
                auto it = buckets[i]->begin();
                while (it != nullptr) {
                    new_i = hashFunction(it->data->key);
                    if (newbuckets[new_i] != nullptr)
                        newbuckets[new_i] = new DoubleList<Entry*>;
                    newbuckets[new_i]->push_back(it->data);
                    it = it->next;
                }
            }
        }
        buckets = newbuckets;
        delete newbuckets;
    }

    size_t hashFunction(TK key) {
        stringstream skey;   skey << key;        // se llama a operator << para pasar a string
        string strkey = sha256(skey.str());

        std::stringstream stream;
        for (int i = 0; i < 4; ++i) {
            stream << std::hex << std::setw(2) << std::setfill('0') 
                   << static_cast<unsigned int>(strkey[i]);
        }
        unsigned int partialHash;
        stream >> partialHash;

        return partialHash % capacity;
    }
};

#endif