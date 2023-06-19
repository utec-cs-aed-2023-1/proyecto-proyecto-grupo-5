#include <iostream>
#include <SFML/Graphics.hpp>
#include "message.h"
#include <string>
using namespace sf;

const unsigned int N = 2;
RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "BlockChain05");

class AppGui {
private:
    std::string title = "Our BlockChain05!";
    std::string subtitle = LIST_BLOCK;
    Message* phrases[N] = {
        new Message("Our BlockChain05!", SIZE_X/2, 60, Color::White),
        new Message("Lista de bloques : ", 12*LIST_BLOCK.size(), 140, Color::Blue)
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