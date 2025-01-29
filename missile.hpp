#pragma once
#include <raylib.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

class Missile {
    public:
        Missile(Vector2 position, float speed, int id);
        Missile();
        void Draw();
        void Update(Vector2 targetPos, float targetWidth, float targetHeight);
        float toDegrees(float radians);
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
        float rotation;
        int id;
};