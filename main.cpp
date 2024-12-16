#include <iostream>
#include <raylib.h>
#include <string>
#include "game.hpp"
#include "button.hpp"

using namespace std;

enum GameState {
    TITLE, GAME
};

int main () {

    Color grey = {29, 29, 27, 255};
    Color green = {57, 255, 20, 255};
    int windowWidth = 750;
    int windowHeight = 750;

    InitWindow(windowWidth, windowHeight, "Bad DCS");
    InitAudioDevice();

    Font regularFont = LoadFontEx("Fonts/PressStart2P-Regular.ttf", 256, 0, 0); 
    Font titleFont = LoadFontEx("Fonts/Quantico-Bold.ttf", 512, 0, 0);
    SetTargetFPS(60);

    GameState currentState = TITLE;

    int numEnemies = 5;
    Game game(numEnemies, 10);
    Music titleMusic = LoadMusicStream("Sounds/Wild_Blue_Yonder.mp3");
    PlayMusicStream(titleMusic);

    while(!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(grey);

        switch (currentState) {
            case TITLE: {
                UpdateMusicStream(titleMusic);
                const char* titleMessage = "Bad DCS";
                const char* startButtonMessage = "START";
                Vector2 offsetStart = MeasureTextEx(titleFont, 
                startButtonMessage, 128, 1);
                Vector2 offsetTitle = MeasureTextEx(titleFont, titleMessage, 
                212, 1);
                float buttonWidth = 400;
                float buttonHeight = 150;
                Vector2 buttonPos = {(windowWidth - buttonWidth) / 2, (windowWidth - buttonHeight) * 2 / 3};
                
                DrawTextEx(titleFont, titleMessage, 
                {(windowWidth - offsetTitle.x) / 2, 
                (windowHeight - offsetTitle.y) / 3}, 212, 1, green);
                DrawTextEx(titleFont, startButtonMessage, 
                {(windowWidth - offsetStart.x) / 2, 
                (windowHeight - offsetStart.y) * 2 / 3}, 128, 1, green);
                Button startButton(buttonPos, buttonWidth, buttonHeight, green);
                startButton.Draw();

                if (startButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    UnloadMusicStream(titleMusic);
                    currentState = GAME;
                }
                break;
            }
            case GAME: {
                game.HandleInput();
                game.Update();

                game.Draw();

                DrawLineEx({25, 680}, {725, 680}, 3, green);
                if (game.run) {
                    string playerHealthDisplay = "Health: " + 
                    to_string(game.player.playerHealth) + " / 10";
                    const char* healthMessage = playerHealthDisplay.c_str();
                    DrawTextEx(regularFont, healthMessage, {25, 710}, 16, 1, green);

                    string numEnemiesDisplay = "Enemies: " + 
                    to_string(game.enemies.size()) + " / " + to_string(numEnemies);
                    const char* numEnemiesMessage = numEnemiesDisplay.c_str();
                    Vector2 offset = MeasureTextEx(regularFont, numEnemiesMessage, 16, 1);
                    DrawTextEx(regularFont, numEnemiesMessage, {(windowWidth - offset.x - 25), 
                    (windowHeight - 680.f) / 2 + 680 - (offset.y / 2)}, 16, 1, green);
                } else if (game.enemies.size() == 0) {
                    const char* winningMessage = "YOU WON";
                    Vector2 offset = MeasureTextEx(regularFont, winningMessage, 64, 1);
                    DrawTextEx(regularFont, winningMessage, {(windowWidth - offset.x) / 2,
                    (windowWidth - offset.y) / 2}, 64, 1, green);           
                } else {
                    const char* losingMessage = "GAME OVER";
                    Vector2 offset = MeasureTextEx(regularFont, losingMessage, 64, 1);
                    DrawTextEx(regularFont, losingMessage, {(windowWidth - offset.x) / 2,
                    (windowHeight - offset.y) / 2}, 64, 1, green);
                }
                break;
            }
        }
        EndDrawing();
    }
    
    CloseAudioDevice();
    CloseWindow();
}