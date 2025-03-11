#ifndef BALL_H
#define BALL_H

#include <raylib.h>

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int cpuScore = 0, playerScore = 0;
    int radius;

    void Draw();
    void Update();
    void ResetBall();
};

#endif