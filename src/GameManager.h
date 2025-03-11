#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <raylib.h>
#include <iostream>

enum Page {
    LOGO,
    WELCOME,
    GAME,
    TIME_OVER,
    LOSS,
    WIN
};

class GameManager {
public:
    Page currentPage;
    int playerScore;
    int cpuScore;
    float elapsedTime;
    float startTime;
    float gameDuration;
    bool isRunning;

    GameManager();
    void StartGame();
    void UpdateGameState();
};

#endif