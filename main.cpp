#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include "enemy.hpp"

using namespace std;

int main () {

    Color grey = {29, 29, 27, 255};
    int windowWidth = 750;
    int windowHeight = 750;

    InitWindow(windowWidth, windowHeight, "Bad DCS");
    SetTargetFPS(60);

   Game game;
   Enemy enemy = Enemy({100, 100});

    while(!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(grey);

        game.HandleInput();
        game.Update();

        game.Draw();
        enemy.Draw();
        
        EndDrawing();
    }

    CloseWindow();
}