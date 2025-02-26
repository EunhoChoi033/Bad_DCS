#include "flare.hpp"

Flare::Flare(Vector2 initPosition, Color initColor, int initHealth, float healthMultiplier, float horizontalVariation, float verticalVariation, float verticalAcceleration, float entityHorizontalCompensation) {
    this -> currentPosition = initPosition;
    this -> color = initColor;
    this -> health = initHealth;
    this -> healthMultiplier = healthMultiplier;
    this -> xVelocity = horizontalVariation;
    this -> yVelocity = verticalVariation;
    this -> yAcceleration = verticalAcceleration;
    this -> entityHorizontalCompensation = entityHorizontalCompensation;
    positions.insert(positions.begin(), currentPosition);
    // run = true;
}

void Flare::Draw() {
    // DrawRectangle(position.x, position.y, 10, 10, color);
    cout << positions.size() << endl;
    for (int i = 0; i < (int)positions.size(); i++) {
        Vector2 currentPos = positions[i];
        color = Color{color.r, color.g, color.b, (unsigned char)(healthMultiplier * (health - i))};
        DrawRectangle(currentPos.x, currentPos.y, FLARE_SIZE, FLARE_SIZE, color);
    }
}

void Flare::Update() {
    if ((int)positions.size() == health) {
        positions.pop_back();
    }
    
    // for (int i = 0; i < (int)positions.size();) {
    //     Vector2 currentPos = positions[i];
    //     if ((currentPos.x + FLARE_SIZE) >= GetScreenWidth() || currentPos.x <= 0 || (currentPos.y - FLARE_SIZE) <= 0 || currentPos.y >= GetScreenHeight()) {
    //         positions.erase(positions.begin() + i);
    //         // cout << "ERASE" << endl;
    //         // i++;
    //     } else {
    //         i++;
    //     }
    // }

    // Vector2 lastPosition = positions[positions.size()];

    // if ((lastPosition.x + FLARE_SIZE) >= GetScreenWidth() || lastPosition.x <= 0 || (lastPosition.y - FLARE_SIZE) <= 0 || lastPosition.y >= GetScreenHeight()) {
    //     positions.clear();
    // }

    currentPosition.x += xVelocity;
    yVelocity += yAcceleration;
    currentPosition.y += yVelocity;
    positions.insert(positions.begin(), currentPosition);
}

int Flare::GetNumPositions() {
    return (int)positions.size();
}
