#include "enemy.hpp"

Enemy::Enemy(Vector2 position) {
    this -> position = position;
    
    image = LoadTexture("Graphics/jet2.png");
    image.height /= 20;
    image.width /= 20;
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