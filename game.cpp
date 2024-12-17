#include "game.hpp"
#include <vector>
#include <cstdlib>

using namespace std;

Game::Game(int numEnemies, int playerHealth, Color colorMain) {
    gunfire = LoadSound("Sounds/gunfire.wav");
    bulletHit = LoadSound("Sounds/bullet_hit.wav");
    SetSoundVolume(gunfire, 0.5f);
    SetSoundVolume(bulletHit, 0.25f);
    InitGame(numEnemies, playerHealth, colorMain);    
    playerRadar = Radar({120, GetScreenHeight() / 2.0f}, player.image.width, colorMain);
}

Game::~Game() {
    for (auto& enemy: enemies) {
        enemy.UnloadImages();
    }
    UnloadSound(gunfire);
}

/*
Automatically updating if the bullets are active or not and deleting those which
are not active
*/
void Game::Update() {
    if (run) {

        playerRadar.Update(player.position, enemies);

        for (auto& enemy: enemies) {
            enemy.MoveDown();
            enemy.Update();
            enemy.FireBullet(enemyBullets);
        }

        for (auto& bullet: player.bullets) {
            bullet.Update();
        }
        
        for (auto& bullet: enemyBullets) {
            bullet.Update();
        }

        DeleteBullets();
        CheckCollisions();
    }
    
    if (enemies.size() == 0) {
        run = false;
    }

    if (IsKeyDown(KEY_ENTER)) {
        Reset();
    }
}

/*
Draws player aircraft and bullets
*/
void Game::Draw() {
    
    player.Draw();
    playerRadar.Draw();

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
            player.FireBullet(gunfire);
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
            player.DamagePlayer(bulletHit, 1);
            if (player.playerHealth == 0) {
                GameOver();
            }
        }
    }

    // Enemy collides with Player, or vice versa
    for (auto it = enemies.begin(); it != enemies.end();) {
        if(CheckCollisionRecs(it -> getRect(), player.getRect())) {
            it = enemies.erase(it);
            player.DamagePlayer(bulletHit, 5);
            // Need to change sound
            if (player.playerHealth == 0) {
                GameOver();
            }
        } else {
            it++;
        }
    }
}

void Game::Reset() {
    enemies.clear();
    enemyBullets.clear();
    player.bullets.clear();
    InitGame(numEnemies, playerHealth, colorMain);
}

void Game::InitGame(int numEnemies, int playerHealth, Color colorMain) {
    this -> numEnemies = numEnemies; 
    this -> playerHealth = playerHealth;
    enemies = CreateEnemies(numEnemies);
    player.playerHealth = playerHealth;
    player.InitPlayer();

    run = true;
}

vector<Enemy> Game::CreateEnemies(int numEnemies) {

    for (int i = 0; i < numEnemies; i++) {
        float posHorizontal = rand() % (GetScreenWidth() - player.image.width);
        float posVertical = ((rand() % GetScreenWidth()) * -1.5)
        - player.image.height;
        
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
