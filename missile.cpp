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
    tracking = true;
    direction = {0, 0};
}

Missile::Missile() {
}

void Missile::Draw() {
    if (active) {
        // DrawTextureV(image, position, WHITE);
        DrawTextureEx(image, position, ToDegrees(rotation) + 90.0f, 1.0f, WHITE);
    }
}

void Missile::Update(Vector2 targetPos, float targetWidth, float targetHeight) {
    
    if (active) {
        if (((position.x + image.width) < 0) || (position.x > GetScreenWidth()) || (position.y < GetScreenHeight())) {
            active = false;
        }
    }
    
    // MISSILE DEVIATION: If the enemy is 200 pixels ahead of the missile (direct vertical distance), then the missile will stop tracking the target and continue on its previously given course
    if (tracking && ((abs(targetPos.y - position.y) < 200) || (targetPos.x == (float)GetScreenWidth() && targetPos.y == (float)GetScreenHeight()))) {
        tracking = false;
    }
    if (tracking) {
        direction = {targetPos.x + (targetWidth / 2) - position.x - (image.width / 2), targetPos.y + (targetHeight / 2) - position.y - (image.height / 2)};
        NormalizeVector();
        rotation = atan2((double)direction.y, (double)direction.x);
       
        Vector2 velocity = {direction.x * speed, direction.y * speed};
        position.x += velocity.x;
        position.y += velocity.y;
        cout << "Tracking" << endl;
    } else {
        cout << "Not Tracking" << endl;
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

float Missile::ToDegrees(float radians) {
    return radians * (180.0 / (2 * acos(0.0)));
}

Rectangle Missile::GetRect() {
    return {position.x, position.y, float(image.width), float(image.height)};
}

int Missile::GetId() {
    return id;
}

bool Missile::GetActive() {
    return active;
}

void Missile::SetActive(bool active) {
    this -> active = active;
}

void Missile::NormalizeVector() {
    float magnitude = hypot(direction.x, direction.y);
    direction.x /= magnitude;
    direction.y /= magnitude;
}

void Missile::LoseLockOpportunity() {
    srand(time(0));

    if ((rand() % LOSING_LOCK_PROBABILITY_TOTAL) < LOSING_LOCK_PROBABILITY) {
        tracking = false;
    }
}
