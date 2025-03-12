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
        void SetColor(Color newColor);
        void SetLockable(bool newLockable);
        bool GetLockable();
        bool IsPressed(Vector2 mousePos, bool mousePressed);
        int GetEnemyReturnNum();

    private:
        int enemyNum;
        Font font;
        Vector2 position;
        Color color;
        float radius;
        float thickness;
        bool lockable;
        // int state;
};