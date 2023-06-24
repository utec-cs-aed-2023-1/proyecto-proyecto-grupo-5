#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include <SFML/Graphics.hpp>

#include "message.h"

using namespace sf;
using namespace std;

const int FORM_TEXT_SIZE = 10;
const int FEAT_BUTTON_SIZE = 25;
const int BUTTON_SIZE = 20;

class InstanceBox {
protected:
    struct Position {
        float x, y;
        void setPosition(float x, float y) {
            this->x = x;   this->y = y;
        }
    } position;
    Message* message;
    RectangleShape* rectangle;

public:
    ~InstanceBox() {
        delete message;
        delete rectangle;
    }

    InstanceBox(string text, float pos_x, float pos_y, int textSize, Color lineColor, Color colorText = Color::White): 
        message(new Message(text, pos_x, pos_y, textSize, colorText)),
        rectangle(new RectangleShape(
            Vector2f(textSize*text.size()* 2/3, textSize + textSize*2/3)
        ))
    {
        rectangle->setFillColor(sf::Color(0, 0, 0, 128));
        rectangle->setSize(Vector2f(textSize*text.size(), textSize + textSize*2/3));       
        rectangle->setOutlineThickness(2.f);
        rectangle->setOutlineColor(lineColor);
        moveFrame(pos_x, pos_y);
    }

    void moveFrame(float pos_x, float pos_y) {
        position.setPosition(pos_x + rectangle->getSize().x,
                             pos_y - rectangle->getSize().y);
        rectangle->setPosition(position.x, position.y);
        message->centering(position.x, position.y, rectangle->getSize());
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*rectangle);
        window.draw(message->getText());
    }

    Text getMessage() { return message->getText(); }

    void onMouseEvent() {
        sf::Color temp = rectangle->getFillColor();
        rectangle->setFillColor(message->getText().getFillColor());
        message->changeColor(temp);
    }

    void centerMessage() {
        // obtengo el tamaño de la palabra renderizada
        message->setPosition(position.x + rectangle->getSize().x / 2,
                         position.y + rectangle->getSize().y / 2);
    }
};


class Input: public InstanceBox {
public:
    Input(string text, float pos_x, float pos_y): 
        InstanceBox(text, pos_x, pos_y, FORM_TEXT_SIZE, Color::White) {}

    void updateMessage(string newtext) {
        message->setMessage(newtext);
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

                rectangle->setSize(sf::Vector2f(message->getText().getLocalBounds().width + 10, FORM_TEXT_SIZE + 30));
            }
            window.clear(sf::Color::Black);
            draw(window);
        }
    }
};


class Button: public InstanceBox {
public:
    Button(string text, float pos_x, float pos_y, sf::Color linecolor, int textSize = BUTTON_SIZE): 
        InstanceBox(text, pos_x, pos_y, textSize, linecolor) {}
};

#endif // BUTTON_GUI_H