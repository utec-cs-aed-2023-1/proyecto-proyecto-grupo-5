#ifndef CHAINHASH_H
#define CHAINHASH_H

#include <sstream>
#include "doubleList.h"
#include "../utils/constants.h"
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
    typedef DoubleList<Entry> HashList;
    typedef NodeList<Entry> EntryNode;

    friend ostream& operator<<(ostream& os, Entry pair) {
        os << "(" << pair.key << "," << pair.value << ") ";
        return os;
    }

private:
    HashList **buckets;
    int capacity;              //tamanio del buckets
    int size = 0;              //cantidad de elementos totales

public:

    ChainHash(): capacity(capacityDEF) {
        buckets = new HashList*[capacityDEF];
        for (short i=0; i<capacityDEF; ++i) {
            buckets[i] = new HashList;
        }
    }

    ~ChainHash() {
        for (short i=0; i<capacity; ++i) {
            delete buckets[i];
        };
        delete[] buckets;
    };
    
    ChainHash(int capacity): capacity(capacity) {
        buckets = new HashList*[capacity];
        for (short i=0; i<capacity; ++i) {
            buckets[i] = new HashList;
        }
	}

    void set(TK key, TV& value){
        size_t index = hashFunction(key);
        buckets[index]->push_front(Entry(key, value));
    }

    TV& get(TK key){
        size_t index = hashFunction(key);
        EntryNode* nodetemp = buckets[index]->begin();
        cout << "index get " << index << endl;
        while (nodetemp != nullptr) {
            cout << "key: " << nodetemp->data.key << " == " << key << endl;
            if (nodetemp->data.key == key)  {
                cout << "done << " << nodetemp->data.value << endl;
                return nodetemp->data.value; 
            }
            nodetemp = nodetemp->next;
        }
        throw std::out_of_range("key unbound in hashtable");
    };

    void viewHash() {
        for (int i=0; i<capacity; ++i) {
            EntryNode* nodetemp = buckets[i]->begin();
            cout << "Bucket " << i+1 << " size: " << bucket_size(i) << "\n -- ";
            while (nodetemp != nullptr) {
                cout << nodetemp->data << " ";

                nodetemp = nodetemp->next;
            }
            cout << endl;
        }
    }

    bool search(TK key) {
        size_t index = hashFunction(key);
        cout << "index search " << index << endl;
        EntryNode* nodetemp = buckets[index]->begin();
        while (nodetemp != nullptr) {
            if (nodetemp->data.key == key)
                return true; 

            nodetemp = nodetemp->next;
        } 
        return false;
    }

    int bucket_count() const {
        return capacity;
    }

    int bucket_size(unsigned int pos) const {
        return buckets[pos]->size();
    };

    EntryNode* get_bucket(unsigned int pos) {
        return buckets[pos]->begin();
    }

private:
    double fillFactor() const {
        return static_cast<double>(size) / (capacity * maxColision);
    }

    void rehashing(){
        // Aumentar la capacidad del arreglo original
        HashList** newbuckets = buckets;
        delete[] buckets;
        buckets = new HashList*[capacity*2];

        // Insertar todos los elementos del arreglo original en el nuevo arreglo
        for (HashList* entry : newbuckets) {
            EntryNode* temp = entry->begin();
            while (temp != nullptr) {
                set(temp.key, temp.value);
                temp = temp->next;
            }
        }

        capacity = capacity*2;
    }

    size_t hashFunction(TK key) {
        stringstream skey;   skey << key;          // se llama a operator << para pasar a string
        string strkey = skey.str();
        int sum = 0;

        // algoritmo Rolling polynomial
        for (int i = 0; i < strkey.size(); i++) {
            int cter = (int)strkey[i];
            int power = (int)pow(PRIMECONST, i);
            int res = cter * power;
            // cout << " --- resolv in : " << strkey[i] << endl;
            // cout << "--- " << cter << " * " << power << " = " << res << endl;
            sum += res % capacity;
            // cout << " --- " << sum << endl;
        }

        return sum % capacity;
    }
};

#endif