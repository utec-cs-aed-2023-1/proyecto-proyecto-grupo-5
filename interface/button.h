#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include <SFML/Graphics.hpp>

#include "position.h"
#include "message.h"

using namespace sf;
using namespace std;

const int FORM_TEXT_SIZE = 10;
const int FEAT_BUTTON_SIZE = 25;
const int BUTTON_SIZE = 20;

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
    {
        rectangle->setFillColor(sf::Color(0, 0, 0, 128));
        rectangle->setPosition(pos_x, pos_y);
        message->setPosition(pos_x, pos_y);
    }

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
    Input(string text, float pos_x, float pos_y): 
        InstanceBox(text, pos_x, pos_y, FORM_TEXT_SIZE)
    {
        rectangle->setSize(Vector2f(FORM_TEXT_SIZE*text.size(), FORM_TEXT_SIZE + 10));
        rectangle->setOutlineThickness(3.f);
        rectangle->setOutlineColor(sf::Color::White);
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
    Button(string text, float pos_x, float pos_y, sf::Color linecolor, 
           sf::Color bgcolor = Color(0, 0, 0, 128), int textSize = BUTTON_SIZE
    ): InstanceBox(text, pos_x, pos_y, textSize) 
    {
        rectangle->setSize(Vector2f(textSize*text.size(), textSize + textSize*2/3));
        rectangle->setFillColor(bgcolor);
        rectangle->setOutlineThickness(3.f);
        rectangle->setOutlineColor(linecolor);
        centerMessage(pos_x, pos_y);
    }

    void onMouseEvent() {
        sf::Color temp = rectangle->getFillColor();
        rectangle->setFillColor(message->getColor());
        message->changeColor(temp);
    }

    void centerMessage(float pos_x, float pos_y) {
        // obtengo el tamaño de la palabra renderizada
        float textWidth = message->getText().getGlobalBounds().width;
        // actualizo la posición del redtangulo para que el message se ve centrado
        rectangle->setPosition(
            rectangle->getPosition().x - textWidth / 2,                               // resta el tamaño del caracter de la palabra / 2
            rectangle->getPosition().y - message->getText().getCharacterSize() / 2    // resta el tamaño de palabra / 2
        );
    }
};


class FeatureButton: public Button {
public:
    FeatureButton(string text, float pos_x, float pos_y, 
                  sf::Color linecolor, sf::Color bgcolor
    ): Button(text, pos_x, pos_y, linecolor, bgcolor, FEAT_BUTTON_SIZE)
    {
        rectangle->setSize(Vector2f(FEAT_BUTTON_SIZE*text.size() + 20, FEAT_BUTTON_SIZE + FEAT_BUTTON_SIZE*5/6));
        centerMessage(pos_x, pos_y);
    }
};

#endif // BUTTON_GUI_H