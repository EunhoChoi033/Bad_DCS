#include "game.hpp"
#include <vector>
#include <cstdlib>

using namespace std;

Game::Game(int numEnemies) { 
    this -> numEnemies = numEnemies;
    enemies = CreateEnemies(numEnemies);
}

Game::~Game() {

}

/*
Automatically updating if the bullets are active or not and deleting those which
are not active
*/
void Game::Update() {
    for (auto& bullet: player.bullets) {
        bullet.Update();
    }

    for (auto& enemy: enemies) {
        for (auto& bullet: enemy.bullets) {
            bullet.Update();
        }
    }

    for (auto& enemy: enemies) {
        enemy.MoveDown();
        enemy.Update();
        enemy.FireBullet();
    }

    DeleteBullets();
}

/*
Draws player aircraft and bullets
*/
void Game::Draw() {
    player.Draw();

    for (auto& bullet: player.bullets) {
        bullet.Draw();
    }

    for (auto& enemy: enemies) {
        for (auto& bullet: enemy.bullets) {
            bullet.Draw();
        }
    }

    for (auto& enemy: enemies) {
        enemy.Draw();
    }
}

/*
Moves the player left or right if they press the left or right keys and makes
them fire a bullet when they press spacebar
*/
void Game::HandleInput() {
    if(IsKeyDown(KEY_LEFT)) {
        player.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        player.MoveRight();
    }
    if (IsKeyDown(KEY_SPACE)) {
        player.FireBullet();
    }
}

vector<Enemy> Game::CreateEnemies(int numEnemies) {
    vector<Enemy> enemies;
    for (int i = 0; i < numEnemies; i++) {
        float posHorizontal = rand() % (GetScreenWidth() + 1);
        float posVertical = (rand() % (GetScreenWidth() + 1)) * -1;
        
        enemies.push_back(Enemy({posHorizontal, posVertical}));
    }

    return enemies;
}

/*
Removes bullets when they are out of sight
*/
void Game::DeleteBullets() {
    for (auto it = player.bullets.begin(); it != player.bullets.end();) {
        if (!it -> active) {
            it = player.bullets.erase(it);
        } else {
            it++;
        }
    }
}
