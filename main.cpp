#include <iostream>
#include <raylib.h>
#include <string>
#include "game.hpp"
#include "button.hpp"

using namespace std;

enum GameState {
    TITLE, GAME
};

const char* TITLE_MESSAGE = "Bad DCS";
const int TITLE_MESSAGE_SIZE = 300;
const char* START_BUTTON_MESSAGE = "START";
const int START_BUTTON_MESSAGE_SIZE = 185;

const int LINE_THICKNESS = 3;
const float BOTTOM_BAR_HORIZONTAL_OFFSET = 25.0f;
const float BOTTOM_BAR_VERTICAL_OFFSET = 70.0f;
const float VERTICAL_BAR_HORIZONTAL_OFFSET = 300.0f;
const float VERTICAL_BAR_VERTICAL_OFFSET = 20.0f;

int main () {

    Color grey = {29, 29, 27, 255};
    Color green = {57, 255, 20, 255};
    // int windowWidth = 900;
    int windowWidth = 1500;
    int windowHeight = 900;

    InitWindow(windowWidth, windowHeight, "Bad DCS");
    InitAudioDevice();

    Font regularFont = LoadFontEx("Fonts/PressStart2P-Regular.ttf", 256, 0, 0); 
    Font titleFont = LoadFontEx("Fonts/Quantico-Bold.ttf", 512, 0, 0);
    // Font radarFont = LoadFontEx("Fonts/Oxanium-SemiBold.ttf", 512, 0, 0);
    SetTargetFPS(60);

    GameState currentState = TITLE;

    int numEnemies = 5;
    Game game(numEnemies, 10, green, VERTICAL_BAR_HORIZONTAL_OFFSET);
    Music titleMusic = LoadMusicStream("Sounds/Wild_Blue_Yonder.mp3");
    // Music missileLocking = LoadMusicStream("Sounds/missile_locking.mp3");
    SetMusicVolume(titleMusic, 0.3f);
    PlayMusicStream(titleMusic);

    while(!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(grey);

        switch (currentState) {
            case TITLE: {
                UpdateMusicStream(titleMusic);

                Vector2 offsetTitle = MeasureTextEx(titleFont, TITLE_MESSAGE, 
                TITLE_MESSAGE_SIZE, 1);
                Vector2 offsetStart = MeasureTextEx(titleFont, 
                START_BUTTON_MESSAGE, START_BUTTON_MESSAGE_SIZE, 1);
                float buttonWidth = START_BUTTON_MESSAGE_SIZE * 3;
                float buttonHeight = START_BUTTON_MESSAGE_SIZE * 1.1;
                Vector2 buttonPos = {(windowWidth - buttonWidth) / 2, (windowHeight - buttonHeight) * 2 / 3};
                
                DrawTextEx(titleFont, TITLE_MESSAGE, 
                {(windowWidth - offsetTitle.x) / 2, 
                (windowHeight - offsetTitle.y) / 4}, TITLE_MESSAGE_SIZE, 1, green);
                DrawTextEx(titleFont, START_BUTTON_MESSAGE, 
                {(windowWidth - offsetStart.x) / 2, 
                (windowHeight - offsetStart.y) * 2 / 3}, START_BUTTON_MESSAGE_SIZE, 1, green);
                Button startButton(buttonPos, buttonWidth, buttonHeight, green);
                startButton.Draw();

                if (startButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    currentState = GAME;
                }
                break;
            }
            case GAME: {

                DrawLineEx({BOTTOM_BAR_HORIZONTAL_OFFSET, windowHeight - BOTTOM_BAR_VERTICAL_OFFSET}, {windowWidth - BOTTOM_BAR_HORIZONTAL_OFFSET, windowHeight - BOTTOM_BAR_VERTICAL_OFFSET}, LINE_THICKNESS, green);
                DrawLineEx({VERTICAL_BAR_HORIZONTAL_OFFSET, VERTICAL_BAR_VERTICAL_OFFSET}, {VERTICAL_BAR_HORIZONTAL_OFFSET, windowHeight - BOTTOM_BAR_VERTICAL_OFFSET - LINE_THICKNESS - VERTICAL_BAR_VERTICAL_OFFSET}, LINE_THICKNESS, green);
                if (game.run) {
                    game.HandleInput();
                    game.Update();

                    game.Draw();

                    string playerHealthDisplay = "Health: " + 
                    to_string(game.player.playerHealth) + " / 10";
                    const char* healthMessage = playerHealthDisplay.c_str();
                    Vector2 offsetHealth = MeasureTextEx(regularFont, healthMessage, 16, 1);
                    DrawTextEx(regularFont, healthMessage, {25, windowHeight - 70.0f + (70.0f / 2) - (offsetHealth.y / 2)}, 16, 1, green);

                    string numEnemiesDisplay = "Enemies: " + 
                    to_string(game.enemies.size()) + " / " + to_string(numEnemies);
                    const char* numEnemiesMessage = numEnemiesDisplay.c_str();
                    Vector2 offsetDamage = MeasureTextEx(regularFont, numEnemiesMessage, 16, 1);
                    DrawTextEx(regularFont, numEnemiesMessage, {(windowWidth - offsetDamage.x - 25), windowHeight - 70.0f + 70.0f / 2 - (offsetDamage.y / 2)}, 16, 1, green);
                } else if (game.GetNumEnemies() == 0) {
                    game.Update();
                    game.player.Draw();
                    
                    // for (auto& enemy: game.enemies) {
                    //     enemy.Draw();
                    // }

                    const char* winningMessage = "YOU WON";
                    Vector2 offset = MeasureTextEx(regularFont, winningMessage, 64, 1);
                    DrawTextEx(regularFont, winningMessage, {(windowWidth - offset.x) / 2,
                    (windowWidth - offset.y) / 2}, 64, 1, green);           
                } else {
                    game.Update();
                    game.player.Draw();

                    // for (auto& enemy: game.enemies) {
                    //     enemy.Draw();
                    // }

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
    
    UnloadMusicStream(titleMusic);
    CloseAudioDevice();
    CloseWindow();
}