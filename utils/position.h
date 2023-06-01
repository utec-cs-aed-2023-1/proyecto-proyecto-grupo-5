#ifndef POSITION_H
#define POSITION_H

struct Position {
    float x = 0, y = 0;
    Position() = default;
    Position(float x_, float y_): x(x_), y(y_) {}
};


#endif // POSITION_H