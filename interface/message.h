#ifndef TEXT_GUI_H
#define TEXT_GUI_H

#include <SFML/Graphics.hpp>
#include "position.h"
#include <iostream>
using namespace sf;

class Message {
    Font font;
    Text sfml_text;
    std::string message;

public:
    Message() = default;
    Message(std::string text_, int textSize,  sf::Color color = Color::White): message(text_) {
        if (!font.loadFromFile("assets/arial.ttf")) {
            throw "not correctly loaded font: ";
        }
        sfml_text.setFont(font);
        sfml_text.setFillColor(color);
        sfml_text.setString(text_);
        sfml_text.setCharacterSize(textSize);
        sfml_text.setStyle(Text::Bold);
    }

    void setMessage(std::string message) {
        this->message = message;
        sfml_text.setString(message);
    }

    void changeColor(sf::Color color) {
        sfml_text.setFillColor(color);
    }

    Text getText() { return sfml_text; }

    Color getColor() { return sfml_text.getFillColor(); }
};


#endif // TEXT_GUI_H