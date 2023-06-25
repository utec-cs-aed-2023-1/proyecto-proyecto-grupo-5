#ifndef TEXT_GUI_H
#define TEXT_GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Message {
    Font font;
    Text sfml_text;
    std::string message;

public:
    Message() = default;
    Message(std::string text_, float pos_x, float pos_y, int ChrSize, sf::Color color): message(text_) {
        if (!font.loadFromFile("assets/arial.ttf")) {
            throw "not correctly loaded font: ";
        }
        sfml_text.setFont(font);
        sfml_text.setFillColor(color);
        sfml_text.setString(text_);
        sfml_text.setCharacterSize(ChrSize);
        sfml_text.setStyle(Text::Bold);
        std::cout << "pos message " << pos_x << " " << pos_y << std::endl;
        sfml_text.setPosition(pos_x - sfml_text.getLocalBounds().width/2, 
                              pos_y + sfml_text.getLocalBounds().height/2);
    }

    void setMessage(std::string message) {
        this->message = message;
        sfml_text.setString(message);
    }

    void changeColor(sf::Color color) {
        sfml_text.setFillColor(color);
    }

    void centering(float pos_x, float pos_y, Vector2f dimensions) {
        sf::FloatRect textBounds = sfml_text.getLocalBounds();
        sfml_text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        sfml_text.setPosition(pos_x + dimensions.x / 2, pos_y + dimensions.y / 2);
        std::cout << "pos message center " << sfml_text.getPosition().x << " " << sfml_text.getPosition().y << std::endl;
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

    void setPosition(float pos_x, float pos_y) {
        sfml_text.setPosition(pos_x, pos_y);
    } 
};


#endif // TEXT_GUI_H