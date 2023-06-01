#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

// Clase Padre de algunas implementaciones de listas

template <typename T>
class List {
public:
    // Destructor virtual por defecto, no es necesario implementarlo en las clases hijas.
    virtual ~List() {
    };

    // Contrato de la clase List

    // Devuelve el elemento en el frente de la lista
    virtual T front() = 0;

    // Devuelve el elemento en la parte posterior de la lista
    virtual T back() = 0;

    // Agrega un elemento al frente de la lista
    virtual void push_front(T) = 0;

    // Agrega un elemento a la parte posterior de la lista
    virtual void push_back(T) = 0;

    // Elimina y devuelve el elemento en el frente de la lista
    virtual T pop_front() = 0;

    // Elimina y devuelve el elemento en la parte posterior de la lista
    virtual T pop_back() = 0;

    // Inserta un elemento en una posición específica de la lista
    virtual void insert(T, int) = 0;

    // Elimina un elemento de la lista en una posición específica
    virtual void remove(int) = 0;

    // Sobrecarga del operador de indexación para acceder a los elementos de la lista por índice
    virtual T& operator[](int) = 0;

    // Verifica si la lista está vacía
    virtual bool is_empty() = 0;

    // Devuelve el tamaño actual de la lista
    virtual int size() = 0;

    // Elimina todos los elementos de la lista
    virtual void clear() = 0;

    virtual bool search(T) = 0;

    // Ordena los elementos de la lista
    virtual void sort() = 0;

    // Verifica si los elementos de la lista están ordenados
    // virtual bool is_sorted() = 0;

    // Invierte el orden de los elementos en la lista
    // virtual void reverse() = 0;

    // Devuelve el nombre de la implementación concreta de la lista
    virtual std::string name() = 0;
};
#endif