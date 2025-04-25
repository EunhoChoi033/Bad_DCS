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
        bool GetActive();
        void SetActive(bool active);
        bool active;
        void NormalizeVector();
        void LoseLockOpportunity();
        float DistanceFromMissile(Vector2 targetPos);
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

const int LOSING_LOCK_PROBABILITY_TOTAL = 100; /* DON'T CHANGE */
const int LOSING_LOCK_PROBABILITY = 80; /* Probability = 0 - 100 */
const int MAX_DISTANCE_AWAY_FROM_TARGET_MISSILE_WILL_LOSE_LOCK = 200;