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
        void DamagePlayer(Sound hitSound, int damageAmount);
        void InitPlayer();
        // float getPlayerWidth();
        float getPlayerHeight();
        Rectangle getRect();
        vector<Bullet> bullets;
        int playerHealth;
        Texture2D image;
        Vector2 position;

    private:
        Color planeColor;
        double fireCooldown;
};