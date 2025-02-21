#pragma once
#include <raylib.h>
#include <vector>
// #include "player.hpp"

class Flare{
    public:
    Flare(Vector2 position, Color initColor, int initHealth, float healthMultiplier, float horizontalVariation, float verticalVariation, float verticalAcceleration, float entityHorizontalCompensation);
    void Draw();
    void Update();
    void SetPosition(Vector2 newPosition);
    int GetHealth();

    private:
    Vector2 position;
    Color color;
    int health;
    float xVelocity;
    float yVelocity;
    float yAcceleration;
    float entityHorizontalCompensation;
    float healthMultiplier;
};