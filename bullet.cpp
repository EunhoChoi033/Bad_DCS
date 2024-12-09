#include "bullet.hpp"

using namespace std;

// id(0) = player, id(1) = enemy
Bullet::Bullet(Vector2 position, int speed, int id) {
    // image = LoadTexture("Graphics/tracer.png");
    this -> position = position;
    this -> speed = speed;
    this -> id = id;

    active = true;
}

// Draws bullets
void Bullet::Draw() {
    // DrawTextureV(image, position, WHITE);
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {245, 184, 105, 255});
    }
}

void Bullet::Update() {
    position.y += speed;
    if (active && (position.y < 0) && id == 0) {
        active = false;
    }
    if (active && (position.y > GetScreenHeight()) && id == 1) {
        active = false;
    }
}