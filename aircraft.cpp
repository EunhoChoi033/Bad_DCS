#include "aircraft.hpp"

Aircraft::Aircraft() {
    image = LoadTexture("Graphics/jet.png");
    image.height = 100;
    image.width = 100;
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;
}

Aircraft::~Aircraft() {
    UnloadTexture(image);
}

void Aircraft::Draw() {
    DrawTextureV(image, position, WHITE);
}