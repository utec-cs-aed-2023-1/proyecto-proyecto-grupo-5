#include<iostream>

#include "node.h"
using namespace std;

template<typename T>
class BPlustree{
private:
    NodeBplusTree<T>* root = nullptr;
    int M;                              // grado del root
    int n;                              // n de elementos

    T minKey(NodeBplusTree<T>* node){ //minimo valor 
        if(node->leaf)
            return node->keys[0];
        return minKey(node->children[0]);
    }

    T maxKey(NodeBplusTree<T>* node){ //maximo valor 
        if(node->leaf)
            return node->keys[node->count-1];
        return maxKey(node->children[node->count]);
    }

    void clear(NodeBplusTree<T>* node){ //eliminar el subarbol por un nodo
        if(node->leaf){
            delete node;
            return;
        }
        for(int i=0;i<=node->count;i++){
            clear(node->children[i]);
        }
        delete node;
    }

    void displayChildren(NodeBplusTree<T>* node, int index){
        if (node->leaf) {
            for (int i=0; i<M-1; ++i)
               cout << node->keys[i] << " ";
            return;
        }

        for(int i=0;i<node->children[index]->count;i++){
            displayChildren(node->children[index]->keys[i]);
        }
        cout << " | ";
    }

    bool search(NodeBplusTree<T>* node, T key){
        int i=0;
        while(i<node->count && key>node->keys[i])
            i++;
      
        if(i<node->count && key==node->keys[i])
            return true;
        
        if(node->leaf)
            return false;
        
        return search(node->children[i],key);
    }

    void remove(NodeBplusTree<T>* node) {

    }


public:
    BPlustree() = default;

    // Lo complejo va aqui

    void insert(T key){
        
    }

    // Y aqui

    void remove(T key){         // qui
        // aqui se llamar a removeNotFull en un caso
        // o+en otro caso eliminiar cuando el nodo esta lleno
    }

    void display(){
        for(int i=0;i<root->count;i++)
            displayChildren(root, i);
        
    }

    bool search(T key){
        return !(root->search(key) == nullptr);
    }

    T minKey(){
        return minKey(root);
    } 
    T maxKey(){
        return maxKey(root);
    }

    void clear(){
        clear(root);
        root=nullptr;
        n = 0;
    }

    int size(){  return n;  }
};