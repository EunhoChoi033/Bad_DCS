#pragma once
#include <raylib.h>
#include <vector>
// #include "player.hpp"

class Flare{
    public:
    Flare(Vector2 position, Color initColor, int initHealth);
    void Draw();
    void Update();
    void SetPosition(Vector2 newPosition);
    int getHealth();

    private:
    Vector2 position;
    Color color;
    int health;
};