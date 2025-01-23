#pragma once
#include <raylib.h>
#include <string>
#include <iostream>

using namespace std;

class EnemyReturn {
    public:
        EnemyReturn(Vector2 position, Color color, Font font, int enemyNum);
        EnemyReturn();
        // ~EnemyReturn();
        void Draw();
        void Update(Vector2 newPosition);
        void setColor(Color newColor);
        bool isPressed(Vector2 mousePos, bool mousePressed);
        int getEnemyReturnNum();

    private:
        int enemyNum;
        Font font;
        Vector2 position;
        Color color;
        float radius;
        float thickness;
        // int state;
};