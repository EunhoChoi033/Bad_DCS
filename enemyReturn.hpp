#pragma once
#include <raylib.h>
#include <string>
#include <iostream>

using namespace std;

class EnemyReturn {
    public:
        EnemyReturn(Vector2 position, Color color, Font font);
        EnemyReturn();
        // ~EnemyReturn();
        void Draw();
        void Update(Vector2 newPosition);
    private:
        Font font;
        Vector2 position;
        Color color;
        float radius;
        float thickness;
        // int state;
};