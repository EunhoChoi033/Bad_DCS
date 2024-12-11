#pragma once
#include "player.hpp"
#include "enemy.hpp"
#include <iostream>

using namespace std;

class Game {
    public:
        Game(int numEnemies);
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;

    private:
        void DeleteBullets();
        void GameOver();
        void CheckCollisions();
        void Reset();
        void InitGame();
        int numEnemies;
        int enemyFireCooldown;
        int playerHealth;
        Player player;
        Color playerColor;
        vector<Enemy> enemies;
        vector<Enemy> CreateEnemies(int numEnemies);
        vector<Bullet> enemyBullets;
};