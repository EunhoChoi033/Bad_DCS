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
        float ToDegrees(float radians);
        Rectangle GetRect();
        int GetId();
        bool active;
        void NormalizeVector();
        void LoseLockOpportunity();
        // bool forward;

    private:
        Texture2D image;
        Vector2 position;
        Vector2 targetPos;
        Vector2 direction;
        float speed;
        float rotation;
        int id;
        bool tracking;
};

const int LOSING_LOCK_PROBABILITY_TOTAL = 100;
const int LOSING_LOCK_PROBABILITY = 90; /* Probability = 0 - 100 */