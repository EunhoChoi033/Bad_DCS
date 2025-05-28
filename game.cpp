#include "game.hpp"

using namespace std;

Game::Game(int numEnemies, int playerHealth, Color colorMain, float horizontalVariationLeft) {
    this -> horizontalVariationLeft = horizontalVariationLeft;
    gunfire = LoadSound("Sounds/gunfire.wav");
    bulletHit = LoadSound("Sounds/bullet_hit.wav");
    radarPing = LoadSound("Sounds/radar_update_blip.wav");
    playerPlaneImage = LoadTexture("Graphics/jet.png");
    playerPlaneImage.height /= 25;
    playerPlaneImage.width /= 25;
    SetSoundVolume(gunfire, 0.5f);
    SetSoundVolume(bulletHit, 0.25f);
    SetSoundVolume(radarPing, 0.15f);
    InitGame(numEnemies, playerHealth, colorMain);    
    playerRadar = Radar({horizontalVariationLeft / 2, GetScreenHeight() / 2.0f}, player.position, player.image.width, player.image.height, colorMain, radarPing, enemies, horizontalVariationLeft);
}

Game::~Game() {
    for (auto& enemy: enemies) {
        enemy.UnloadImages();
    }
    UnloadSound(gunfire);
    UnloadSound(bulletHit);
    UnloadSound(radarPing);
    UnloadSound(playerRadar.missileLockVWS);
    UnloadMusicStream(playerRadar.missileLocking);
}


/*
Automatically updating if the bullets are active or not and deleting those which
are not active
*/
void Game::Update() {
    if (run) {
        player.Update();
        currentPlayerPos = player.GetPlayerPos();

        for (auto& enemy: enemies) {
            enemy.MoveDown();
            enemy.SetPlayerPos(currentPlayerPos);
            if ((enemy.GetMissileRequests() == 1) && (player.GetPlayerPos().y - enemy.GetEnemyYPos() > 200)) {
                int currentNumEnemies = numEnemies;
                enemyMissiles.push_back(Missile(enemy.GetEnemyPos(), 3.0, currentNumEnemies));
                enemy.SetMissileRequests(0);
                playerRadar.AlertMissileLaunch();
                cout << "Spawning Enemy Missile" << endl;
            }
            enemy.Update();
            enemy.FireBullet(enemyBullets);
        }

        playerRadar.SetEnemyMissiles(enemyMissiles);

        if (enemyMissiles.size() > 0) {
            Vector2 playerPos = player.GetPlayerPos();
            for (auto& missile: enemyMissiles) {
                missile.Update({playerPos.x, playerPos.y}, playerPlaneImage.width, playerPlaneImage.height);
                if (player.GetCountermeasureFired() && ((missile.DistanceFromMissile(player.GetPlayerPos())) < FLARE_DISTANCE_TO_MISSILE_TO_LOSE_LOCK)) {
                    missile.LoseLockOpportunity();
                    player.SetCountermeasureFired(true);
                }

            }
        }

        for (auto& bullet: player.bullets) {
            bullet.Update();
        }
        
        for (auto& bullet: enemyBullets) {
            bullet.Update();
        }

        playerRadar.Update(player.position, enemies);

        DeleteStuff();
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
        // cout << enemy.getEnemyNum() << ", ";
    }

    for (auto& missile: enemyMissiles) {
        missile.Draw();
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
        player.HandleInput();
    }
}

int Game::GetNumEnemies() {
    return enemies.size();
}

void Game::CheckCollisions() {
    // Player's bullets
    for (auto& bullet: player.bullets) {
        for(auto it = enemies.begin(); it != enemies.end();) {
            if(CheckCollisionRecs(it -> GetRect(), bullet.GetRect())) {
                bullet.active = false;
                it -> DamageEnemy(bulletHit, 1);
                if (it -> enemyHealth == 0) {
                    it = enemies.erase(it);
                } else {
                    it++;
                }
            } else {
                it++;
            }
        }
    }

    // Enemy's bullets
    for (auto& bullet: enemyBullets) {
        if (CheckCollisionRecs(bullet.GetRect(), player.GetRect())) {
            bullet.active = false;
            player.DamagePlayer(bulletHit, 1);
            if (player.GetPlayerHealth() == 0) {
                GameOver();
            }
        }
    }

    // Enemy collides with Player, or vice versa
    for (auto it = enemies.begin(); it != enemies.end();) {
        if(CheckCollisionRecs(it -> GetRect(), player.GetRect())) {
            it = enemies.erase(it);
            player.DamagePlayer(bulletHit, 8);
            // Need to change sound
            if (player.GetPlayerHealth() == 0) {
                GameOver();
            }
        } else {
            it++;
        }
    }

    // Enemy-Missile Collision
    for (auto& missile: playerRadar.missiles) {
        for (auto it = enemies.begin(); it != enemies.end();){
            if (CheckCollisionRecs(it -> GetRect(), missile.GetRect())) {
                player.DamagePlayer(bulletHit, 0);
                it = enemies.erase(it);
                missile.SetActive(false);
                break;
            } else {
                it++;
            }
        }
    }

    // Player-Missile Collision
    if (enemyMissiles.size() > 0) {
        for (auto it = enemyMissiles.begin(); it != enemyMissiles.end();) {
            if (CheckCollisionRecs(it -> GetRect(), player.GetRect())) {
                player.DamagePlayer(bulletHit, 5);
                it = enemyMissiles.erase(it);
                if (player.GetPlayerHealth() == 0) {
                    GameOver();
                }
            } else {
                it++;
            }
        }
    }
}

void Game::Reset() {
    enemies.clear();
    enemyBullets.clear();
    enemyMissiles.clear();
    player.bullets.clear();
    playerRadar.ClearMissiles();
    playerRadar.SetSelectedEnemy(-1);
    InitGame(numEnemies, playerHealth, colorMain);
}

void Game::InitGame(int numEnemies, int playerHealth, Color colorMain) {
    this -> numEnemies = numEnemies; 
    this -> playerHealth = playerHealth;
    enemies = CreateEnemies(numEnemies);
    player.playerHealth = playerHealth;
    player.InitPlayer(horizontalVariationLeft);
    player.SetNumEnemies(numEnemies);
    run = true;
}

vector<Enemy> Game::CreateEnemies(int numEnemies) {

    for (int i = 0; i < numEnemies; i++) {
        float posHorizontal = (rand() % (GetScreenWidth() - player.image.width - (int)horizontalVariationLeft)) + horizontalVariationLeft;
        float posVertical = ((rand() % GetScreenWidth()) * -1.5) - player.image.height;
        
        enemies.push_back(Enemy({posHorizontal, posVertical}, i, numEnemies, horizontalVariationLeft));
    }

    return enemies;
}

/*
Removes bullets and missiles when they are not active, one for player bullets and the other for enemy bullets
*/
void Game::DeleteStuff() {
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

    for (auto it = playerRadar.missiles.begin(); it != playerRadar.missiles.end();) {
        if (!it -> GetActive()) {
            it = playerRadar.missiles.erase(it);
        } else {
            it++;
        }
    }

    if (enemyMissiles.size() > 0) {
        for (auto it = enemyMissiles.begin(); it != enemyMissiles.end();) {
            if (!it -> GetActive()) {
                it = enemyMissiles.erase(it);
            } else {
                it++;
            }
        }
    }
}

void Game::GameOver() {
    run = false;
}
