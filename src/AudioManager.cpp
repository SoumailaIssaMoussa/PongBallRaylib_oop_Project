#include "AudioManager.h"

void AudioManager::LoadMusic(const char *filePath) {
    music = LoadMusicStream(filePath);
}

void AudioManager::PlayMusic() {
    PlayMusicStream(music);
}

void AudioManager::UpdateMusicStream() {
    //UpdateMusicStream(music);
}

void AudioManager::UnloadMusic() {
    UnloadMusicStream(music);
}