#include "flare.hpp"

Flare::Flare(int centerX, float entityWidth, float entityHeight, float entityYPosition, Color initColor, int initHealth, float healthMultiplier, float horizontalVelocity, float verticalVelocity, float verticalAcceleration, float xInitVariation, float yInitVariation) {
    this -> centerX = centerX;
    this -> entityWidth = entityWidth;
    this -> entityHeight = entityHeight;
    this -> entityYPosition = entityYPosition;
    this -> color = initColor;
    this -> health = initHealth;
    this -> healthMultiplier = healthMultiplier;
    this -> xVelocity = horizontalVelocity;
    this -> yVelocity = verticalVelocity;
    this -> yAcceleration = verticalAcceleration;
    this -> xInitVariation = xInitVariation;
    this -> yInitVariation = yInitVariation;

    currentPosition = Vector2 {centerX + entityWidth/2 + xInitVariation, entityYPosition + entityHeight + yInitVariation};
    // currentPositionLeft = Vector2 {centerX - entityWidth/2 - initVariation, entityYPosition + entityHeight + initVariation};
    
    positions.insert(positions.begin(), currentPosition);
    // positions.insert(positions.begin(), currentPositionLeft);
}

void Flare::Draw() {
    for (int i = 0; i < (int)positions.size(); i++) {
        Vector2 currentPos = positions[i];
        color = Color{color.r, color.g, color.b, (unsigned char)(healthMultiplier * (health - i))};
        DrawRectangle(currentPos.x, currentPos.y, FLARE_SIZE, FLARE_SIZE, color);
        DrawRectangle(centerX - (currentPos.x - centerX), currentPos.y, FLARE_SIZE, FLARE_SIZE, color);
    }
}

void Flare::Update() {
    if ((int)positions.size() == health) {
        positions.pop_back();
    }

    currentPosition.x += xVelocity;
    // currentPositionLeft.x -= xVelocity;
    
    yVelocity += yAcceleration;
    currentPosition.y += yVelocity;

    // currentPositionLeft.y += yVelocity;

    positions.insert(positions.begin(), currentPosition);
    // positions.insert(positions.begin(), currentPositionLeft);
    
    Vector2 lastPosition = positions[positions.size() - 1];
    
    if ((lastPosition.x + FLARE_SIZE) >= GetScreenWidth() || lastPosition.x <= 0 || (lastPosition.y - FLARE_SIZE) <= 0 || lastPosition.y >= GetScreenHeight()) {
        positions.clear();
    }

}

int Flare::GetNumPositions() {
    return (int)positions.size();
}
