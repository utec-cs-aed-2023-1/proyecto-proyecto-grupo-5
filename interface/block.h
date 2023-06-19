#ifndef BLOCK_GUI_H
#define BLOCK_GUI_H

#include <SFML/Graphics.hpp>
#include "../structures/doubleList.h"
#include "button.h"

using namespace sf;

class SFMLBlock {
    RectangleShape* boxBlock;
    Image userProfile;

public:
    SFMLBlock(const std::string username, string metadataBlock);

    // renderiza la metadada del bloque y la imagen del usuario
    void viewBlock(RenderWindow& window, float pos_x, float pos_y);

    // cambia de color del fondo de bloque
    void changeColor(Color color);

};




#endif // BLOCK_GUI_H