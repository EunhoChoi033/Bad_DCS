#pragma once
#include <raylib.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "enemy.hpp"
#include "player.hpp"
#include "missile.hpp"
#include "enemyReturn.hpp"

class Radar {
    public:
        Radar(Vector2 position, Vector2 initPlayerPos, float playerWidth, float playerHeight, Color color, Sound radarPing);
        Radar();
        ~Radar();
        void Draw();
        void Update(Vector2 playerPos, vector<Enemy> enemies);
        bool enemyNumInList(vector<EnemyReturn> enemyReturns, int enemyNum);
        int findEnemyIndex(Vector<Enemy> enemies);
        void clearMissiles();
        Font radarFont;
        vector<Missile> missiles;
        Sound missileLockVWS;
        Music missileLocking;

    private:
        int limiter(int value, int min, int max);
        int selectedEnemy;
        Vector2 position;
        Color color;
        Vector2 initPlayerPos;
        vector<Enemy> enemies;
        vector<EnemyReturn> enemyReturns;
        Texture2D planeImage;
        float radarRangeX;
        float radarRangeY;
        float outerRadius;
        float innerRadius;
        float thickness;
        float playerWidth;
        float playerHeight;
        float radarUpdateCooldown;
        float radarReturnSelectCooldown;
        float missileLockMessageCooldown;
        Color fadedColor;
        Color grey;
        Sound radarPing;
        // Missile oneMissile;
};