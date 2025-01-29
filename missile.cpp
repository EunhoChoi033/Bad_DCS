#include "missile.hpp"

Missile::Missile(Vector2 position, float speed, int id) {
    this -> position = position;
    this -> speed = speed;
    this -> id = id;
    
    image = LoadTexture("Graphics/missile.png");
    image.width /= 4;
    image.height /= 4;
    active = true;
}

Missile::Missile() {
}

void Missile::Draw() {
    if (active) {
        DrawTextureV(image, position, WHITE);
    }
}

void Missile::Update(Vector2 targetPos, float targetWidth, float targetHeight) {
    if (targetPos.y < position.x - 50) {
        direction = {targetPos.x + (targetWidth / 2) - position.x - (image.width / 2), targetPos.y + (targetHeight / 2) - position.y - (image.height / 2)};
        normalizeVector();
        Vector2 velocity = {direction.x * speed, direction.y * speed};

        position.x += velocity.x;
        position.y += velocity.y;
    } else {
        position.y -= speed;
    }
}

Rectangle Missile::getRect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}

int Missile::getId() {
    return id;
}

void Missile::normalizeVector() {
    float magnitude = hypot(direction.x, direction.y);
    direction.x /= magnitude;
    direction.y /= magnitude;
}
