#include "radar.hpp"

Radar::Radar(Vector2 position, Color color) {
    this -> position = position;
    this -> color = color;
}

void Radar::Draw() {
    DrawCircle(position.x, position.y, 10, color);
}
