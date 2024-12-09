#pragma once
#include "player.hpp"
#include "enemy.hpp"
#include <iostream>

using namespace std;

class Game {
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        vector<Enemy> CreateEnemies(vector<Enemy> enemies);
    private:
        void DeleteBullets();
        Player player;
        vector<Enemy> enemies;
};