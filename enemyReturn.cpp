#include "enemyReturn.hpp"

EnemyReturn::EnemyReturn(Vector2 position, Color color, Font font) {
    this -> position = position;
    this -> color = color;
    this -> font = font;
    radius = 10.0f;
    thickness = 2.0f;
}

EnemyReturn::EnemyReturn() {
    
}



// EnemyReturn::~EnemyReturn() {
//     UnloadFont(font);
// }

void EnemyReturn::Draw() {
    
    DrawPolyLinesEx(position, 4, radius, 0.0f, thickness, color);
    DrawRing(position, radius, radius + thickness, 0.0f, 360.0f, 128, color);
    
    // DrawRing(position, radius, radius + thickness, 0.0f, 360.0f, 128, color);
    // const char* missileMessage = "M";
    // Vector2 offset = MeasureTextEx(font, missileMessage, 10, 1);
    // DrawTextEx(font, missileMessage, {position.x - (offset.x / 2), position.y - (offset.y / 2)}, 10, 1, color);
}

void EnemyReturn::Update(Vector2 newPosition) {
    position = newPosition;
}
