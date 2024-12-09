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
        void FireBullet();
        vector<Bullet> bullets;
    private:
        Texture2D image;
        Vector2 position;
        double fireCooldown;
};