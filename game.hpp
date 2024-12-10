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
        void CheckCollisions();
    private:
        void DeleteBullets();
        int numEnemies;
        int enemyFireCooldown;
        Player player;
        vector<Enemy> enemies;
        vector<Enemy> CreateEnemies(int numEnemies);
        vector<Bullet> enemyBullets;
};