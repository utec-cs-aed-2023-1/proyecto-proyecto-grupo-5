#ifndef NODE_H
#define NODE_H
#include <sstream>

template<typename T>
struct NodeList {
    
    T data;               // Almacena el valor del nodo
    NodeList<T> *next;    // Puntero al siguiente nodo en la lista
    NodeList<T> *prev;    // Puntero al nodo anterior en la lista

    NodeList() : data(0), next(nullptr), prev(nullptr) {}
    // Constructor por defecto. Inicializa los miembros con valores predeterminados.

    NodeList(T _data) : data(_data), next(nullptr), prev(nullptr) {}
    // Constructor que permite inicializar el valor del nodo con un valor específico.

    void killSelf() {
        prev->next = next;  // El siguiente del nodo anterior apunta al siguiente del nodo actual
        next->prev = prev;  // El anterior del siguiente nodo apunta al nodo anterior
        next = nullptr;     // Establece el siguiente del nodo actual como nullptr
        prev = nullptr;     // Establece el anterior del nodo actual como nullptr
    }

    std::string to_string(std::string sep = " ") {
        std::stringstream ss;
        NodeList<T>* temp = this;
        while (temp != nullptr) {
            ss << temp->data << sep;
            temp = temp->next;
        }
        std::string res = ss.str();
        return res.substr(0, res.size()-sep.size());
    }
};


template <typename T>
struct NodeBT {

    T data; // El valor del nodo
    NodeBT* left; // Puntero al hijo izquierdo
    NodeBT* right; // Puntero al hijo derecho
    int height;

    // Constructor por defecto
    NodeBT() : left(nullptr), right(nullptr) {}

    // Constructor con un valor dado
    NodeBT(T value) : data(value), left(nullptr), right(nullptr) {}


    // Función que elimina todos los nodos a partir del actual
    void killSelf() {
        // Si el hijo izquierdo no es nulo, llamar recursivamente a KillSelf en el hijo izquierdo
        if (left != nullptr)
            left->killSelf();
        // Si el hijo derecho no es nulo, llamar recursivamente a KillSelf en el hijo derecho
        if (right != nullptr)
            right->killSelf();

        // Eliminar el nodo actual
        delete this;
    }
};


//// NODE B+

template <typename T>
struct NodeBplusTree {
    T* keys;
    NodeBplusTree<T>** children;
    NodeBplusTree<T>* next = nullptr;
    int count = 0;
    bool leaf;
    int M;

    NodeBplusTree(int M){
        keys = new T[M-1];
        children = new NodeBplusTree<T>*[M];
        this->leaf = true;
        this->M = M;
    }

    void splitChildren(int index){
        NodeBplusTree<T>* origin = children[index];
        NodeBplusTree<T>* sibling = new NodeBplusTree<T>();

        if(origin->leaf){

		}
        else if (origin->leaf == false){
            for(int i=M/2+1,j=0;i<M;i++,j++){
                sibling->keys[j] = origin->keys[i];
            }

            sibling->count = M - ((M/2) + 1);
            origin->count = M/2;

            //  FALTA
        
        }
    }

    void killSelf() {
        if (leaf) {
            delete[] keys;
            delete[] children;
        }
        for (int i = 0; i <= count; i++) {
            children[i]->killSelf();
        }
        delete[] keys;
        delete[] children;
    }

    void insertNonFull(int key){
        int i=count-1;
        if (leaf){
            while (i>=0 && keys[i]>key){
                keys[i+1]=keys[i];
                i--;
            }
            keys[i+1]=key;
            count++;
        }
        else {
            while (i>=0 && keys[i]>key)
                i--;

            if (children[i+1]->count==2*M-1){
                splitChild(i+1,children[i]);
                if(keys[i+1]<key)
                    i++;
            }
            children[i+1]->insertNonFull(key);
        }
    }

    void deleteFromLeaf(T key){

    }

    void deleteFrom_noLeaf(int index, T key){

    }

    void removeNotFull(T key){   // quitar key del nodo

    }

};





template <typename T>
struct NodeBtree {
    T* keys;                  // array de keys
    NodeBtree** children;     // array de punteros a hijos
    int count;                // cantidad de keys
    bool leaf;                // indicador de nodo hoja
    int M;                    // M u orden del arbol

    NodeBtree() : keys(nullptr), children(nullptr), count(0) {}
    NodeBtree(int M,bool leaf) {
        keys = new T[2*M - 1];
        children = new NodeBtree<T>*[2*M];
        count = 0;
        this->leaf = leaf;
        this->M = M;
    }

    void killSelf() {
        if (leaf) {
            delete[] keys;
            delete[] children;
        }
        for (int i = 0; i <= count; i++) {
            children[i]->killSelf();
        }
        delete[] keys;
        delete[] children;
    }

    void splitChild(int i, NodeBtree<T>* node){
        NodeBtree<T>* child=new NodeBtree<T>(node->M,node->leaf);
        child->count=M-1;

        for(int j=0;j<M-1;j++){
          child->keys[j]=node->keys[j+M];
        }

        if(!node->leaf){
            for(int j=0;j<M;j++) {
                child->children[j]=node->children[j+M];
            }
        }

        node->count=M-1;

        for(int j=count;j>i;j--){
            children[j+1]=children[j];
        }

        children[i+1]=child;

        for(int j=count-1;j>=i;j--){
            keys[j+1]=keys[j];
        }

        keys[i]=node->keys[M-1];
        count++;
    }

    void insertNonFull(int key){
        int i=count-1;
        if (leaf){
            while (i>=0 && keys[i]>key){
                keys[i+1]=keys[i];
                i--;
            }
            keys[i+1]=key;
            count++;
        }
        else {
            while (i>=0 && keys[i]>key){
                i--;
            }

            if (children[i+1]->count==2*M-1){
                splitChild(i+1,children[i]);
                if(keys[i+1]<key){
                    i++;
                }
            }
            children[i+1]->insertNonFull(key);
        }
    }

};

#endif