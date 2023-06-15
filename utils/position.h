#ifndef POSITION_H
#define POSITION_H

struct Position {
    float x = 0, y = 0;
    void movePos(int x, int y) { 
        this->x = y;    this->y = y;
    }
};


#endif // POSITION_H