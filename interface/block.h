#ifndef BLOCK_GUI_H
#define BLOCK_GUI_H

#include "required.h"
#include "box.h"
#include "../structures/doubleList.h"

using namespace sf;

class SFMLBlock {
    RectangleShape* boxBlock;
    Image userProfile;

public:
    SFMLBlock(const std::string username, string metadataBlock);

    // renderiza la metadada del bloque y la imagen del usuario
    void drawBlock(Button& viewTx_btn, float pos_x, float pos_y) {
        viewTx_btn.draw(window);
    }

    // cambia de color del fondo de bloque
    void changeColor(Color color);

};




#endif // BLOCK_GUI_H