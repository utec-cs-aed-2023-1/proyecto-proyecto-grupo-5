// por consola

// #include "blocks/blockchain.h"

// int main() {
//     BlockChain* blockchain = new BlockChain("assets/data", "data.txt");
//     blockchain->init_blockchain();
//     delete blockchain;
// }

// por SFML

#include <iostream>
#include "interface/gui.h"

using namespace std;

int main() {
    AppGui* gui = new AppGui;
    gui->init_visualize_app();
    delete gui;
}
