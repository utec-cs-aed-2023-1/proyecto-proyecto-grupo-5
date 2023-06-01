#ifndef TEXT_GUI_H
#define TEXT_GUI_H

#include <SFML/Graphics.hpp>
#include "../utils/position.h"
#include <iostream>
using namespace sf;

class Message {
    Font font;
    Text sfml_text;
    std::string message;
    Position* position;

public:
    Message() = default;
    Message(std::string text_, float pos_x, float pox_y, sf::Color color) {
        if (!font.loadFromFile("../assets/arial.ttf")) {
            throw "not correctly loaded font: ";
        }
        this->position = new Position(pos_x, pox_y);
        sfml_text.setFont(font);
        sfml_text.setFillColor(color);
        sfml_text.setString(text_);
    }
};


#endif // TEXT_GUI_H