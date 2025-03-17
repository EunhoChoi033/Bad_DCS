#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
// #include "player.hpp"

using namespace std;

class Flare{
    public:
    Flare(int centerX, float entityWidth, float entityHeight, float entityYPosition, Color initColor, int initHealth, float healthMultiplier, float horizontalVelocity, float verticalVelocity, float verticalAcceleration, float xInitVariation, float yInitVariation);
    void Draw();
    void Update();
    int GetNumPositionsRight();
    int GetNumPositionsLeft();

    private:
    Vector2 currentPositionRight;
    Vector2 currentPositionLeft;
    int centerX;
    float entityWidth;
    float entityHeight;
    vector<Vector2> positionsLeft;
    vector<Vector2> positionsRight;
    Color color;
    int health;
    float xVelocity;
    float yVelocity;
    float yAcceleration;
    float healthMultiplier;
    float xInitVariation;
    float yInitVariation;
    float entityYPosition;
};

const int FLARE_SIZE = 10;