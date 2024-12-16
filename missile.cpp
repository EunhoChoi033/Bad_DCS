#include "missile.hpp"

Missile::Missile(Vector2 position, float missileSpeed, float missileTurnRate, int id) {
    this -> position = position;
    this -> missileSpeed = missileSpeed;
    this -> missileTurnRate = missileTurnRate;
    this -> id = id;
    
    active = true;
}


void Missile::Draw() {
    if (active) {
        DrawRectangle(position.x, position.y, 10, 30, WHITE);
    }
}

void Missile::Update() {
    position.y += missileSpeed;
    if (active && (position.y < 0) && id == 0) {
        active = false;
    }
    if (active && (position.y > GetScreenHeight()) && id == 1) {
        active = false;
    }
}
