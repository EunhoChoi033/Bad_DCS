#pragma once
#include <raylib.h>

class Aircraft{
    public:
        Aircraft();
        ~Aircraft();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireGun();
    private:
        Texture2D image;
        Vector2 position;
        
};