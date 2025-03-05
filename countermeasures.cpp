#include "countermeasures.hpp"

Countermeasures::Countermeasures() {

}

Countermeasures::Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight) {
    this -> id = id;
    this -> numEnemies = numEnemies;
    this -> entityWidth = entityWidth;
    this -> entityHeight = entityHeight;
}

void Countermeasures::Draw() {
    if (countermeasures.size() > 0) { 
        for (auto it = countermeasures.begin(); it != countermeasures.end();) {
            it -> Draw();
            it++;
        }
    }
}

void Countermeasures::Update() {
    if (countermeasures.size() > 0) { 
        for (auto it = countermeasures.begin(); it != countermeasures.end();) {
            it -> Update();
            if (it -> GetNumPositions() == 0) {
                it = countermeasures.erase(it);
            } else {
                it++;
            }
        }
    }
}

void Countermeasures::AddFlare(Vector2 entityPosition) {
    int centerX = entityPosition.x + (entityWidth/2);
    float entityYPosition = entityPosition.y;
    if (id == numEnemies) {
        /* Vector2 {centerX + entityWidth/2 + INIT_VARIATION, entityPosition.y + entityHeight + INIT_VARIATION}*/
        countermeasures.push_back(Flare(centerX, entityWidth, entityHeight, entityYPosition, WHITE, FLARE_HEALTH, 255.f / FLARE_HEALTH, FLARE_HORIZONTAL_VELOCITY, FLARE_VERTICAL_VELOCITY, FLARE_VERTICAL_ACCELERATION, INIT_VARIATION));
    } else {
        // positions.push_back(Vector2 {initPosition.x - INIT_VARIATION, initPosition.y - INIT_VARIATION});
        countermeasures.push_back(Flare(centerX, entityWidth, entityHeight, entityYPosition, WHITE, FLARE_HEALTH, 255.f / FLARE_HEALTH, FLARE_HORIZONTAL_VELOCITY, FLARE_VERTICAL_VELOCITY, FLARE_VERTICAL_ACCELERATION, INIT_VARIATION));
    }
}

// void Countermeasures::SetEntityHorizontalCompensation(float horizontalSpeed) {
//     this -> entityHorizontalCompensation = horizontalSpeed;
// }

// bool Flares::getActive() {
//     return active;
// }
