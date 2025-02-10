#include "flares.hpp"

Flares::Flares(Vector2 initPosition, int id, int numEnemies, float entityWidth, float entityHeight) {
    // active = true;
    this -> initPosition = initPosition;
    this -> id = id;
    this -> numEnemies = numEnemies;
    int centerX = initPosition.x + (entityWidth/2);
    if (id = numEnemies) {
        // positions.push_back(Vector2 {initPosition.x + INIT_VARIATION, initPosition.y + INIT_VARIATION});
    } else {
        // positions.push_back(Vector2 {initPosition.x - INIT_VARIATION, initPosition.y - INIT_VARIATION});
    }
}

void Flares::Draw() {
    
}

void Flares::Update() {

}

// bool Flares::getActive() {
//     return active;
// }
