#pragma once
#include <raylib.h>
#include <vector>
#include "enemy.hpp"
#include "enemyReturn.hpp"

class Radar {
    public:
        Radar(Vector2 position, Color color);
        Radar();
        // ~Radar();
        void Draw();
        void Update(Vector2 playerPos, vector<Enemy> enemies);
        Font radarFont;

    private:
        int limiter(int value, int min, int max);
        Vector2 position;
        Color color;
        Vector2 playerPos;
        vector<Enemy> enemies;
        EnemyReturn oneReturn;
        vector<EnemyReturn> enemyReturns;
        float radarRangeX;
        float radarRangeY;
        float outerRadius;
        float innerRadius;
        float thickness;
        Color fadedColor;
        Color grey;
};