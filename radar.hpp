#pragma once
#include <raylib.h>

class Radar {
    public:
        Radar(Vector2 position, Color color);
        ~Radar();
        void Draw();
        void Update();
    private:
        Vector2 position;
        Color color;
};