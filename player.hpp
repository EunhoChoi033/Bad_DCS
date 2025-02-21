#pragma once
#include <raylib.h>
#include <vector>
#include "bullet.hpp"
#include "countermeasures.hpp"
#include <iostream>

using namespace std;

class Player{
    public:
        Player();
        ~Player();
        void Draw();
        void Update();
        void MoveLeft();
        void MoveRight();
        void FireBullet(Sound gunfire);
        void DamagePlayer(Sound hitSound, int damageAmount);
        void InitPlayer();
        void SetNumEnemies(int numEnemies);
        void HandleInput();
        // float getPlayerWidth();
        // float getPlayerHeight();
        Rectangle GetRect();
        vector<Bullet> bullets;
        int playerHealth;
        Texture2D image;
        Vector2 position;

    private:
        Color planeColor;
        Countermeasures playerCountermeasures;
        double fireCooldown;
        double countermeasureCooldown;
        int numEnemies;
};

const float HORIZONTAL_MOVEMENT_MAGNITUDE = 5;