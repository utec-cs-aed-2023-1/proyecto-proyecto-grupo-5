#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include <SFML/Graphics.hpp>

#include "message.h"

using namespace sf;
using namespace std;

const int FORM_TEXT_SIZE = 10;
const int FEAT_BUTTON_SIZE = 25;
const int BUTTON_SIZE = 20;

class BoxMessage {
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
    ~BoxMessage() {
        delete message;
        delete rectangle;
    }

    BoxMessage(string text, float pos_x, float pos_y, int textSize, Color lineColor, Color colorText = Color::White): 
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
        position.setPosition(pos_x - rectangle->getSize().x/2,
                             pos_y + rectangle->getSize().y/2);
        rectangle->setPosition(position.x, position.y);
        message->centering(position.x, position.y, rectangle->getSize());
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*rectangle);
        window.draw(message->getText());
    }

    Text getMessage() { return message->getText(); }
};


class Input: public BoxMessage {
public:
    Input(string text, float pos_x, float pos_y): 
        BoxMessage(text, pos_x, pos_y, FORM_TEXT_SIZE, Color::White) {}

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


class Button: public BoxMessage {
public:
    Button(string text, float pos_x, float pos_y, sf::Color linecolor, int textSize = BUTTON_SIZE): 
        BoxMessage(text, pos_x, pos_y, textSize, linecolor) {}

    void onMouseEvent() {
        sf::Color temp = rectangle->getFillColor();
        rectangle->setFillColor(message->getText().getFillColor());
        message->changeColor(temp);
    }

    bool on_click(RenderWindow& window, Event& event) {
        // Activa cuando se hizo clic en el botón
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            if (rectangle->getGlobalBounds().contains(mousePosition))
                return true;
        }
        return false;
    }
};

#endif // BUTTON_GUI_H