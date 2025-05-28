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
        Radar(Vector2 position, Vector2 initPlayerPos, float playerWidth, float playerHeight, Color color, Sound radarPing, vector<Enemy> enemies, float horizontalVariationLeft);
        Radar();
        ~Radar();
        void Draw();
        void Update(Vector2 playerPos, vector<Enemy> enemies);
        void HandleInput(Vector2 playerPos);
        bool EnemyNumInList(vector<EnemyReturn> enemyReturns, int enemyNum);
        Enemy FindEnemy(Missile missile, vector<Enemy> enemyList);
        void ClearMissiles();
        void SetSelectedEnemy(int newSelectedEnemy);
        void AlertMissileLaunch();
        void SetEnemyMissiles(vector<Missile> enemyMissiles);
        Font radarFont;
        vector<Missile> missiles;
        Sound missileLockVWS;
        Music missileLocking;
        Music alertMissileLaunch;

    private:
        int Limiter(int value, int min, int max);
        int selectedEnemy;
        int previousSelectedEnemy;
        Vector2 position;
        Color color;
        Vector2 initPlayerPos;
        vector<Missile> enemyMissiles;
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
        float horizontalVariationLeft;
        float flickeringRWRTimer;
        bool rwrOn;
        bool canFire;
        Color fadedColor;
        Color grey;
        Sound radarPing;
        // Missile oneMissile;
};

const float RWR_TIME = 0.30;