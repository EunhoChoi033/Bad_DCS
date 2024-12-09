#pragma once
#include <raylib.h>

class Enemy {
    public:
        Enemy(Vector2 position);
        void Draw();
        void MoveDown();
        void Update();
        bool alive;
    private:
    Texture2D image;
    Vector2 position;
    double movementCooldown;
    int movementDecider;
};