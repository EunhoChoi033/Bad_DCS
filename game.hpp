#pragma once
#include "player.hpp"
#include "enemy.hpp"
#include "radar.hpp"
#include "missile.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Game {
    public:
        Game(int numEnemies, int playerHealth, Color colorMain, float horizontalVariationLeft);
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        int GetNumEnemies();
        bool run;
        int numEnemies;
        Sound gunfire;
        Sound bulletHit;
        Sound radarPing;
        Music missileLocking;
        vector<Enemy> enemies;
        Player player;
        Color colorMain;
        Radar playerRadar;

    private:
        void DeleteStuff();
        void GameOver();
        void CheckCollisions();
        void Reset();
        void InitGame(int numEnemies, int playerHealth, Color colorMain);
        int enemyFireCooldown;
        int playerHealth;
        Vector2 currentPlayerPos;
        float horizontalVariationLeft;
        vector<Enemy> CreateEnemies(int numEnemies);
        vector<Bullet> enemyBullets;
};