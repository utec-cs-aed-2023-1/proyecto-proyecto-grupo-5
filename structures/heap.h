#include <iostream>
#include <stdexcept>

using namespace std;

// template <typename T, enum Type>
template <typename T>
class Heap {
public:
    enum Type { MAX_HEAP, MIN_HEAP };

private:
    T *array;
    int capacity;   //capacidad maxima del arbol
    int elements;   //cantidad de elementos en el arbol
    Type type;

public:
    Heap(Type type = MAX_HEAP) = default;

    Heap(T *array, int elem, Type type = MAX_HEAP) : elements(elem), capacity(elem), type(type) {
        buildFromArray(array, elem);
    }

    Heap(int capacity, Type type = MAX_HEAP) : elements(0), capacity(capacity), type(type) {
        this->array = new T[capacity];
    }

    ~Heap(){ 
        delete [] this->array;
    }

    void buildFromArray(T *array, int n){
        for (int i = 0; i < n; i++){
            push(array[i]);
        }  
    }

    int size() {
        return elements;
    }

    bool is_empty() {
        //verificar si el arbol esta vacio
        return (elements == 0);
    }

    void push(T value) {
        if (elements == capacity){
            //Redimensionamos:
            resize(capacity*2);
        }
        array[elements] = value;
        heapify_up(elements);
        elements++;
    }

    void resize(int capacity) {
        if (capacity == this->capacity)   return;

        T *new_arr = new T[capacity];
        for (int i = 0; i < (capacity<this->capacity)? capacity : this->capacity; i++){
            new_arr[i] = array[i];
        }
        delete [] array;
        array = new_arr;
        this->capacity = capacity;
    }

    T pop() {
        // eliminar el primer elemento del arbol
        T aux = array[0];
        array[0] = array[--elements];
        resize(elements);
        heapify_down(0);
        return aux;
    }

    T top() {
        //devuelve el elemento de la raiz
        return array[0];
    }

    T back() {
        return array[elements-1];
    }

    /*vector<T> extractTheTopK(int k){
        //devuelve un vector con los k elementos mas grandes o mas pequeños,
        // dependiendo del tipo de heap
        vector<T> topk;
        if (k > elements){//no se puede extraer mas elementos de los que hay
            throw runtime_error("The heap has less array than k");
        }
        else{
            for (int i = 0; i < k; i++){
                topk.push_back(top());
            }
        }
        return topk;
    }*/

    static void sortAsc(T* arr, int n){
        // Construimos un Max Heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extraemos los elementos uno a uno del heap en orden descendente
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);  // Movemos el elemento máximo al final
            heapify(arr, i, 0);    // Ajustamos el subárbol reducido
        }
    }
    
    //Funcion auxiliar para sortAsc
    static void heapify(T* arr, int n, int i) {
        int largest = i;        // Inicializamos el nodo raíz como el más grande
        int left = 2 * i + 1;   // Índice del hijo izquierdo
        int right = 2 * i + 2;  // Índice del hijo derecho

        // Si el hijo izquierdo es más grande que la raíz
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // Si el hijo derecho es más grande que la raíz
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // Si el mayor no es la raíz, intercambiamos y volvemos a ajustar
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }        

    T* getArray() {
        return array;
    }

    void print(int index = 0) {
        if (index >= elements)
            return;
        
        cout << "( ";
        print(2 * index + 1); cout << " <- ";
        cout << array[index]; cout << " -> ";
        print(2 * index + 2); cout << " ) ";
    }

    static void minheapify(T* arr, int n, int i) {
        int smallest = i;     // Inicializar el índice más pequeño como la raíz
        int left = 2 * i + 1; // Índice del hijo izquierdo
        int right = 2 * i + 2; // Índice del hijo derecho

        // Si el hijo izquierdo es más pequeño que la raíz
        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }

        // Si el hijo derecho es más pequeño que el más pequeño hasta ahora
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }

        // Si el más pequeño no es la raíz, intercambiar y aplicar minheapify al subárbol afectado
        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            minheapify(arr, n, smallest);
        }
    }

    static void sortDesc(T* arr, int n){
        // Construir el min heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            minheapify(arr, n, i);
        }

        // Extraer los elementos del heap en orden ascendente
        for (int i = n - 1; i > 0; i--) {
            // Intercambiar el elemento raíz (mínimo) con el último elemento sin ordenar
            std::swap(arr[0], arr[i]);

            // Aplicar minheapify al subárbol reducido
            minheapify(arr, i, 0);
        }
    }


private:
    int Parent(int i) {
        return (i - 1) / 2;
    }

    int Left(int i) {
        return (2 * i + 1);
    }

    int Right(int i) {
        return (2 * i + 2);
    }

    void heapify_down(int i) {
        if (type == MAX_HEAP){
            if (array[Left(i)] > array[i] && array[Left(i)]>=array[Right(i)] && Left(i) < elements){
                swap(array[Left(i)], array[i]);
                heapify_down(Left(i));
            }
            if (array[Right(i)] > array[i] && array[Right(i)]>=array[Left(i)] && Right(i) < elements){
                swap(array[Right(i)], array[i]);
                heapify_down(Right(i));
            }
        }
        else{
            if (array[Left(i)] < array[i] && array[Left(i)]<=array[Right(i)] && Left(i) < elements){
                swap(array[Left(i)], array[i]);
                heapify_down(Left(i));
            }
            if (array[Right(i)] < array[i] && array[Right(i)]<=array[Left(i)] && Right(i) < elements){
                swap(array[Right(i)], array[i]);
                heapify_down(Right(i));
            }
        }
       //throw ("Function not implemented"); 
    }

    void heapify_up(int i) { 
        if (type == MAX_HEAP){
            if (array[Parent(i)] < array[i] && i > 0){
                swap(array[Parent(i)], array[i]);
                heapify_up(Parent(i));
            }
        }
        else{
            if (array[Parent(i)] > array[i] && i > 0){
                swap(array[Parent(i)], array[i]);
                heapify_up(Parent(i));
            }
        }
    }
};