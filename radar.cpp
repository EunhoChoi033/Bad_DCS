#include "radar.hpp"

using namespace std;

Radar::Radar(Vector2 position, float playerWidth, Color color) {
    this -> position = position;
    this -> color = color;
    this -> playerWidth = playerWidth;
    radarFont = LoadFontEx("Fonts/Oxanium-SemiBold.ttf", 256, 0, 0);
    outerRadius = 100.0f;
    innerRadius = 20.0f;
    thickness = 5.0f;
    fadedColor = {color.r, color.g, color.b, (unsigned char)limiter(color.a - 225, 0 , 255)};
    grey = {29, 29, 27, 255};
    radarRangeX = GetScreenWidth() / 3;
    radarRangeY = 2 * GetScreenHeight();
    // oneReturn = EnemyReturn({170, (GetScreenHeight() / 2.0f) + 50.0f}, color, radarFont);
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

    // oneReturn.Draw();  
    
    DrawRing(position, outerRadius + 10.0f, outerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
    DrawRing(position, innerRadius + 10.0f, innerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
}  

void Radar::Update(Vector2 playerPos, vector<Enemy> enemies) {
    Rectangle radarRange = {playerPos.x - (radarRangeX / 2) + (playerWidth / 2), playerPos.y, radarRangeX, -radarRangeY};
    // DrawRectangle(playerPos.x - (radarRangeX / 2) + (playerWidth / 2), playerPos.y - radarRangeY, radarRangeX, radarRangeY, WHITE);
    enemyReturns.clear();
    
    // enemyReturns.push_back(EnemyReturn({170, (GetScreenHeight() / 2.0f) + 50.0f}, color, radarFont));

    for (auto& enemy: enemies) {
        if (CheckCollisionRecs(enemy.getRect(), radarRange)) {
            Vector2 radarPos = {position.x + (((2 * outerRadius) / (radarRangeX)) * (enemy.position.x - playerPos.x)), position.y + (((2 * outerRadius) / (radarRangeY)) * (enemy.position.y - playerPos.y))};
            cout << enemyReturns.size() << endl;
            enemyReturns.push_back(EnemyReturn(radarPos, color, radarFont));
        }
        cout << "None" << endl;
    }
}

int Radar::limiter(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}