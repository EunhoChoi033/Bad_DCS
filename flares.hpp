#pragma once
#include <raylib.h>

class Flares{
    public:
        Flares(Vector2 position, int id);
        void Draw();
        void Update();
        bool getActive();

    private:
        Vector2 position;
        bool active;
        int id;
};