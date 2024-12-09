#include "game.hpp"
#include <vector>
#include <cstdlib>

Game::Game() { 
    vector<Enemy> enemies;
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

    DeleteBullets();
    // enemy.MoveDown();
}

/*
Draws player aircraft and bullets
*/
void Game::Draw() {
    player.Draw();

    for (auto& bullet: player.bullets) {
        bullet.Draw();
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

vector<Enemy> Game::CreateEnemies(vector<Enemy> enemies) {
    int posx = rand() % (GetScreenWidth() + 1);
    
    enemies.push_back(Enemy({posx, 100}));
}

/*
Removes bullets when they are out of sight
*/
void Game::DeleteBullets() {
    for (auto it = player.bullets.begin(); it != player.bullets.end();) {
        if (!it -> active) {
            it = player.bullets.erase(it);
        } else {
            ++ it;
        }
    }
}
