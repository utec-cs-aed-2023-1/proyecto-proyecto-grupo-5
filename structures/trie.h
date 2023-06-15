#ifndef TRIE_H
#define TRIE_H

#include <string>

using namespace std;

#define ALPHA_SIZE_1 26
class Trie
{
public:
    virtual void insert(string key) = 0;
    virtual bool search(string key) = 0;
    virtual void remove(string key) = 0;        
    
    //imprime ordenado
    virtual string toString(string sep=",") = 0;
};

#endif  // TRIE_H
