#include "TextureManager.h"

void TextureManager::loadTexture(const char *filePath) {
    texture = LoadTexture(filePath);
}

void TextureManager::unloadTexture() {
    UnloadTexture(texture);
}

Texture2D TextureManager::GetTexture() {
    return texture;
}