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
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {245, 184, 105, 255});
    }
}

Rectangle Bullet::getRect() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Bullet::Update() {
    position.y += speed;
    if (active && ((position.y + 15) < 0) && id == 0) {
        active = false;
    }
    if (active && (position.y > GetScreenHeight()) && id == 1) {
        active = false;
    }
}