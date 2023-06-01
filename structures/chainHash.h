#include <sstream>
#include "doubleList.h"
using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;
const unsigned int PRIMECONST = 31;
const int capacityDEF = 10;

template<typename TK, typename TV>
class ChainHash {
private:    
    struct Entry {
        TK key;
        TV value;
        Entry(const TK& key, TV value): key(key), value(value) {}
        ~Entry() = default;
    };

public:
    typedef DoubleList<Entry*> HashList;
    typedef NodeList<Entry*> EntryNode;

private:
    HashList **buckets = new HashList*[capacityDEF];
    int capacity;              //tamanio del buckets
    int size = 0;              //cantidad de elementos totales

public:

    ChainHash(): capacity(capacityDEF) {
        buckets = new HashList*[capacityDEF];
    };
    ~ChainHash() = default;
    
    ChainHash(int capacity): capacity(capacity) {
        buckets = new HashList*[capacity];
	}

    size_t hashFunction(TK key) {
        stringstream skey;   skey << key;          // se llama a operator << para pasar a string
        string strkey = skey.str();
        int sum;

        // algoritmo Rolling polynomial
        for (int i = 0; i < strkey.size(); i++) {
            sum += (strkey[i] * (int)pow(PRIMECONST, i)) % capacity;
        }

        return sum % capacity;
    }

    void set(TK key, TV value){
        size_t index = hashFunction(key);
        buckets[index]->push_front(new Entry(key, value));
    }

    TV get(TK key){
        size_t index = hashFunction(key);
        EntryNode* nodetemp = buckets[index]->begin();
        while (nodetemp != nullptr) {
            if (nodetemp->data->key == key)
                return nodetemp->data->value; 

            nodetemp = nodetemp->next;
        }
        throw std::out_of_range("key unbound in hashtable");
    };

    bool search(TK key) {
        try{
            TV bound = get(key);   return true;
        } catch {
            return false;
        }
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
                set(temp->key, temp->value);
                temp = temp->next;
            }
        }

        capacity = capacity*2;
    }
};