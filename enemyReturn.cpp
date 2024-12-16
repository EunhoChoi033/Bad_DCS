#include "enemyReturn.hpp"

EnemyReturn::EnemyReturn(Vector2 position) {
    this -> position = position;
}

void EnemyReturn::Draw() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 20;
    rect.height = 20;

    
}
