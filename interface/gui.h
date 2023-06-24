#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "button.h"
#include "block.h"
#include "../blocks/blockchain.h"
#include "../structures/chainHash.h"
using namespace sf;

enum Options {
    closed, initmenu, visualizate, listing
};

// RenderWindow window(VideoMode::getFullscreenModes()[0], "BlockChain05");
RenderWindow window(VideoMode(1920, 1060), "BlockChain05");

static const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

////////
const string VIEW_BLOCKS = "Visualizar BlockChain";
const string LIST_USERS = "Usuarios registrados";
////////

class AppGui {
private:
    std::string title_app = "Our BlockChain05!";
    Options options = Options::initmenu;
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
            VIEW_BLOCKS, window.getSize().x /2, window.getSize().y /2 - 30, Color::Cyan
        );
        buttons->set(VIEW_BLOCKS, viewBlocks);

        // boton de visualizar en tabla los usuarios registrados con fecha y n° de transacciones
        Button* listUsers = new Button(
            LIST_USERS, window.getSize().x/2, window.getSize().y /2 + 40, Color::Cyan
        );
        buttons->set(LIST_USERS, listUsers);

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
        Message* title = new Message(
            title_app, desktop.width /2, 0, 40, Color::Yellow
        );

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    options = Options::closed;
                    return;
                }
            }
            window.clear(sf::Color::Black);

            window.draw(title->getText());
            drawButton(VIEW_BLOCKS);
            drawButton(LIST_USERS);
            window.display();
        }
        delete title;
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
        mainMenu();
        while (options != Options::closed) {
            switch (options) {
                case Options::visualizate:
                    break;
            
                default:
                    break;
            }
        }
        window.close();
    }
};