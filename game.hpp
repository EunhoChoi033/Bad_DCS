#pragma once
#include "player.hpp"
#include "enemy.hpp"
#include "radar.hpp"
#include <iostream>

using namespace std;

class Game {
    public:
        Game(int numEnemies, int playerHealth);
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int numEnemies;
        Sound gunfire;
        Sound bulletHit;
        vector<Enemy> enemies;
        Player player;

    private:
        void DeleteBullets();
        void GameOver();
        void CheckCollisions();
        void Reset();
        void InitGame(int numEnemies, int playerHealth);
        int enemyFireCooldown;
        int playerHealth;
        Radar playerRadar;
        Color playerColor;
        vector<Enemy> CreateEnemies(int numEnemies);
        vector<Bullet> enemyBullets;
};