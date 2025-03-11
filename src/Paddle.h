#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

class Paddle {
protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    virtual void Update();
};

#endif