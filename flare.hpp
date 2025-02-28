#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
// #include "player.hpp"

using namespace std;

class Flare{
    public:
    Flare::Flare(/* Vector2 initPosition */int centerX, float entityWidth, float entityHeight, Color initColor, int initHealth, float healthMultiplier, float horizontalVariation, float verticalVariation, float verticalAcceleration, float entityHorizontalCompensation);
    void Draw();
    void Update();
    int GetNumPositions();

    private:
    // Vector2 currentPosition;
    int centerX;
    float entityWidth;
    float entityHeight;
    vector<Vector2> positions;
    Color color;
    int health;
    float xVelocity;
    float yVelocity;
    float yAcceleration;
    float entityHorizontalCompensation;
    float healthMultiplier;
    // bool run;
};

const int FLARE_SIZE = 10;