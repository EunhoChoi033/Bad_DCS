#include "player.hpp"

Player::Player() {
    image = LoadTexture("Graphics/jet.png");
    image.height /= 20;
    image.width /= 20;
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;
    fireCooldown = 0.0;
}

// Removes the plane once game ends
Player::~Player() {
    UnloadTexture(image);
}

// Draws player's plane
void Player::Draw() {
    DrawTextureV(image, position, WHITE);
}

// Makes the player's plane move left
void Player::MoveLeft() {
    if (position.x != 0) {
       position.x -= 5; 
    }
}

// Makes the players plane move right
void Player::MoveRight() {
    if (position.x != GetScreenWidth() - image.width) {
       position.x += 5; 
    }
}

// Makes the player's plane fire a bullet and ensures a cooldown between shots
void Player::FireBullet() {
    if (GetTime() - fireCooldown >= 0.1) {
        bullets.push_back(Bullet({position.x + image.width/2 - 2, position.y}, 
        -6));
        fireCooldown = GetTime();
    }
}