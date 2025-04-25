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
        void InitPlayer(float horizontalVariationLeft);
        void SetNumEnemies(int numEnemies);
        void HandleInput();
        void SetCountermeasureFired(bool countermeasureFired);
        bool GetCountermeasureFired();
        Vector2 GetPlayerPos();
        Rectangle GetRect();
        int GetPlayerHealth();
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
        float horizontalVariationLeft;
        bool countermeasureFired;
};

const float HORIZONTAL_MOVEMENT_MAGNITUDE = 5;
const float PLAYER_COUNTERMEASURE_COOLDOWN_TIME = 0.3f;