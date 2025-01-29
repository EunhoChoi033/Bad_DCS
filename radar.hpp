#pragma once
#include <raylib.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include "enemy.hpp"
#include "player.hpp"
#include "missile.hpp"
#include "enemyReturn.hpp"

using namespace std;

class Radar {
    public:
        Radar(Vector2 position, Vector2 initPlayerPos, float playerWidth, float playerHeight, Color color, Sound radarPing, vector<Enemy> enemies);
        Radar();
        ~Radar();
        void Draw();
        void Update(Vector2 playerPos, vector<Enemy> enemies);
        void HandleInput(Vector2 playerPos);
        bool enemyNumInList(vector<EnemyReturn> enemyReturns, int enemyNum);
        Enemy findEnemy(Missile missile, vector<Enemy> enemyList);
        void clearMissiles();
        void setSelectedEnemy(int newSelectedEnemy);
        Font radarFont;
        vector<Missile> missiles;
        Sound missileLockVWS;
        Music missileLocking;

    private:
        int limiter(int value, int min, int max);
        int selectedEnemy;
        int previousSelectedEnemy;
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
        float missileLockedCooldown;
        bool canFire;
        Color fadedColor;
        Color grey;
        Sound radarPing;
        // Missile oneMissile;
};