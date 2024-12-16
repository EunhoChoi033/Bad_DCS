#pragma once
#include <raylib.h>

class Button {
    public:
        Button(Vector2 position, float width, float height, Color color);
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);
    private:
        Texture2D image;
        Vector2 position;
        Color color;
        float width;
        float height;
        float thickness;
};