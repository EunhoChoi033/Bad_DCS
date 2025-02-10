#pragma once
#include <raylib.h>
#include <vector>
#include "player.hpp"

using namespace std;

class Flares{
    public:
        Flares(Vector2 position, int id, int numEnemies, float entityWidth, float entityHeight);
        void Draw();
        void Update();
        // bool getActive();
        const float INIT_VARIATION = 50;
        const float SIDEWAYS_VARIATION = 20;
        
        private:
        Vector2 initPosition;
        vector<Vector2> positions;
        int numEnemies;
        int id;
        float centerX;
        // bool active;
};