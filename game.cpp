#include "game.hpp"
#include <vector>
#include <cstdlib>

using namespace std;

Game::Game(int numEnemies) {
    this -> numEnemies = numEnemies; 
    InitGame();
}

Game::~Game() {
    for (auto& enemy: enemies) {
        enemy.UnloadImages();
    }
}

/*
Automatically updating if the bullets are active or not and deleting those which
are not active
*/
void Game::Update() {
    if (run) {
        for (auto& bullet: player.bullets) {
            bullet.Update();
        }

        for (auto& bullet: enemyBullets) {
            bullet.Update();
        }

        for (auto& enemy: enemies) {
            enemy.MoveDown();
            enemy.Update();
            enemy.FireBullet(enemyBullets);
        }

        DeleteBullets();
        CheckCollisions();
    } else if (IsKeyDown(KEY_ENTER)) {
        Reset();
    }
}

/*
Draws player aircraft and bullets
*/
void Game::Draw() {
    
    player.Draw();

    for (auto& bullet: player.bullets) {
        bullet.Draw();
    }

    for (auto& bullet: enemyBullets) {
        bullet.Draw();
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
    if (run) {
        if(IsKeyDown(KEY_LEFT)) {
            player.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            player.MoveRight();
        }
        if (IsKeyDown(KEY_SPACE)) {
            player.FireBullet();
        }
    }
}

void Game::CheckCollisions() {
    // Player's bullets
    for (auto& bullet: player.bullets) {
        for(auto it = enemies.begin(); it != enemies.end();) {
            if(CheckCollisionRecs(it -> getRect(), bullet.getRect())) {
                it = enemies.erase(it);
                bullet.active = false;
            } else {
                it++;
            }
        }
    }

    // Enemy's bullets
    for (auto& bullet: enemyBullets) {
        if (CheckCollisionRecs(bullet.getRect(), player.getRect())) {
            bullet.active = false;
            playerHealth--;
            if (playerHealth == 0) {
                GameOver();
            }
            // playerColor = {232, 35, 35, 255};
            player.damageGraphic();
            cout << "Player hit" << endl;
        }
    }

    // Enemy collides with Player, or vice versa
    for (auto it = enemies.begin(); it != enemies.end();) {
        if(CheckCollisionRecs(it -> getRect(), player.getRect())) {
            it = enemies.erase(it);
            cout << "Spaceship done" << endl;
        } else {
            it++;
        }
    }
}

void Game::Reset() {
    enemies.clear();
    enemyBullets.clear();
    player.bullets.clear();
    player.InitPlayer();
    InitGame();
}

void Game::InitGame() {
    enemies = CreateEnemies(numEnemies);
    playerColor = WHITE;
    playerHealth = 5;
    run = true;
}

vector<Enemy> Game::CreateEnemies(int numEnemies) {

    for (int i = 0; i < numEnemies; i++) {
        float posHorizontal = rand() % (GetScreenWidth() + 1);
        float posVertical = (rand() % (GetScreenWidth() + 1)) * -2;
        
        enemies.push_back(Enemy({posHorizontal, posVertical}));
    }

    return enemies;
}

/*
Removes bullets when they are not active, one for player bullets and
the other for enemy bullets
*/
void Game::DeleteBullets() {
    for (auto it = player.bullets.begin(); it != player.bullets.end();) {
        if (!it -> active) {
            it = player.bullets.erase(it);
        } else {
            it++;
        }
    }

    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        if (!it -> active) {
            it = enemyBullets.erase(it);
        } else {
            it++;
        }
    }
}

void Game::GameOver() {
    run = false;
}
