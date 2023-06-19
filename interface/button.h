#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include <SFML/Graphics.hpp>
#include "position.h"
#include "message.h"

using namespace sf;
using namespace std;


class InstanceBox {
protected:
    Position position;
    Message* message;
    RectangleShape* rectangle;

public:
    ~InstanceBox() {
        delete message;
        delete rectangle;
    }

    InstanceBox(string text, float pos_x, float pos_y, int textSize): 
        position(pos_x, pos_y), 
        message(new Message(text, textSize)),
        rectangle(new RectangleShape(Vector2f(textSize*text.size(), textSize)))
    {}

    void moveFrame(int pos_x, int pos_y) {
        position.movePos(pos_x, pos_y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*rectangle);
        window.draw(message->getText());
    }

    void updateMessage(string newtext) {
        message->setMessage(newtext);
    }

    Text getMessage() { return message->getText(); }
};


class Input: public InstanceBox {
public:
    Input(string text, float pos_x, float pos_y, int TextSize = 30): InstanceBox(text, pos_x, pos_y, TextSize) {
        rectangle->setSize(Vector2f(TextSize*text.size() + 15, TextSize + 15));
        rectangle->setFillColor(Color::White);
        rectangle->setOutlineThickness(2.f);
        rectangle->setOutlineColor(sf::Color::Black);
    }

    void updateInput(sf::RenderWindow& window, Event event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                if (event.text.unicode == '\b' && !message->is_empty()) {
                    message->pop_char();
                }
                else if (event.text.unicode != '\b') {
                    message->push_char(static_cast<char>(event.text.unicode));
                }

                rectangle->setSize(sf::Vector2f(message->getText().getLocalBounds().width + 10, 30));
            }
            window.clear(sf::Color::White);
            draw(window);
        }
    }
};


class Button: public InstanceBox {
public:
    Button(string text, float pos_x, float pos_y, sf::Color color, int TextSize = 30): InstanceBox(text, pos_x, pos_y, TextSize) {
        rectangle->setSize(Vector2f(TextSize*text.size() + 20, TextSize + 20));
        rectangle->setFillColor(color);
        centerMessage(pos_x, pos_y);
    }

    void onMouseEvent() {
        sf::Color temp = rectangle->getFillColor();
        rectangle->setFillColor(message->getColor());
        message->changeColor(temp);
    }

    void centerMessage(float pos_x, float pos_y) {
        float textWidth = message->getText().getGlobalBounds().width;
        rectangle->setPosition(
            message->getText().getPosition().x - textWidth / 2,
            message->getText().getPosition().y - message->getText().getCharacterSize() / 2
        );
    }
};


class FeatureButton: public Button {
public:
    FeatureButton(string text, float pos_x, float pos_y, sf::Color color, int TextSize = 30): Button(text, pos_x, pos_y, color, TextSize + 5) {
        rectangle->setSize(Vector2f(TextSize*text.size() + 20, TextSize + 20));
        centerMessage(pos_x, pos_y);
    }
};

#endif // BUTTON_GUI_H