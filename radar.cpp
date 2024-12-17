#include "radar.hpp"

using namespace std;

Radar::Radar(Vector2 position, Color color) {
    this -> position = position;
    this -> color = color;
    radarFont = LoadFontEx("Fonts/Oxanium-SemiBold.ttf", 256, 0, 0);
    outerRadius = 100.0f;
    innerRadius = 20.0f;
    thickness = 5.0f;
    fadedColor = {color.r, color.g, color.b, (unsigned char)limiter(color.a - 225, 0 , 255)};
    grey = {29, 29, 27, 255};
    radarRangeX = GetScreenWidth() / 3;
    radarRangeY = 2 * GetScreenHeight();
    oneReturn = EnemyReturn({170, (GetScreenHeight() / 2.0f) + 50.0f}, color, radarFont);
}

Radar::Radar() {

}

// Radar::~Radar() {
    
// }

void Radar::Draw() {
    
    DrawCircle(position.x, position.y, outerRadius + 10.0f, fadedColor);
 
    DrawCircleSector(position, outerRadius + 6.0f, 20.0f, 60.0f, 128, YELLOW);
    DrawCircleSector(position, outerRadius + 2.0f, 20.0f, 60.0f, 128, grey);
    DrawCircleSector(position, outerRadius + 2.0f, 20.0f, 60.0f, 128, fadedColor);

    for (auto& enemyReturn: enemyReturns) {
        enemyReturn.Draw();
    }

    oneReturn.Draw();  
    
    DrawRing(position, outerRadius + 10.0f, outerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
    DrawRing(position, innerRadius + 10.0f, innerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
}  

void Radar::Update(Vector2 playerPos, vector<Enemy> enemies) {
    Rectangle radarRange = {playerPos.x - radarRangeX, playerPos.y, radarRangeX, -radarRangeY};
    enemyReturns.clear();
    
    for (auto& enemy: enemies) {
        if (CheckCollisionPointRec(enemy.position, radarRange)) {
            Vector2 distance = {position.x + outerRadius / (), position.y};
        }
    }
}

int Radar::limiter(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}