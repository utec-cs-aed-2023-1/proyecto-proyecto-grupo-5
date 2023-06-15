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
    Position position;
    
public:
    Message() = default;
    Message(std::string text_, float pos_x, float pos_y, sf::Color color) {
        if (!font.loadFromFile("assets/arial.ttf")) {
            throw "not correctly loaded font: ";
        }
        position.movePos(pos_x, pos_y);
        sfml_text.setFont(font);
        sfml_text.setFillColor(color);
        sfml_text.setString(text_);
        sfml_text.setCharacterSize(40);
        sfml_text.setStyle(Text::Bold);
        sfml_text.setPosition(pos_x - sfml_text.getLocalBounds().width / 2,
                              pos_y - sfml_text.getLocalBounds().height / 2);
    }

    void moveMessage() {
        return;
    }

    void changeColor(sf::Color color) {
        sfml_text.setFillColor(color);
    }

    sf::Text getText() {
        return sfml_text;
    }
};


#endif // TEXT_GUI_H