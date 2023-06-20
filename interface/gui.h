#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "button.h"
#include "block.h"
#include "../blocks/blockchain.h"
#include "../structures/chainHash.h"
using namespace sf;

// RenderWindow window(VideoMode::getFullscreenModes()[0], "BlockChain05");
RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "BlockChain05");

static const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

////////
const string VIEW_BLOCKS = "Visualizar BlockChain";
////////

class AppGui {
private:
    std::string title = "Our BlockChain05!";
    // BlockChain* blockchain;
    ChainHash<string, Button*>* buttons = new ChainHash<string, Button*>;

public:
    AppGui()  {
        // blockchain = new BlockChain; 
        window.setFramerateLimit(60);
        window.setPosition(Vector2<int>(desktop.width / 2 - window.getSize().x / 2, 
                                        desktop.height / 2 - window.getSize().y / 2 - 20));
        
        // boton de visualizar los bloques
        Button* viewBlocks = new Button(
            VIEW_BLOCKS, window.getSize().x / 2, window.getSize().y / 3 + 20, Color::White
        );
        buttons->set(VIEW_BLOCKS, viewBlocks);

        //


        //


        //
    };
    ~AppGui() {
        // InstanceBox* mainTitle = new InstanceBox(title, )
        // for (short i=0; i<(int)N; ++i)
        //     delete phrases[i];
        delete buttons;
    }

private:
    void mainMenu() {
        drawButton(VIEW_BLOCKS);
    }

    void drawButton(const string button) {
        buttons->get(button)->draw(window);
    }

    void loadFileBlockChain(const string file) {

    }

    void insertFile() {

    }

    void set_username() {
        return;
    }


public:  // para realizar testing sin acceso al backend de la app

    void init_visualize_app() {
        // Clock clock;

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Black);
            mainMenu();
            window.display();
        }
    }
};