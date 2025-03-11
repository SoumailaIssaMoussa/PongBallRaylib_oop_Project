#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

class Button {
public:
    Texture2D texture;
    Vector2 position;
    float scale;

    Button(const char *imagePath, Vector2 pos, float s);
    ~Button();
    void Draw();
    void draw();
    bool isPressed(Vector2 mousePosition, bool mousePressed);
};

#endif