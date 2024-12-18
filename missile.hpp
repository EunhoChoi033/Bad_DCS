#pragma once
#include <raylib.h>
#include <cmath>

class Missile {
    public:
        Missile(Vector2 position, float speed, int id);
        Missile();
        void Draw();
        void Update(Vector2 targetPos, float targetWidth, float targetHeight);
        Rectangle getRect();
        int getId();
        bool active;
        // bool forward;

    private:
        void normalizeVector();
        Texture2D image;
        Vector2 position;
        Vector2 targetPos;
        Vector2 direction;
        float speed;
        int id;
};