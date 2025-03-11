#include "Paddle.h"

void Paddle::LimitMovement() {
    if (y <= 0) {
        y = 0;
    }
    if (y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;
    }
}

void Paddle::Draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, BLACK);
}

void Paddle::Update() {
    if (IsKeyDown(KEY_UP)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        y += speed;
    }
    LimitMovement();
}