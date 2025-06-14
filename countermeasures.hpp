#pragma once
#include <raylib.h>
#include <vector>
#include "flare.hpp"
// #include "player.hpp"

using namespace std;

class Countermeasures{
    public:
        Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight);
        Countermeasures();
        void Draw();
        void Update();
        void AddFlare(Vector2 entityPosition);
        // void SetEntityHorizontalCompensation(float horizontalSpeed);
        
        private:
        vector<Flare> countermeasures;
        int numEnemies;
        int id;
        float centerX;
        float entityWidth;
        float entityHeight;
        int flareHealth;
        Color flareColor;
        int coolingCooldown;
        Sound chaffFlareSound;
        // float entityHorizontalCompensation;
};

const int FLARE_HEALTH = 13;
const float FLARE_HORIZONTAL_VELOCITY = 4;
const float FLARE_VERTICAL_VELOCITY = 1;
const float FLARE_VERTICAL_ACCELERATION = 0.2;
const float INIT_VERTICAL_VARIATION = 5;
const float INIT_HORIZONTAL_VARIATION = 5;