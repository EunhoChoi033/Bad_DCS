#pragma once
#include <raylib.h>
#include <vector>
#include "flare.hpp"
// #include "player.hpp"

using namespace std;

class Countermeasures{
    public:
        Countermeasures();
        Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight);
        void Draw();
        void Update();
        void AddFlare(Vector2 entityPosition);
        // bool getActive();
        
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
        // bool active;
};

// const float HORIZONTAL_VARIATION = 20;
const float INIT_VARIATION = 50;