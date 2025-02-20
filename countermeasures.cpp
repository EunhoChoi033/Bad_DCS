#include "countermeasures.hpp"

Countermeasures::Countermeasures() {
    flareHealth = 17;
    coolingCooldown = 0;
}

Countermeasures::Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight)
{
    // active = true;
    this -> id = id;
    this -> numEnemies = numEnemies;
    this -> entityWidth = entityWidth;
    this -> entityHeight = entityHeight;
    // flareColor = Color{255, 255, 255, 255};
    flareHealth = 17;
    coolingCooldown = 0;
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
            if (it -> GetHealth() == 0) {
                it = countermeasures.erase(it);
            } else {
                it++;
            }
        }
    }
}

void Countermeasures::AddFlare(Vector2 entityPosition) {
    int centerX = entityPosition.x + (entityWidth/2);
    if (id == numEnemies) {
        countermeasures.push_back(Flare(Vector2 {centerX + entityWidth/2 + INIT_VARIATION, entityPosition.y + entityHeight + INIT_VARIATION}, WHITE, flareHealth, FLARE_HORIZONTAL_VARIATION, FLARE_VERTICAL_VARIATION));
    } else {
        // positions.push_back(Vector2 {initPosition.x - INIT_VARIATION, initPosition.y - INIT_VARIATION});
        countermeasures.push_back(Flare(Vector2 {centerX + entityWidth/2 + INIT_VARIATION, entityPosition.y + entityHeight + INIT_VARIATION}, WHITE, flareHealth, FLARE_HORIZONTAL_VARIATION, FLARE_VERTICAL_VARIATION));
    }
}

void Countermeasures::SetEntityHorizontalCompensation(float horizontalSpeed) {
    this -> entityHorizontalCompensation = horizontalSpeed;
}

// bool Flares::getActive() {
//     return active;
// }
