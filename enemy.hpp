#pragma once
#include <raylib.h>
#include "bullet.hpp"
#include "countermeasures.hpp"
#include <vector>

using namespace std;

class Enemy {
    public:
        Enemy(Vector2 position, int enemyNum, int numEnemies);
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
        Rectangle GetRect();
        bool alive;
        Texture2D image;
        int enemyHealth;
    
        private:
        Countermeasures enemyCountermeasures;
        double countermeasureCooldown;
        Vector2 position;
        int enemyNum;
        int numEnemies;
        double movementCooldown;
        int movementDecider;
        double fireCooldown;
        Color planeColor;
};

const float ENEMY_COUNTERMEASURE_COOLDOWN_TIME = 0.3f;