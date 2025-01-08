#include "radar.hpp"

using namespace std;

Radar::Radar(Vector2 position, Vector2 initPlayerPos, float playerWidth, float playerHeight, Color color, Sound radarPing) {
    this -> position = position;
    this -> color = color;
    this -> playerWidth = playerWidth;
    this -> playerHeight = playerHeight;
    this -> radarPing = radarPing;
    this -> initPlayerPos = initPlayerPos;
    selectedEnemy = -1;
    planeImage = LoadTexture("Graphics/radar_jet.png");
    radarFont = LoadFontEx("Fonts/Oxanium-SemiBold.ttf", 256, 0, 0);
    outerRadius = 100.0f;
    innerRadius = 20.0f;
    thickness = 2.0f;
    fadedColor = {color.r, color.g, color.b, (unsigned char)limiter(color.a - 225, 0 , 255)};
    grey = {29, 29, 27, 255};
    radarRangeX = GetScreenWidth() / 2;
    radarRangeY =  1.5 * GetScreenHeight();
    radarUpdateCooldown = 0.0;
    radarReturnSelectCooldown = 0.0;

    // oneMissile = Missile({initPlayerPos.x + (playerWidth / 2), initPlayerPos.y}, 2.0f, 0);
}

Radar::Radar() {

}

// Radar::~Radar() {
    
// }

void Radar::Draw() {
    
    DrawCircle(position.x, position.y, outerRadius + 10.0f, fadedColor);
 
    // DrawCircleSector(position, outerRadius + 6.0f, 20.0f, 60.0f, 128, YELLOW);
    // DrawCircleSector(position, outerRadius + 2.0f, 20.0f, 60.0f, 128, grey);
    // DrawCircleSector(position, outerRadius + 2.0f, 20.0f, 60.0f, 128, fadedColor);

    for (auto& enemyReturn: enemyReturns) {
        enemyReturn.Draw();
    }
    DrawRing(position, outerRadius + 10.0f, outerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
    DrawRing(position, innerRadius + 10.0f, innerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
    DrawTextureV(planeImage, {position.x - (planeImage.width / 2), position.y - (planeImage.height / 2)}, WHITE);

    // oneMissile.Draw();
}  

void Radar::Update(Vector2 playerPos, vector<Enemy> enemies) {
    if (GetTime() - radarUpdateCooldown > 0.75) {
        Rectangle radarRange = {playerPos.x - (radarRangeX / 2) + (playerWidth / 2), playerPos.y - radarRangeY + (playerHeight / 2), radarRangeX, radarRangeY};
        enemyReturns.clear();

        // DrawRectangleRec(radarRange, RED);

        for (auto& enemy: enemies) {
            if (CheckCollisionRecs(enemy.getRect(), radarRange)) {
                Vector2 actualDistance = {enemy.position.x - playerPos.x, enemy.position.y - playerPos.y};
                float actualDistanceLength = sqrt((actualDistance.x * actualDistance.x) + (actualDistance.y * actualDistance.y));
                float scaleDownX = (outerRadius - innerRadius) / (radarRangeX / 2);
                float scaleDownY = (outerRadius - innerRadius) / radarRangeY;
                float innerCircleAdjust = 20 / actualDistanceLength;

                Vector2 radarPos = {(position.x + actualDistance.x * scaleDownX) + (innerCircleAdjust * actualDistance.x), (position.y + actualDistance.y * scaleDownY) + (innerCircleAdjust * actualDistance.y)};
                float radarDistanceLength = hypot(radarPos.x - position.x, radarPos.y - position.y);

                if (radarDistanceLength <= outerRadius) {
                    if (enemy.enemyNum == selectedEnemy) {
                        enemyReturns.push_back(EnemyReturn(radarPos, RED, radarFont, enemy.enemyNum));
                    } else {
                    enemyReturns.push_back(EnemyReturn(radarPos, color, radarFont, enemy.enemyNum));
                    }
                }
            }
        }
        
        if (enemyReturns.size() > 0) {
            PlaySound(radarPing);
        }

        radarUpdateCooldown = GetTime();
    }
    
    if (GetTime() - radarReturnSelectCooldown >= 0.1f) {
        for (auto& enemyReturn: enemyReturns) {
            if (enemyReturn.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                enemyReturn.setColor(RED);
                selectedEnemy = enemyReturn.enemyNum;
                radarReturnSelectCooldown = GetTime();
            }
        }
    }

    // int missileID = oneMissile.getId();
    // auto it = find_if(enemies.begin(), enemies.end(), [missileID](const Enemy& enemies) {
    //     return enemies.enemyNum == missileID;
    // });
    // oneMissile.Update(it -> position, it -> image.width, it -> image.height);
}

int Radar::limiter(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}