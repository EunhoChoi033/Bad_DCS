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

    currentPositionRight = Vector2 {centerX + entityWidth/2 + xInitVariation, entityYPosition + entityHeight + yInitVariation};
    currentPositionLeft = Vector2 {centerX - entityWidth/2 - xInitVariation, entityYPosition + entityHeight + yInitVariation};
    
    positionsRight.insert(positionsRight.begin(), currentPositionRight);
    positionsLeft.insert(positionsLeft.begin(), currentPositionLeft);
}

void Flare::Draw() {
    for (int i = 0; i < (int)positionsRight.size(); i++) {
        Vector2 currentPosRight = positionsRight[i];
        color = Color{color.r, color.g, color.b, (unsigned char)(healthMultiplier * (health - i))};
        DrawRectangle(currentPosRight.x, currentPosRight.y, FLARE_SIZE, FLARE_SIZE, color);
    }
    for (int i = 0; i < (int)positionsLeft.size(); i++) {
        Vector2 currentPosLeft = positionsLeft[i];
        color = Color{color.r, color.g, color.b, (unsigned char)(healthMultiplier * (health - i))};
        DrawRectangle(currentPosLeft.x, currentPosLeft.y, FLARE_SIZE, FLARE_SIZE, color);
    }
}

void Flare::Update() {

    if ((int)positionsRight.size() == health) {
        positionsRight.pop_back();
    }
    if ((int)positionsLeft.size() == health) {
        positionsLeft.pop_back();
    }

    currentPositionRight.x += xVelocity;
    currentPositionLeft.x -= xVelocity;
    
    yVelocity += yAcceleration;
    currentPositionRight.y += yVelocity;
    currentPositionLeft.y += yVelocity;
    
    positionsRight.insert(positionsRight.begin(), currentPositionRight);
    positionsLeft.insert(positionsLeft.begin(), currentPositionLeft);
    
    Vector2 lastPositionRight = positionsRight[positionsRight.size() - 1];
    Vector2 lastPositionLeft = positionsLeft[positionsLeft.size() - 1];
    
    if ((lastPositionRight.x + FLARE_SIZE) >= GetScreenWidth() || lastPositionRight.x <= 0 || (lastPositionRight.y - FLARE_SIZE) <= 0 || lastPositionRight.y >= GetScreenHeight()) {
        positionsRight.clear();
    }
    if ((lastPositionLeft.x + FLARE_SIZE) >= GetScreenWidth() || lastPositionLeft.x <= 0 || (lastPositionLeft.y - FLARE_SIZE) <= 0 || lastPositionLeft.y >= GetScreenHeight()) {
        positionsLeft.clear();
    }

}

int Flare::GetNumPositionsRight() {
    return (int)positionsRight.size();
}

int Flare::GetNumPositionsLeft() {
    return (int)positionsLeft.size();
}
