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
        bool getSelected();
        void setSelected(bool selected);
        bool isPressed(Vector2 mousePos, bool mousePressed);
        int enemyNum;
    private:
        Font font;
        Vector2 position;
        Color color;
        float radius;
        float thickness;
        bool selected;
        // int state;
};