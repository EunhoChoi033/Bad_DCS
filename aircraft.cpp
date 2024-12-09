#include "aircraft.hpp"

Aircraft::Aircraft() {
    
    image = LoadTexture("Graphics/f_45.png");
    position.x = 100;
    position.y = 100;
}

Aircraft::~Aircraft() {
    UnloadTexture(image);
}