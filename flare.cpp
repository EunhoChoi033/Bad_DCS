#include "flare.hpp"

Flare::Flare(Vector2 position, Color initColor, int initHealth) {
    this -> position = position;
    this -> color = initColor;
    this -> health = initHealth;
}

void Flare::Draw() {
    DrawRectangle(position.x, position.y, 10, 10, color);
}

void Flare::Update() {
    health--;
    position.x += 10;
    color = Color{color.r, color.g, color.b, (unsigned char)(15 * health)};
}

void Flare::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

int Flare::getHealth() {
    return health;
}
