#include "enemy.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Enemy::Enemy(Vector2 position) {
    this -> position = position;
    
    image = LoadTexture("Graphics/jet2.png");
    image.height /= 30;
    image.width /= 30;
    movementCooldown = 0.0;
    fireCooldown = 0.0;
}

// Draws enemy plane
void Enemy::Draw() {
    DrawTextureV(image, position, WHITE);
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
        // cout << "Movement decider changed to " << movementDecider << endl;
    }
    
    switch(movementDecider) {
    case 0:
        if (position.x > 0) {
            position.x -= 3;
        }
        break;
    
    case 1:
        if (position.x < (GetScreenWidth() - image.width)) {
            position.x += 3;
        }
        break;

    // case 2:
    //     break;
    }
}

void Enemy::FireBullet() {
    if (GetTime() - fireCooldown >= 1) {
        bullets.push_back(Bullet({position.x + image.width/2 - 2, position.y +
        image.height/2 - 7}, 6, 1));
        fireCooldown = GetTime();
        // cout << "FIRE" << endl;
    }
}
