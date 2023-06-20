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

    void pop_char() {
        this->message.pop_back();
        sfml_text.setString(message);
    }

    void push_char(const char ch) {
        this->message += ch; 
        sfml_text.setString(message);
    }

    bool is_empty() { return message.empty(); }

    Text getText() { return sfml_text; }

    Color getColor() { return sfml_text.getFillColor(); }

    void setPosition(float pos_x, float pos_y) {
        sfml_text.setPosition(pos_x, pos_y);
    } 
};


#endif // TEXT_GUI_H