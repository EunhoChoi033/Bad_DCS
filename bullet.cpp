#include "bullet.hpp"

using namespace std;

Bullet::Bullet(Vector2 position, int speed) {
    // image = LoadTexture("Graphics/tracer.png");
    this -> position = position;
    this -> speed = speed;
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
    if (active && (position.y > GetScreenHeight())) {
        active = false;
    }
}