#pragma once
#include <raylib.h>

class Enemy {
    public:
        Enemy(Vector2 position);
        void Draw();
        void MoveDown();
        bool alive;
    private:
    Texture2D image;
    Vector2 position;
};