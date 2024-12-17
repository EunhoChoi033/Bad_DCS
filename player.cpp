#include "player.hpp"
#include <iostream>

Player::Player() {
    InitPlayer();
}

// Removes the plane once game ends
Player::~Player() {
    UnloadTexture(image);
}

// Draws player's plane
void Player::Draw() {
    DrawTextureV(image, position, planeColor);
}

// Makes the player's plane move left
void Player::MoveLeft() {
    if (position.x >= 0) {
       position.x -= 5; 
    }
}

// Makes the players plane move right
void Player::MoveRight() {
    if (position.x <= GetScreenWidth() - image.width) {
       position.x += 5; 
    }
}

// Makes the player's plane fire a bullet and ensures a cooldown between shots
void Player::FireBullet(Sound gunfire) {
    if (GetTime() - fireCooldown >= 0.1) {
        bullets.push_back(Bullet({position.x + image.width/2 - 2, position.y}, 
        -6, 0));
        fireCooldown = GetTime();
        PlaySound(gunfire);
    }
}

void Player::DamagePlayer(Sound hitSound, int damageAmount) {
    if ((playerHealth - damageAmount) < 0) {
        playerHealth = 0;
    } else {
        playerHealth -= damageAmount;
    }
    
    planeColor = {planeColor.r, (unsigned char)(23 * playerHealth), 
    (unsigned char)(23 * playerHealth), planeColor.a};
    PlaySound(hitSound);
}

void Player::InitPlayer() {
    image = LoadTexture("Graphics/jet.png");
    image.height /= 25;
    image.width /= 25;
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 75;
    fireCooldown = 0.0;
    planeColor = {230, (unsigned char)(23 * playerHealth), (unsigned char)(23 * 
    playerHealth), 255};
}

Rectangle Player::getRect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}
