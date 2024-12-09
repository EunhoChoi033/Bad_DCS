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
    private:
        void DeleteBullets();
        int numEnemies;
        Player player;
        vector<Enemy> enemies;
        vector<Enemy> CreateEnemies(int numEnemies);
};