#include <iostream>
//#include "doubleList.h"
#include "heap.h"
// #include "chainHash.h"

using namespace std;

/*int main() {
    ChainHash<string, int> hashTable;

    // Insertar pares clave-valor
    hashTable.set("Alice", 25);
    hashTable.set("Bob", 30);
    hashTable.set("Charlie", 35);
    hashTable.set("David", 40);

    // Recuperar valores
    cout << "Alice: " << hashTable.get("Alice") << endl;
    cout << "Bob: " << hashTable.get("Bob") << endl;
    cout << "Charlie: " << hashTable.get("Charlie") << endl;
    cout << "David: " << hashTable.get("David") << endl;

    // Modificar valores
    hashTable["Alice"] = 26;
    cout << "Alice: " << hashTable.get("Alice") << endl; // Debería imprimir 26

    // Eliminar una entrada
    hashTable.remove("David");

    // Intentar recuperar un valor después de eliminarlo debe lanzar una excepción
    try {
        cout << "David: " << hashTable.get("David") << endl;
    } catch(const std::out_of_range& e) {
        cout << e.what() << endl; // Debería imprimir "La clave no existe en la tabla hash"
    }

    // Mostrar el tamaño de las cubetas
    for(int i = 0; i < hashTable.bucket_count(); i++) {
        cout << "Bucket " << i << " size: " << hashTable.bucket_size(i) << endl;
    }

    return 0;
}*/


// Test Heap
int main() {
    // Crear un objeto Heap con el arreglo
    Heap<int> heap(6, Heap<int>::MAX_HEAP);

    // Insertar un nuevo elemento en el Heap
    heap.push(7);
    heap.push(5);
    heap.push(1);
    heap.push(9);
    heap.push(34);
    heap.push(12);
    
    heap.print();


    // Imprimir el tamaño del Heap
    std::cout << "\nTamaño del Heap: " << heap.size() << std::endl;

    // Imprimir el elemento superior del Heap
    std::cout << "Elemento superior del Heap: " << heap.top() << std::endl;

    std::cout << std::endl;
    return 0;
}


/*
// Test para doublelist

int main() {
    DoubleList<int> myList;

    // Agregar elementos a la lista
    myList.push_back(10);
    myList.push_front(5);
    myList.push_back(20);
    myList.push_front(2);

    // Imprimir los elementos de la lista
    std::cout << "Lista: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Eliminar un elemento de la lista
    myList.remove(2);

    // Insertar un elemento en una posición específica
    myList.insert(15, 1);

    // Imprimir los elementos de la lista después de las modificaciones
    std::cout << "Lista modificada: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Realizar operaciones adicionales
    std::cout << "Front: " << myList.front() << std::endl;
    std::cout << "Back: " << myList.back() << std::endl;
    std::cout << "Tamanio: " << myList.size() << std::endl;
    std::cout << "¿Esta vacia? " << (myList.is_empty() ? "Sí" : "No") << std::endl;

    // Ordenar la lista
    myList.sort();

    // Imprimir los elementos de la lista ordenada
    std::cout << "Lista ordenada: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Invertir la lista
    myList.reverse();

    // Imprimir los elementos de la lista invertida
    std::cout << "Lista invertida: ";
    for (int i = 0; i < myList.size(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
*/