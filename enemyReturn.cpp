#include "enemyReturn.hpp"

// enum RadarTargetState {
//     LIVE, LOCKED, LOCKING, MISSILE, MISSILE_LAUNCH
//
//     Locking sound effects: 
//     https://youtu.be/LtyxrdLwVsU
//     https://youtu.be/Jqt2kg7IUt8 
// };

EnemyReturn::EnemyReturn(Vector2 position, Color color, Font font, int enemyNum) {
    this -> position = position;
    this -> color = color;
    this -> font = font;
    this -> enemyNum = enemyNum;
    lockable = false;
    radius = 10.0f;
    thickness = 2.0f;
}

EnemyReturn::EnemyReturn() {
    
}

void EnemyReturn::Draw() {
    
    DrawPolyLinesEx(position, 4, radius, 0.0f, thickness, color);
    if (lockable) {
        DrawRing(position, radius, radius + thickness, 0.0f, 360.0f, 128, color);
    }
    
    // Other stuff to draw on the radar:

    // DrawRing(position, radius, radius + thickness, 0.0f, 360.0f, 128, color);
    // const char* missileMessage = "M";
    // Vector2 offset = MeasureTextEx(font, missileMessage, 10, 1);
    // DrawTextEx(font, missileMessage, {position.x - (offset.x / 2), position.y - (offset.y / 2)}, 10, 1, color);
}

void EnemyReturn::Update(Vector2 newPosition) {
    position = newPosition;
}

void EnemyReturn::SetColor(Color newColor) {
    color = newColor;
}

void EnemyReturn::SetLockable(bool newLockable) {
    lockable = newLockable;
}

bool EnemyReturn::GetLockable() {
    return lockable;
}

bool EnemyReturn::IsPressed(Vector2 mousePos, bool mousePressed) {
    if (CheckCollisionPointCircle(mousePos, position, radius) && mousePressed) {
        return true;
    } else {
        return false;
    }
}

int EnemyReturn::GetEnemyReturnNum() {
    return enemyNum;
}
