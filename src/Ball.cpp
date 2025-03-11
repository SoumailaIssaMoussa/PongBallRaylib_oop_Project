#include "Ball.h"

void Ball::Draw() {
    DrawCircle(x, y, radius, WHITE);
}

void Ball::Update() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth()) {
        cpuScore++;
        ResetBall();
    }
    if (x - radius <= 0) {
        playerScore++;
        ResetBall();
    }
}

void Ball::ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};
    speed_x = 7 * speed_choices[GetRandomValue(0, 1)];
    speed_y = 7 * speed_choices[GetRandomValue(0, 1)];
}