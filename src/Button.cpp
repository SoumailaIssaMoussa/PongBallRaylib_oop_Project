#include "Button.h"

Button::Button(const char *imagePath, Vector2 pos, float s) {
    texture = LoadTexture(imagePath);
    position = pos;
    scale = s;
}

Button::~Button() {
    UnloadTexture(texture);
}

void Button::Draw() {
    DrawTextureEx(texture, position, 0.0f, scale, MAROON);
}

void Button::draw() {
    DrawTextureEx(texture, position, 0.0f, scale, WHITE);
}

bool Button::isPressed(Vector2 mousePosition, bool mousePressed) {
    Rectangle buttonRect = { position.x, position.y, texture.width * scale, texture.height * scale };
    return CheckCollisionPointRec(mousePosition, buttonRect) && mousePressed;
}