#ifndef PATRICIATRIE_H
#define PATRICIATRIE_H

#include <iostream>
#include <list>
#include <map>
#include "trie.h"

using namespace std;

//const unsigned ALPHA_SIZE_1 = 26;//tamanio del alfabeto: letras minusculas

class TriePatricia : public Trie{
private:
    struct TrieNode{
        // Opciones para almacenar los hijos del nodo
        // opcion 1:   TrieNode **children;
        // opcion 2:   list<pair<char, TrieNode*>> children;
        // opcion 3:   map<pair<char, TrieNode*>> children;
        TrieNode **children; // Puntero a un arreglo de punteros TrieNode
        string prefix; // Prefijo almacenado en el nodo
        bool endWord; // Indica si es el final de una palabra

        TrieNode(){
            children = new TrieNode*[ALPHA_SIZE_1]; // Se crea un nuevo arreglo de punteros TrieNode
            for(size_t i = 0; i < ALPHA_SIZE_1; i++)
                children[i] = nullptr; // Inicializa todos los punteros a nullptr
            endWord = false; // Inicializa endWord como falso
        }

        TrieNode(string prefix, bool endWord = false): prefix(prefix), endWord(endWord){
            children = new TrieNode*[ALPHA_SIZE_1]; // Se crea un nuevo arreglo de punteros TrieNode
            for(size_t i = 0; i < ALPHA_SIZE_1; i++)
                children[i] = nullptr; // Inicializa todos los punteros a nullptr
        }

        ~TrieNode(){
            for(size_t i = 0; i < ALPHA_SIZE_1; i++)
                if(children[i] != nullptr)
                    delete children[i]; // Libera la memoria de los nodos hijos recursivamente
            delete[] children; // Libera la memoria del arreglo de punteros
        }
    };
    TrieNode* root; // Puntero al nodo raíz del Trie Patricia


    // Función auxiliar para convertir el Trie Patricia en una cadena de texto
    void toString(TrieNode* node, string prefix, string& result, const string& sep) {
        if (node == nullptr)
            return;

        if (node->endWord)
            result += prefix + sep; // Se agrega el prefijo al resultado si es el final de una palabra

        for (size_t i = 0; i < ALPHA_SIZE_1; i++) {
            if (node->children[i] != nullptr) {
                toString(node->children[i], prefix + node->children[i]->prefix, result, sep); // Recursivamente se llama a toString para los hijos
            }
        }
    }


    // Función auxiliar para insertar una clave en el Trie Patricia
    void insert(TrieNode *&node, const string &key) {
        if (node == nullptr) {
            node = new TrieNode(key, true); // Se crea un nuevo nodo con la clave y se marca como final de palabra
            return;
        }

        string prefix = node->prefix;
        if (key == prefix) {
            node->endWord = true; // Si la clave ya existe, se marca como final de palabra
            return;
        }

        size_t minLength = min(key.length(), prefix.length());
        size_t j = 0;
        while (j < minLength && key[j] == prefix[j])
            j++;

        if (j == key.length()) {
            TrieNode *copy = node;
            node = new TrieNode(key); // Se crea un nuevo nodo con la clave
            node->children[prefix[j] - 'a'] = copy;
            copy->prefix = copy->prefix.substr(j); // Se ajusta el prefijo del nodo copiado
            node->endWord = true; // Se marca el nuevo nodo como final de palabra
            return;
        }
        if (j == prefix.length()) {
            insert(node->children[key[j] - 'a'], key.substr(j)); // Se inserta la clave restante en el nodo hijo correspondiente
            return;
        }

        string::iterator prefixIterator = prefix.begin();
        TrieNode *copy = node;
        node = new TrieNode(string(prefixIterator, prefixIterator + j), false); // Se crea un nuevo nodo con el prefijo en común
        node->children[prefix[j] - 'a'] = copy;
        copy->prefix = copy->prefix.substr(j); // Se ajusta el prefijo del nodo copiado
        insert(node->children[key[j] - 'a'], key.substr(j)); // Se inserta la clave restante en el nodo hijo correspondiente
    }

    // Función auxiliar para buscar una clave en el Trie Patricia
    bool search(const TrieNode* node, const string& key) {
        if (node == nullptr)
            return false;

        string prefix = node->prefix;
        if (key == prefix)
            return node->endWord; // Si la clave coincide con el prefijo, se verifica si es el final de una palabra

        size_t minLength = min(key.length(), prefix.length());
        size_t j = 0;
        while (j < minLength && key[j] == prefix[j])
            j++;

        if (j == key.length()) {
            TrieNode* child = node->children[prefix[j] - 'a'];
            return (child != nullptr) && (child->endWord); // Se verifica si el nodo hijo es válido y si es el final de una palabra
        }

        if (j == prefix.length()) {
            TrieNode* child = node->children[key[j] - 'a'];
            return search(child, string(key, j)); // Se busca la clave restante en el nodo hijo correspondiente
        }

        return false;
    }

    // Función auxiliar para eliminar una clave del Trie Patricia
    void remove(TrieNode*& node, const string& key) {
        if (node == nullptr)
            return;

        string prefix = node->prefix;
        if (key == prefix) {
            if (!node->endWord)
                return;
            node->endWord = false; // Si la clave coincide con el prefijo y no es final de palabra, se marca como no final de palabra
            return;
        }

        size_t minLength = min(key.length(), prefix.length());
        size_t j = 0;
        while (j < minLength && key[j] == prefix[j])
            j++;

        if (j == prefix.length()) {
            TrieNode*& child = node->children[key[j] - 'a'];
            remove(child, string(key, j)); // Se elimina la clave restante en el nodo hijo correspondiente
            if (child == nullptr)
                node->children[key[j] - 'a'] = nullptr; // Si el nodo hijo se vuelve nulo, se actualiza el puntero en el arreglo de hijos
            return;
        }
        return;
    }

public:
    TriePatricia(): root(new TrieNode()) {}

    void insert(string key) override{
        insert(root, key); // Llama a la función auxiliar insert para insertar la clave en el Trie Patricia
    }

    bool search(string key)override{
        return search(root, key); // Llama a la función auxiliar search para buscar la clave en el Trie Patricia
    }

    void remove(string key)override{
        remove(root, key); // Llama a la función auxiliar remove para eliminar la clave del Trie Patricia
    }

    //imprime ordenado
    string toString(string sep)override{
        string result;
        string prefix = "";
        toString(root, prefix, result, sep); // Llama a la función auxiliar toString para convertir el Trie Patricia en una cadena de texto
        return result;
    }

};

#endif  // PATRICIATRIE_H
