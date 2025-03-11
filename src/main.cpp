#include <iostream>
#include "GameManager.h"
#include "Button.h"
#include "Ball.h"
#include "Paddle.h"
#include "CpuPaddle.h"
#include "PlayerPaddle.h"
#include "AudioManager.h"
#include "TextureManager.h"

using namespace std;

int main() {
    cout << "Starting game!" << endl;

    const int screen_width = 1200;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(65);

    // Enable window resizing
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Load textures
    TextureManager textureManager;
    textureManager.loadTexture("picture/logo.png");
    Texture2D logoTexture = textureManager.GetTexture();
    textureManager.loadTexture("picture/2.png");
    Texture2D background = textureManager.GetTexture();

    // Initialize buttons with image paths, positions, and scales
    Button startButton("picture/play_game.png", {520, 500}, 0.2f);
    Button exitButton("picture/QUIT.png", {880, 280}, 0.2f);
    Button replayButton("picture/replay.png", {100, 300}, 0.2f);
    Button over("picture/over.png", {380, 180}, 0.2f);
    Button congratulation("picture/smiley.png", {400, 250}, 0.5f);

    // Initialize ball properties
    Ball ball;
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    // Initialize player paddle properties
    PlayerPaddle player;
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 10;

    // Initialize CPU paddle properties
    CpuPaddle cpu;
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    GameManager gameManager;
    Page Current_Page = LOGO; // Start with the logo page

    // Start timer at the beginning
    gameManager.startTime = GetTime();

    AudioManager audioManager;
    InitAudioDevice();
    audioManager.LoadMusic("music/aya1.mp3");
    audioManager.PlayMusic();

    // Main game loop
    while (!WindowShouldClose()) {
        audioManager.UpdateMusicStream();

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Update elapsed time
        if (gameManager.isRunning) {
            gameManager.elapsedTime = GetTime() - gameManager.startTime;
        }

        // Handle different game pages
        switch (Current_Page) {
            case LOGO:
                BeginDrawing();
                ClearBackground(WHITE);
                
                // Draw the logo texture centered
                DrawTexture(logoTexture, screen_width / 2 - logoTexture.width / 2, screen_height / 2 - logoTexture.height / 2, WHITE);
                
                // Switch to welcome page after 3 seconds
                if (gameManager.elapsedTime >= 5.0f) {
                    Current_Page = WELCOME;
                    gameManager.startTime = GetTime(); // Reset timer for the next page
                }
                EndDrawing();
                break;

            case WELCOME:
                BeginDrawing();
                ClearBackground(BLACK);
                DrawTexture(background, screen_width / 2 - background.width / 2, screen_height / 2 - background.height / 2, RED);

                // Draw buttons
                startButton.Draw();

                // Check for button clicks
                if (startButton.isPressed(mousePosition, mousePressed)) {
                    Current_Page = GAME;
                    gameManager.startTime = GetTime(); // Start the game timer
                }
                
                EndDrawing();
                break;

            case GAME:
                BeginDrawing();
                ball.Update();
                player.Update();
                cpu.Update(ball.y);

                // Check collisions between the ball and paddles
                if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
                    ball.speed_x *= -1;
                }
                if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
                    ball.speed_x *= -1;
                }

                // Draw game elements
                ClearBackground(RED);
                DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, MAROON);
                DrawCircle(screen_width / 2, screen_height / 2, 150, { 139, 0, 0, 255 });
                DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, { 139, 0, 0, 255 });
                ball.Draw();
                cpu.Draw();
                player.Draw();
                DrawText(TextFormat("%i", gameManager.cpuScore), screen_width / 4 - 20, 20, 80, { 100, 0, 0, 255 });
                DrawText(TextFormat("%i", gameManager.playerScore), 3 * screen_width / 4 - 20, 20, 80, { 100, 0, 0, 255 });

                // Draw remaining time
                DrawText(TextFormat("Time: %.0f", gameManager.gameDuration - gameManager.elapsedTime), screen_width / 2 - 100, 20, 60, { 100, 0, 0, 255 });

                EndDrawing();

                // Check for game over or win conditions
                if (gameManager.elapsedTime >= gameManager.gameDuration) {
                    if (gameManager.cpuScore < gameManager.playerScore)
                        Current_Page = WIN;
                    if (gameManager.cpuScore >= gameManager.playerScore)
                        Current_Page = LOSS;
                    if (gameManager.cpuScore == gameManager.playerScore)
                        Current_Page = TIME_OVER;
                }
                break;

            case TIME_OVER:
                BeginDrawing();
                ClearBackground(BLACK);
                exitButton.Draw();
                replayButton.Draw();
                DrawRectangleRounded(Rectangle{10, 10, 220, 80}, 0.3, 0, { 230, 41, 55, 40 });
                DrawText(TextFormat("SCORE_CPU : %d", gameManager.cpuScore), 20, 20, 20, MAROON);
                DrawText(TextFormat("SCORE_PLAYER : %d", gameManager.playerScore), 20, 50, 20, MAROON);
                DrawText("COMPUTER_AI", 900, 700, 30, MAROON);
                DrawText("TIME IS FINISH ...!\n\nGAME TIED\n\nDO YOU WANT TO REPLAY?", 460, 50, 30, MAROON);
                if (exitButton.isPressed(mousePosition, mousePressed)) {
                    CloseWindow();
                    return 0;
                }
                EndDrawing();

                // Reset game and return to game page on replay button press
                if (replayButton.isPressed(mousePosition, mousePressed)) {
                    Current_Page = GAME;
                    gameManager.playerScore = 0;
                    gameManager.cpuScore = 0;
                    ball.ResetBall();
                    gameManager.startTime = GetTime(); // Reset timer
                }
                break;

            case LOSS:
                BeginDrawing();
                ClearBackground(BLACK);
                exitButton.Draw();
                replayButton.Draw();
                over.draw();
                DrawRectangleRounded(Rectangle{10, 10, 220, 80}, 0.3, 0, { 230, 41, 55, 40 });
                DrawText(TextFormat("SCORE_CPU : %d", gameManager.cpuScore), 20, 20, 20, MAROON);
                DrawText(TextFormat("SCORE_PLAYER : %d", gameManager.playerScore), 20, 50, 20, MAROON);
                DrawText("COMPUTER_AI", 900, 700, 30, MAROON);
                DrawText("TIME IS FINISH ...!\n\n\nGAME OVER", 460, 30, 50, MAROON);
                if (exitButton.isPressed(mousePosition, mousePressed)) {
                    CloseWindow();
                    return 0;
                }
                EndDrawing();

                // Reset game and return to game page on replay button press
                if (replayButton.isPressed(mousePosition, mousePressed)) {
                    Current_Page = GAME;
                    gameManager.playerScore = 0;
                    gameManager.cpuScore = 0;
                    ball.ResetBall();
                    gameManager.startTime = GetTime(); // Reset timer
                }
                break;

            case WIN:
                BeginDrawing();
                ClearBackground(BLACK);
                exitButton.Draw();
                replayButton.Draw();
                congratulation.draw();
                DrawRectangleRounded(Rectangle{10, 10, 220, 80}, 0.3, 0, { 230, 41, 55, 40 });
                DrawText(TextFormat("SCORE_CPU : %d", gameManager.cpuScore), 20, 20, 20, MAROON);
                DrawText(TextFormat("SCORE_PLAYER : %d", gameManager.playerScore), 20, 50, 20, MAROON);
                DrawText("COMPUTER_AI", 900, 700, 30, MAROON);
                DrawText("TIME IS FINISH ...!\n\n\nCONGRATULATIONS", 400, 50, 50, GREEN);
                if (exitButton.isPressed(mousePosition, mousePressed)) {
                    CloseWindow();
                    return 0;
                }
                EndDrawing();

                // Reset game and return to game page on replay button press
                if (replayButton.isPressed(mousePosition, mousePressed)) {
                    Current_Page = GAME;
                    gameManager.playerScore = 0;
                    gameManager.cpuScore = 0;
                    ball.ResetBall();
                    gameManager.startTime = GetTime(); // Reset timer
                }
                break;
        }
    }

    // Unload resources and close the windows
    audioManager.UnloadMusic();
    CloseAudioDevice();

    textureManager.unloadTexture();
    CloseWindow();

    return 0;
}