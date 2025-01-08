#include "enemyReturn.hpp"

// enum RadarTargetState {
//     LIVE, LOCKED, LOCKING, MISSILE, MISSILE_LAUNCH
//
//     Locking sound effects: https://youtu.be/hok2D_9Y6Ic
//     https://youtu.be/LtyxrdLwVsU
//     https://youtu.be/Jqt2kg7IUt8 
// };

EnemyReturn::EnemyReturn(Vector2 position, Color color, Font font, int enemyNum) {
    this -> position = position;
    this -> color = color;
    this -> font = font;
    this -> enemyNum = enemyNum;
    radius = 10.0f;
    thickness = 2.0f;
}

EnemyReturn::EnemyReturn() {
    
}

void EnemyReturn::Draw() {
    
    DrawPolyLinesEx(position, 4, radius, 0.0f, thickness, color);
    DrawRing(position, radius, radius + thickness, 0.0f, 360.0f, 128, color);
    
    // Other stuff to draw on the radar:

    // DrawRing(position, radius, radius + thickness, 0.0f, 360.0f, 128, color);
    // const char* missileMessage = "M";
    // Vector2 offset = MeasureTextEx(font, missileMessage, 10, 1);
    // DrawTextEx(font, missileMessage, {position.x - (offset.x / 2), position.y - (offset.y / 2)}, 10, 1, color);
}

void EnemyReturn::Update(Vector2 newPosition) {
    position = newPosition;
}

void EnemyReturn::setColor(Color newColor) {
    color = newColor;
}

bool EnemyReturn::isPressed(Vector2 mousePos, bool mousePressed) {
    if (CheckCollisionPointCircle(mousePos, position, radius) && mousePressed) {
        return true;
    } else {
        return false;
    }
}
