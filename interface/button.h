#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
protected:
    RectangleShape* rectangle;
    
};

class BasicButton: public Button {

};

class SubmitButton: public Button {

};

#endif // BUTTON_CHAIN_H