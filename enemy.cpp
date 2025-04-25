#include "enemy.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Enemy::Enemy(Vector2 position, int enemyNum, int numEnemies, float horizontalVariationLeft) {
    this -> position = position;
    this -> enemyNum = enemyNum;
    this -> numEnemies = numEnemies;
    this -> horizontalVariationLeft = horizontalVariationLeft;
    srand(GetTime() + (double)enemyNum);
    missileRequests = 0;

    if (position.x != GetScreenWidth() && position.y != GetScreenHeight()) {
        InitEnemy();
    }
}

void Enemy::InitEnemy() {
    enemyHealth = 2;
    planeColor = {230, (unsigned char)(115 * enemyHealth), (unsigned char)(115 * enemyHealth), 255};
    image = LoadTexture("Graphics/jet2.png");
    image.height /= 25;
    image.width /= 25;
    movementCooldown = 0.0;
    fireMissileCooldown = 0.0;
    fireCooldown = 0.0;
    countermeasureCooldown = 0.0;
    enemyCountermeasures = Countermeasures(enemyNum, numEnemies, image.width, image.height);
}

// Draws enemy plane
void Enemy::Draw() {
    DrawTextureV(image, position, planeColor);
    enemyCountermeasures.Draw();

    // if (missiles.size() > 0) {
    //     for (auto& missile: missiles) {
    //         cout << "Drawing" << endl;
    //         missile.Draw();
    //     }
    // }
}

// Moves the plane down
void Enemy::MoveDown() {
    if (position.y < GetScreenHeight()) {
        position.y += 1;
    }
}

void Enemy::FireCountermeasure() { 
    if(GetTime() - countermeasureCooldown >= ENEMY_COUNTERMEASURE_COOLDOWN_TIME) {
        enemyCountermeasures.AddFlare(position);
        countermeasureCooldown = GetTime();
    }
}

/*
Randomly makes the enemy move to the left, right, or continue down straight
after a certain period of time
*/
void Enemy::Update() {
    
    if (GetTime() - movementCooldown >= 0.5) {
        movementDecider = rand() % 3;
        movementCooldown = GetTime();
    }
    
    switch(movementDecider) {
        case 0:
        if (position.x > horizontalVariationLeft) {
            position.x -= 1;
        }
        break;
        
        case 1:
        if (position.x < (GetScreenWidth() - image.width)) {
            position.x += 1;
        }
        break;
    }

    if ((GetTime() - fireMissileCooldown) > FIRING_MISSILE_COOLDOWN_TIME) {
        FireMissileOpportunity();
        fireMissileCooldown = GetTime();
    }

    enemyCountermeasures.Update();
    
    // if (missiles.size() > 0) {
    //     for (auto& missile: missiles) {
    //         missile.Update({playerPos.x, playerPos.y}, image.width, image.height);
    //     }
    // }

    // FireCountermeasure();
}

void Enemy::FireBullet(vector<Bullet>& enemyBullets) {
    if (GetTime() - fireCooldown >= 1) {
        enemyBullets.push_back(Bullet({position.x + image.width/2 - 2, 
        position.y + image.height/2 - 7}, 6, 1));
        fireCooldown = GetTime();
    }
}

void Enemy::UnloadImages() {
    UnloadTexture(image);
}

void Enemy::DamageEnemy(Sound hitSound, int damageAmount) {
    if ((enemyHealth - damageAmount) < 0) {
        enemyHealth = 0;
    } else {
        enemyHealth -= damageAmount;
    }

    planeColor = {planeColor.r, (unsigned char)(115 * enemyHealth), 
    (unsigned char)(115 * enemyHealth), planeColor.a};
    PlaySound(hitSound);
}

int Enemy::GetEnemyNum() {
    return enemyNum;
}

Vector2 Enemy::GetEnemyPos() {
    return position;
}

float Enemy::GetEnemyXPos() {
    return position.x;
}

float Enemy::GetEnemyYPos() {
    return position.y;
}

int Enemy::GetMissileRequests() {
    return missileRequests;
}

void Enemy::SetMissileRequests(int missileRequests) {
    this -> missileRequests = missileRequests;
}

void Enemy::SetPlayerPos(Vector2 playerPos) {
    this -> playerPos = playerPos;
}

Rectangle Enemy::GetRect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Enemy::FireMissileOpportunity() {

    if ((rand() % FIRING_MISSILE_PROBABILITY_TOTAL) < FIRING_MISSILE_PROBABILITY) {
        missileRequests = 1;
        // cout << "#" << enemyNum << " requesting Missile" << endl;
    }
}

// int Enemy::GetMissilesSize() {
//     return missiles.size();
// }

// vector<Missile> Enemy::GetMissiles() {
//     return missiles;
// }
