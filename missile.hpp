#pragma once
#include <raylib.h>
#include <cmath>

class Missile {
    public:
        Missile(Vector2 position, float missileSpeed, float missileTurnRate, 
        int id);
        void Draw();
        void Update();
        Rectangle getRect();
        bool active;

    private:
        Texture2D image;
        Vector2 position;
        float missileSpeed;
        float missileTurnRate;
        int id;
};