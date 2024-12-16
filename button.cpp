#include "button.hpp"

Button::Button(Vector2 position, float width, float height, Color color) {
    this -> position = position;
    this -> width = width;
    this -> height = height;
    this -> color = color;
    thickness = 5.0f;

}

void Button::Draw() {
    Rectangle box = {position.x, position.y , width, height};
    DrawRectangleLinesEx(box, thickness, color);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed){
    Rectangle rect = {position.x, position.y, width, height};

    if (CheckCollisionPointRec(mousePos, rect) && mousePressed) {
        return true;
    } else {
        return false;
    }
}
