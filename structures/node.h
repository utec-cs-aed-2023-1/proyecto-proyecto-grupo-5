#ifndef NODE_H
#define NODE_H

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
        // Elimina el nodo de la lista

        prev->next = next;  // El siguiente del nodo anterior apunta al siguiente del nodo actual
        next->prev = prev;  // El anterior del siguiente nodo apunta al nodo anterior
        next = nullptr;     // Establece el siguiente del nodo actual como nullptr
        prev = nullptr;     // Establece el anterior del nodo actual como nullptr
    }
};

#endif
