#include "enemy.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Enemy::Enemy(Vector2 position, int enemyNum) {
    this -> position = position;
    this -> enemyNum = enemyNum;

    enemyHealth = 2;
    planeColor = {230, (unsigned char)(115 * enemyHealth), (unsigned char)(115 * enemyHealth), 255};
    image = LoadTexture("Graphics/jet2.png");
    image.height /= 25;
    image.width /= 25;
    movementCooldown = 0.0;
    fireCooldown = 0.0;
}

// Draws enemy plane
void Enemy::Draw() {
    DrawTextureV(image, position, planeColor);
}

// Moves the plane down
void Enemy::MoveDown() {
    if (position.y < GetScreenHeight()) {
        position.y += 1;
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
        if (position.x > 0) {
            position.x -= 1;
        }
        break;
    
    case 1:
        if (position.x < (GetScreenWidth() - image.width)) {
            position.x += 1;
        }
        break;
    }
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
    cout << enemyHealth << endl;
}

Rectangle Enemy::getRect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}
