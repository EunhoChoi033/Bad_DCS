#include <iostream>
#include <raylib.h>
#include "aircraft.hpp"

using namespace std;

int main () {

    Color grey = {29, 29, 27, 255};
    int windowWidth = 750;
    int windowHeight = 750;

    InitWindow(windowWidth, windowHeight, "Game Window C++");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(grey);
        
        EndDrawing();
    }

    CloseWindow();
}