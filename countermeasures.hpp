#pragma once
#include <raylib.h>
#include <vector>
#include "flare.hpp"
// #include "player.hpp"

using namespace std;

class Countermeasures{
    public:
        Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight);
        void Draw();
        void Update();
        void setNumEnemies(int newNumEnemies);
        void AddFlares(Vector2 entityPosition);
        // bool getActive();
        const float INIT_VARIATION = 50;
        const float HORIZONTAL_VARIATION = 20;
        
        private:
        Vector2 initPosition;
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