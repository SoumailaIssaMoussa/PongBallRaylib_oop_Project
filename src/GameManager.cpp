#include "GameManager.h"

GameManager::GameManager() {
    currentPage = LOGO;
    playerScore = 0;
    cpuScore = 0;
    elapsedTime = 0.0f;
    startTime = 0.0f;
    gameDuration = 60.0f;
    isRunning = true;
}

void GameManager::StartGame() {
    // Initialization logic
}

void GameManager::UpdateGameState() {
    // Update game state logic
}