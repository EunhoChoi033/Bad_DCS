#pragma once
#include <raylib.h>
#include "bullet.hpp"
#include "countermeasures.hpp"
#include "missile.hpp"
#include <cstdlib>
#include <vector>

using namespace std;

class Enemy {
    public:
        Enemy(Vector2 position, int enemyNum, int numEnemies, float horizontalVariationLeft);
        void InitEnemy();
        void Draw();
        void MoveDown();
        void FireCountermeasure();
        void Update();
        void FireBullet(vector<Bullet>& enemyBullets);
        void UnloadImages();
        void DamageEnemy(Sound hitSound, int damageAmount);
        int GetEnemyNum();
        float GetEnemyXPos();
        float GetEnemyYPos();
        void SetPlayerPos(Vector2 playerPos);
        Rectangle GetRect();
        void FireMissileOpportunity();
        bool alive;
        Texture2D image;
        int enemyHealth;
    
        private:
        Countermeasures enemyCountermeasures;
        double countermeasureCooldown;
        Vector2 position;
        Vector2 playerPos;
        vector<Missile> missiles;
        int enemyNum;
        int numEnemies;
        double movementCooldown;
        double fireMissileCooldown;
        int movementDecider;
        double fireCooldown;
        Color planeColor;
        float horizontalVariationLeft;
};

const float ENEMY_COUNTERMEASURE_COOLDOWN_TIME = 0.3f;
const double FIRING_MISSILE_COOLDOWN_TIME = 2.0;
const int FIRING_MISSILE_PROBABILITY_TOTAL = 100;
const int FIRING_MISSILE_PROBABILITY = 20; /* Probability = 0 - 100 */