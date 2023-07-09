#include "trie.h" // Agregar esta línea para incluir el archivo de encabezado de Trie

class TrieSimple : public Trie {
private:
    struct TrieNode {
        TrieNode** children; // Puntero a un arreglo de punteros a nodos hijos
        bool endWord; // Indica si es el final de una palabra

        TrieNode() {
            children = new TrieNode*[ALPHA_SIZE_1]; // Crear un arreglo de punteros a nodos hijos
            for (size_t i = 0; i < ALPHA_SIZE_1; i++)
                children[i] = nullptr; // Inicializar todos los punteros a nullptr
            endWord = false; // Inicializar endWord como falso
        }

        ~TrieNode() {
            for (size_t i = 0; i < ALPHA_SIZE_1; i++)
                if (children[i] != nullptr)
                    delete children[i]; // Liberar la memoria de los nodos hijos recursivamente
            delete[] children; // Liberar la memoria del arreglo de punteros a nodos hijos
        }
    };

    TrieNode* root; // Puntero al nodo raíz del trie

    void toString(TrieNode* node, std::string prefix, std::string& result, std::string sep) {
        if (node == nullptr)
            return;
        if (node->endWord)
            result += prefix + sep; // Agregar el prefijo actual al resultado si es el final de una palabra
        for (size_t i = 0; i < ALPHA_SIZE_1; i++) {
            TrieNode* child = node->children[i];
            if (child != nullptr) {
                char c = 'a' + i;
                toString(child, prefix + c, result, sep); // Llamar recursivamente a toString para los nodos hijos
            }
        }
    }

    void traverse(TrieNode* node, string prefix, vector<string>& result) {
        if (node->endWord) {
            result.push_back(prefix);
        }

        for (int i = 0; i < ALPHA_SIZE_1; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i; // Obtener el carácter correspondiente al índice
                traverse(node->children[i], prefix + c, result);
            }
        }
    }
    
    vector<string> words(vector<string>& result, string prefix, TrieNode* node) {
        if (node->endWord) {
            result.push_back(prefix);
        }
        for (int i = 0; i < ALPHA_SIZE_1; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i;
                words(result, prefix + c, node->children[i]);
            }
        }
        return result;
    }

    bool coincide(const std::string& palabra, const std::string& patron) {
        int longitudPalabra = palabra.length();
        int longitudPatron = patron.length();
        if (longitudPalabra < longitudPatron) {
            return false;
        }
        for (int i = 0; i <= longitudPalabra - longitudPatron; i++) {
            if (palabra.substr(i, longitudPatron) == patron) {
                return true;
            }
        }
        return false;
    } 
 

public:
    TrieSimple() : root(new TrieNode()) {} // Constructor que crea un nuevo nodo raíz

    void insert(std::string key) override {
        TrieNode* node = root;
        for (char c : key) {
            if (node->children[c - 'a'] == nullptr)
                node->children[c - 'a'] = new TrieNode(); // Crear un nuevo nodo hijo si no existe
            node = node->children[c - 'a']; // Mover al nodo hijo correspondiente
        }
        node->endWord = true; // Marcar el último nodo como final de palabra
    }

    bool search(std::string key) override {
        TrieNode* node = root;
        for (char c : key) {
            if (node == nullptr)
                return false; // Si el nodo actual es nulo, la palabra no existe en el trie
            node = node->children[c - 'a']; // Mover al nodo hijo correspondiente
        }
        return node != nullptr && node->endWord; // Retornar true si el último nodo es válido y marca el final de una palabra
    }

    vector<string> searchFirst(string prefix) {
        TrieNode* current = root;
        vector<string> result;
        for (char c : prefix) {
            if (current->children[c - 'a'] == nullptr) {
                return result;
            }
            current = current->children[c- 'a'];
        }
        traverse(current, prefix, result);
        return result;
    }

    vector<string> searchContent(const std::string& patron) {
        vector<string> wordsWithContent;
        vector<string> result;
        words(wordsWithContent, "", root);
        for (const auto& word : wordsWithContent) {
            if (coincide(word, patron)) {
                result.push_back(word);
            }
        }
        return result;
    }

    void remove(std::string key) override {
        TrieNode* node = root;
        for (char c : key) {
            if (node == nullptr)
                return; // Si el nodo actual es nulo, la palabra no existe en el trie
            node = node->children[c - 'a']; // Mover al nodo hijo correspondiente
        }
        if (node != nullptr)
            node->endWord = false; // Marcar el último nodo como no final de palabra
    }

    std::string toString(std::string sep) override {
        std::string result = "";
        toString(root, "", result, sep); // Llamar a toString para generar el resultado
        return result;
    }
};
