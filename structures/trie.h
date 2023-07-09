#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <vector>

class Trie {
private:
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        bool isEndOfWord;
    };

    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clear(root);
    }

    void insert(const std::string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return curr->isEndOfWord;
    }

    std::vector<std::string> inicia_con(const std::string& prefix) {
        std::vector<std::string> result;
        TrieNode* curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end()) {
                return result;
            }
            curr = curr->children[c];
        }
        recolecta_palabras(curr, prefix, result);
        return result;
    }

    std::vector<std::string> esta_contenido_en(const std::string& content) {
        std::vector<std::string> result;
        std::string palabraactual = "";
        words(result, palabraactual, root);
        std::vector<std::string> matches;
        for (const auto& palabra : result) {
            if (coincide(palabra, content)) {
                matches.push_back(palabra);
            }
        }
        return matches;
    }

private:
    void clear(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (auto& pair : node->children) {
            clear(pair.second);
        }
        delete node;
    }

    void recolecta_palabras(TrieNode* node, const std::string& prefix, std::vector<std::string>& result) {
        if (node->isEndOfWord) {
            result.push_back(prefix);
        }
        for (auto& pair : node->children) {
            recolecta_palabras(pair.second, prefix + pair.first, result);
        }
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

    void words(std::vector<std::string>& result, std::string prefix, TrieNode* node) {
        if (node->isEndOfWord) {
            result.push_back(prefix);
        }
        for (const auto& pair : node->children) {
            char c = pair.first;
            words(result, prefix + c, pair.second);
        }
    }
};

#endif  // TRIE_H
