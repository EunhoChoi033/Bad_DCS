#include "missile.hpp"

Missile::Missile(Vector2 position, float speed, int id) {
    this -> position = position;
    this -> speed = speed;
    this -> id = id;
    
    image = LoadTexture("Graphics/missile.png");
    image.width /= 4;
    image.height /= 4;
    rotation = 0.0f;
    active = true;
    direction = {0, 0};
}

Missile::Missile() {
}

void Missile::Draw() {
    if (active) {
        // DrawTextureV(image, position, WHITE);
        DrawTextureEx(image, position, toDegrees(rotation) + 90.0f, 1.0f, WHITE);
    }
}

void Missile::Update(Vector2 targetPos, float targetWidth, float targetHeight) {
    
    if (active) {
        if (((position.x + image.width) < 0) || (position.x > GetScreenWidth())) {
            active = false;
        }
    }
    
    if ((position.y - 250) > targetPos.y) {
        direction = {targetPos.x + (targetWidth / 2) - position.x - (image.width / 2), targetPos.y + (targetHeight / 2) - position.y - (image.height / 2)};
        normalizeVector();
        rotation = atan2((double)direction.y, (double)direction.x);
        Vector2 velocity = {direction.x * speed, direction.y * speed};

        position.x += velocity.x;
        position.y += velocity.y;
    } else {
        Vector2 velocity;
        if (direction.x == 0 && direction.y == 0) {
            position.y -= speed;
            rotation = atan(-90);
        } else {
            velocity = {direction.x * speed, direction.y * speed};
            position.x += velocity.x;
            position.y += velocity.y;
            rotation = atan2((double)direction.y, (double)direction.x);
        }
    }
}

float Missile::toDegrees(float radians) {
    return radians * (180.0 / (2 * acos(0.0)));
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
