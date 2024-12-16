#pragma once
#include <raylib.h>
#include "bullet.hpp"
#include <vector>

using namespace std;

class Player{
    public:
        Player();
        ~Player();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireBullet(Sound gunfire);
        void damagePlayer(Sound bulletHit);
        void InitPlayer();
        Rectangle getRect();
        vector<Bullet> bullets;
        Color planeColor;
        int playerHealth;
        Texture2D image;
    private:
        Vector2 position;
        double fireCooldown;
};