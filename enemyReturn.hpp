#pragma once
#include <raylib.h>

class EnemyReturn {
    public:
        EnemyReturn(Vector2 position);
        void Draw();
        void Update(Vector2 position);
    private:
        Vector2 position;
        // int state;
};