#include "enemy.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Enemy::Enemy(Vector2 position) {
    this -> position = position;
    
    image = LoadTexture("Graphics/jet2.png");
    image.height /= 20;
    image.width /= 20;
    movementCooldown = 0.0;
}

// Draws enemy plane
void Enemy::Draw() {
    DrawTextureV(image, position, WHITE);
}

// Moves the plane down
void Enemy::MoveDown() {
    if (position.y < GetScreenHeight()) {
        position.y += 3;
    }
}

void Enemy::Update() {
    if (GetTime() - movementCooldown >= 0.02) {
        movementDecider = rand() % 3;
    }

    cout << movementDecider << endl;
    
    switch(movementDecider) {
    case 0:
        if (position.x > 0) {
            position.x -= 5;
            movementCooldown = GetTime();
        }
        break;
    
    case 1:
        if (position.x < (GetScreenWidth() - image.width)) {
            position.x += 5;
            movementCooldown = GetTime();
        }
        break;

    case 2:
        break;
    }
    // switch(rand() % 3){
    //     case 0:
    //         if (position.x > 0) {
    //             if (GetTime() - movementCooldown >= 1) {
    //                 position.x -= 5;
    //                 movementCooldown = GetTime();
    //             } else {
    //                 position.x += 5;
    //             }
    //         }
    //         break;

    //     case 1:
    //         if (position.x < GetScreenWidth() - image.width) {
    //             if (GetTime() - movementCooldown >= 1) {
    //                 position.x += 5;
    //                 movementCooldown = GetTime();
    //             } else {
    //                 position.x -= 5;
    //             }
    //         }
    //         break;

    //     case 2:
    //         break;
    // }
}
