#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "node.h"
using namespace std;

template <typename T>
class BTree {
private:
    NodeBtree<T>* root;
    int M;          // grado u orden del arbol
    int n;          // total de elementos en el arbol


    T minKey(NodeBtree<T>* node){ //minimo valor de la llave en el arbol
        if(node->leaf)
            return node->keys[0];
        return minKey(node->children[0]);
    }

    T maxKey(NodeBtree<T>* node){ //maximo valor de la llave en el arbol
        if(node->leaf)
            return node->keys[node->count-1];
        return maxKey(node->children[node->count]);
    }

    void merge(NodeBtree<T>* node, int i){ //une dos nodos
        NodeBtree<T>* child=node->children[i];
        NodeBtree<T>* sibling=node->children[i+1];

        child->keys[M/2-1]=node->keys[i];
        for(int j=0;j<sibling->count;j++){
            child->keys[j+M/2]=sibling->keys[j];
        }
        if(!child->leaf){
            for(int j=0;j<=sibling->count;j++){
                child->children[j+M/2]=sibling->children[j];
            }
        }
        for(int j=i;j<node->count-1;j++){
            node->keys[j]=node->keys[j+1];
        }
        for(int j=i+1;j<node->count;j++){
            node->children[j]=node->children[j+1];
        }
        child->count+=sibling->count+1;
        node->count--;
        delete sibling;
    }

    void borrowFromPrev(NodeBtree<T>* node, int i){ //presta de un nodo anterior
        NodeBtree<T>* child=node->children[i];
        NodeBtree<T>* sibling=node->children[i-1];

        for(int j=child->count-1;j>=0;j--){
            child->keys[j+1]=child->keys[j];
        }
        if(!child->leaf){
            for(int j=child->count;j>=0;j--){
                child->children[j+1]=child->children[j];
            }
        }
        child->keys[0]=node->keys[i-1];
        if(!child->leaf){
            child->children[0]=sibling->children[sibling->count];
        }
        node->keys[i-1]=sibling->keys[sibling->count-1];
        child->count++;
        sibling->count--;
    }

    void borrowFromNext(NodeBtree<T>* node, int i){
        NodeBtree<T>* child=node->children[i];
        NodeBtree<T>* sibling=node->children[i+1];
        child->keys[child->count]=node->keys[i];

        if(!child->leaf){
            child->children[child->count+1]=sibling->children[0];
        }
        node->keys[i]=sibling->keys[0];
        for(int j=1;j<sibling->count;j++){
            sibling->keys[j-1]=sibling->keys[j];
        }
        if(!sibling->leaf){
            for(int j=1;j<=sibling->count;j++){
                sibling->children[j-1]=sibling->children[j];
            }
        }
        child->count++;
        sibling->count--;
    }

    void fill(NodeBtree<T>* node, int i){ //llena un nodo
        if(i!=0 && node->children[i-1]->count>=M/2){
            borrowFromPrev(node,i);
        }
        else if(i!=node->count && node->children[i+1]->count>=M/2){
            borrowFromNext(node,i);
        }
        else{
            if(i!=node->count){
                merge(node,i);
            }
            else{
                merge(node,i-1);
            }
        }
    }

    void remove(NodeBtree<T>* node, T key){ //elimina un elemento
        int i=0;
        while(i<node->count && node->keys[i]<key){
            i++;
        }
        if(node->keys[i]==key){
            if(node->leaf){
                for(int j=i;j<node->count-1;j++){
                    node->keys[j]=node->keys[j+1];
                }
                node->count--;
            }
            else{
                if(node->children[i]->count>=M/2){
                    T pred=maxKey(node->children[i]);
                    node->keys[i]=pred;
                    remove(node->children[i],pred);
                }
                else if(node->children[i+1]->count>=M/2){
                    T succ=minKey(node->children[i+1]);
                    node->keys[i]=succ;
                    remove(node->children[i+1],succ);
                }
                else{
                    merge(node,i);
                    remove(node->children[i],key);
                }
            }
        }
        else{
            if(node->leaf)   return;
            
            bool flag=false;
            if(i==node->count){
                flag=true;
            }
            if(node->children[i]->count<M/2){
                fill(node,i);
            }
            if(flag && i>node->count){
                remove(node->children[i-1],key);
            }
            else{
                remove(node->children[i],key);
            }
        }
    }

    void clear(NodeBtree<T>* node){ //eliminar todos lo elementos del arbol
        if(node->leaf){
            delete node;
            return;
        }
        for(int i=0;i<=node->count;i++){
            clear(node->children[i]);
        }
        delete node;
    }

    bool search(NodeBtree<T>* node, T key){
        int i=0;
        while(i<node->count && key>node->keys[i]){
            i++;
        }
        if(i<node->count && key==node->keys[i]){
            return true;
        }
        if(node->leaf){
            return false;
        }
        return search(node->children[i],key);
    }

     int height(NodeBtree<T>* node) {
        if (node == nullptr) {
            return 0; // Árbol vacío
        }

        if (node->leaf) {
            return 1; // Nodo hoja
        }

        int max_child_height = 0;
        for (int i = 0; i <= node->count; i++) {
            int child_height = height(node->children[i]);
            if (child_height > max_child_height) {
                max_child_height = child_height;
            }
        }

        return max_child_height + 1;
    }

    string toString(NodeBtree<T>* node, const string& sep) {
        if (node == nullptr) {
            return "";
        }

        string result;
        if (node->leaf) {
            for (int i = 0; i < node->count; i++) {
                result += to_string(node->keys[i]) + sep;
            }
        } else {
            for (int i = 0; i < node->count; i++) {
                result += toString(node->children[i], sep);
                result += to_string(node->keys[i]) + sep;
            }
            result += toString(node->children[node->count], sep);
        }
        return result;
    }


public:
    BTree(int _M) : root(nullptr), M(_M), n(0) {}

    void insert(T key){
        if(root==nullptr){ 
            root=new NodeBtree<T>(M,true);
            root->keys[0]=key;
            root->count=1;
            n++;
        } else {
            if(root->count==(2*M-1)){
                NodeBtree<T>* newNode=new NodeBtree<T>(M,false);
                newNode->children[0]=root;
                newNode->splitChild(0,root);
                int i=0;
                if(newNode->keys[0]<key){
                        i++;
                }
                newNode->children[i]->insertNonFull(key);
                root=newNode;
                n++;
            }
            else{
                root->insertNonFull(key);
                n++;
            }
        }
    }

    void remove(T key){
        // Planteamos la eliminacion:
        // 1. Si el arbol esta vacio, no se hace nada
        // 2. Si el arbol no esta vacio, buscamos la posicion donde eliminar
        // 3. Si el nodo esta lleno, se debe dividir
        // 4. Si el nodo no esta lleno, se elimina
        if(root==nullptr){ // 1. Si el arbol esta vacio, no se hace nada
            return;
        }
        remove(root,key); // 2. Si el arbol no esta vacio, buscamos la posicion donde eliminar
        n--;
        if(root->count==0){ // 3. Si el nodo esta lleno, se debe dividir
            NodeBtree<T>* temp=root;
            if(root->leaf){
                root=nullptr;
            }
            else{
                root=root->children[0];
            }
            delete temp;
        }
    }

    bool search(T key){
        int i = 0;
        while(i < root->count && key > root->keys[i]) i++;

        if(i < root->count && key == root->keys[i]) 
            return true;
        if(root->leaf) 
            return false;

        return search(root->children[i], key);
    }


    int height(){
        return height(root);
    }

    string toString(const string& sep){
        string result=toString(root,sep);
        result = result.substr(0, result.size()-sep.size());
        return result;
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

    int size(){
        return n;
    }

    ~BTree(){
        delete root;
    }
};

#endif