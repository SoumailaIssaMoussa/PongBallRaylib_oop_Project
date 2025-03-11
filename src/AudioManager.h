#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <raylib.h>

class AudioManager {
public:
    void LoadMusic(const char *filePath);
    void PlayMusic();
    void UpdateMusicStream();
    void UnloadMusic();

private:
    Music music;
};

#endif