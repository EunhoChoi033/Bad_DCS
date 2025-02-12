#include "countermeasures.hpp"

Countermeasures::Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight) {
    // active = true;
    this -> initPosition = initPosition;
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
            if (it -> getHealth() == 0) {
                it = countermeasures.erase(it);
            } else {
                it++;
            }
        }
    }
}

void Countermeasures::setNumEnemies(int newNumEnemies) {
    numEnemies = newNumEnemies;
}

void Countermeasures::AddFlares(Vector2 entityPosition) {
    int centerX = initPosition.x + (entityWidth/2);
    if (id = numEnemies) {
        countermeasures.push_back(Flare(Vector2 {centerX + entityWidth + INIT_VARIATION, initPosition.y + entityHeight + INIT_VARIATION}, WHITE, flareHealth));
    } else {
        // positions.push_back(Vector2 {initPosition.x - INIT_VARIATION, initPosition.y - INIT_VARIATION});
        countermeasures.push_back(Flare(Vector2 {centerX + entityWidth + INIT_VARIATION, initPosition.y + entityHeight + INIT_VARIATION}, WHITE, flareHealth));
    }
}

// bool Flares::getActive() {
//     return active;
// }
