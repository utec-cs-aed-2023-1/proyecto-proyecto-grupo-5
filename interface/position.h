#ifndef POSITION_H
#define POSITION_H

const unsigned int SIZE_X = 1920;
const unsigned int SIZE_Y = 1060;

struct Position {
    float x = 0, y = 0;

    Position() = default;
    Position(int x, int y):  x(x), y(y) {}
    
    void movePos(int x, int y) { 
        this->x = y;    this->y = y;
    }

    void go_simetric_x() {}
    void go_simetric_y() {}

    void go_center() {}
};


#endif // POSITION_H