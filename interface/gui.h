#include <iostream>
#include <SFML/Graphics.hpp>
#include "message.h"
#include <string>
using namespace sf;

const std::string HOLY_TITLE = "Our BlockChain05!";
const std::string LIST_BLOCK = "Lista de bloques : ";
const unsigned int N = 2;
RenderWindow window(VideoMode(1500, 700), "BlockChain05");

class AppGui {
private:
    std::string title = HOLY_TITLE;
    std::string subtitle = LIST_BLOCK;
    Message* phrases[N] = {
        new Message(HOLY_TITLE, window.getSize().x /2, 60, Color::White),
        new Message(LIST_BLOCK, 12*LIST_BLOCK.size(), 140, Color::Blue)
    };

public:
    AppGui() = default;
    ~AppGui() {
        for (short i=0; i<(int)N; ++i)
            delete phrases[i];
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

            window.clear();
            for (auto& phr: phrases) {
                window.draw(phr->getText());
            }
            window.display();
        }
    }
};