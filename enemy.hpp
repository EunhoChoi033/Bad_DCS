#pragma once
#include <raylib.h>
#include "bullet.hpp"
#include <vector>

using namespace std;

class Enemy {
    public:
        Enemy(Vector2 position, int enemyNum);
        void Draw();
        void MoveDown();
        void Update();
        void FireBullet(vector<Bullet>& enemyBullets);
        void UnloadImages();
        void DamageEnemy(Sound hitSound, int damageAmount);
        Rectangle getRect();
        bool alive;
        Texture2D image;
        Vector2 position;
        int enemyNum;
        int enemyHealth;
    private:
        double movementCooldown;
        int movementDecider;
        double fireCooldown;
        Color planeColor;
};