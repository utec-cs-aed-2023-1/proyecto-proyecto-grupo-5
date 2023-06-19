#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "../blocks/blockchain.h"
#include <string>
using namespace sf;

const unsigned int N = 2;
RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "BlockChain05");

class AppGui {
private:
    std::string title = "Our BlockChain05!";
    BlockChain* blcokchain;

public:
    AppGui()  {
        blcokchain = new BlockChain; 
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.setPosition(Vector2<int>(desktop.width / 2 - window.getSize().x / 2, 
                                        desktop.height / 2 - window.getSize().y / 2));
    };
    ~AppGui() {
        // for (short i=0; i<(int)N; ++i)
        //     delete phrases[i];
    }

    void insertFile() {

    }

    void set_username() {
        return;
    }

    void init_visualize_app() {
        Clock clock;

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            InstanceBox* m1 = new InstanceBox("Hola", 30, 30, 30);
            m1->draw(window);
            window.display();
        }
    }
};