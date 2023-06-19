#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include <SFML/Graphics.hpp>
#include "position.h"
#include "message.h"

using namespace sf;
using namespace std;


class InstanceFrame {
protected:
    Position position;
    Message* message;
    RectangleShape* rectangle;

public:

    InstanceFrame(string text, float pos_x, float pos_y, int textSize): position(pos_x, pos_y), message(new Message(text, textSize)) {
        rectangle->setSize(Vector2f(textSize*text.size(), textSize));
    }

    void moveFrame(int pos_x, int pos_y) {
        position.movePos(pos_x, pos_y);
        rectangle->setPosition(pos_x - rectangle->getSize().x / 2,
                              pos_y - rectangle->getSize().y / 2);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*rectangle);
        window.draw(message->getText());
    }

    Text getMessage() { return message->getText(); }
};


class Input: public InstanceFrame {
public:
    Input(string text, float pos_x, float pos_y, int TextSize = 30): InstanceFrame(text, pos_x, pos_y, TextSize) {}
};


class Button: public InstanceFrame {
public:
    Button(string text, float pos_x, float pos_y, int TextSize = 30): InstanceFrame(text, pos_x, pos_y, TextSize) {}

    void onMouseEvent() {
        sf::Color temp = rectangle->getFillColor();
        rectangle->setFillColor(message->getColor());
        message->changeColor(temp);
    }
};


class FeatureButton: public Button {
public:
};

#endif // BUTTON_CHAIN_H