#include "radar.hpp"

using namespace std;

Radar::Radar(Vector2 position, Color color) {
    this -> position = position;
    this -> color = color;
    radarRangeX = GetScreenWidth() / 3;
    radarRangeY = 2 * GetScreenHeight();
}

Radar::Radar() {

}

// Radar::~Radar() {

// }

void Radar::Draw() {
    Color fadedColor = {color.r, color.g, color.b, (unsigned char)limiter(color.a - 225, 0 , 255)};
    DrawCircle(position.x, position.y, 100, fadedColor);
    DrawRing(position, 100.0f, 105.0f, 0, 360, 128, color);
    DrawRing(position, 20.0f, 25.0f, 0, 360, 128, color);

    
}

void Radar::Update(Vector2 playerPos, vector<Enemy> enemies) {
//     enemyReturns.clear();
//     for (auto& enemy: enemies) {

//     }
}

int Radar::limiter(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}