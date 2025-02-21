#include "flare.hpp"

Flare::Flare(Vector2 position, Color initColor, int initHealth, float healthMultiplier, float horizontalVariation, float verticalVariation, float verticalAcceleration, float entityHorizontalCompensation) {
    this -> position = position;
    this -> color = initColor;
    this -> health = initHealth;
    this -> healthMultiplier = healthMultiplier;
    this -> xVelocity = horizontalVariation;
    this -> yVelocity = verticalVariation;
    this -> yAcceleration = verticalAcceleration;
    this -> entityHorizontalCompensation = entityHorizontalCompensation;
}

void Flare::Draw() {
    DrawRectangle(position.x, position.y, 10, 10, color);
}

void Flare::Update() {
    health--;
    position.x += xVelocity + entityHorizontalCompensation;
    yVelocity += yAcceleration;
    position.y += yVelocity;
    // color = Color{color.r, color.g, color.b, (unsigned char)(15 * health)};
    color = Color{color.r, color.g, color.b, (unsigned char)(healthMultiplier * health)};
}

void Flare::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

int Flare::GetHealth() {
    return health;
}
