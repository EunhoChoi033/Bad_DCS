#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
// #include "player.hpp"

using namespace std;

class Flare{
    public:
    Flare(int centerX, float entityWidth, float entityHeight, float entityYPosition, Color initColor, int initHealth, float healthMultiplier, float horizontalVelocity, float verticalVelocity, float verticalAcceleration, float initVariation);
    void Draw();
    void Update();
    int GetNumPositions();

    private:
    Vector2 currentPosition;
    // Vector2 currentPositionRight;
    // Vector2 currentPositionLeft;
    int centerX;
    float entityWidth;
    float entityHeight;
    vector<Vector2> positions;
    Color color;
    int health;
    float xVelocity;
    float yVelocity;
    float yAcceleration;
    float healthMultiplier;
    float initVariation;
    float entityYPosition;
    // bool run;
};

const int FLARE_SIZE = 10;