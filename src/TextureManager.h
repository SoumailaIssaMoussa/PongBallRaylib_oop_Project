#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <raylib.h>

class TextureManager {
public:
void loadTexture(const char *filePath);
void unloadTexture();
Texture2D GetTexture();

private:
     Texture texture;
};

#endif