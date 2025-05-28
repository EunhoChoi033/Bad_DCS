#include "countermeasures.hpp"

Countermeasures::Countermeasures() {

}

Countermeasures::Countermeasures(int id, int numEnemies, float entityWidth, float entityHeight) {
    this -> id = id;
    this -> numEnemies = numEnemies;
    this -> entityWidth = entityWidth;
    this -> entityHeight = entityHeight;
    chaffFlareSound = LoadSound("Sounds/Chaff_Flare_SFX.wav");
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
            if (it -> GetNumPositionsLeft() == 0 && it -> GetNumPositionsRight() == 0) {
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
        countermeasures.push_back(Flare(centerX, entityWidth, entityHeight, entityYPosition, WHITE, FLARE_HEALTH, 255.f / FLARE_HEALTH, FLARE_HORIZONTAL_VELOCITY, FLARE_VERTICAL_VELOCITY, FLARE_VERTICAL_ACCELERATION, INIT_HORIZONTAL_VARIATION, INIT_VERTICAL_VARIATION));
        PlaySound(chaffFlareSound);
    } else {
        countermeasures.push_back(Flare(centerX, entityWidth, 0, entityYPosition, WHITE, FLARE_HEALTH, 255.f / FLARE_HEALTH, FLARE_HORIZONTAL_VELOCITY, -FLARE_VERTICAL_VELOCITY, -FLARE_VERTICAL_ACCELERATION, INIT_HORIZONTAL_VARIATION, -INIT_VERTICAL_VARIATION));
    }
}
