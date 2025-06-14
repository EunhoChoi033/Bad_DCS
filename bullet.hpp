#pragma once
#include <raylib.h>

class Bullet {
    public:
        Bullet(Vector2 position, int speed, int id);
        void Update();
        void Draw();
        Rectangle GetRect();
        bool active;
    private:
        // Texture2D image;
        Vector2 position;
        int speed;
        int id;
};