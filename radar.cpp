#include "radar.hpp"

using namespace std;

Radar::Radar(Vector2 position, Vector2 initPlayerPos, float playerWidth, float playerHeight, Color color, Sound radarPing, vector<Enemy> enemies) {
    this -> position = position;
    this -> color = color;
    this -> playerWidth = playerWidth;
    this -> playerHeight = playerHeight;
    this -> radarPing = radarPing;
    this -> initPlayerPos = initPlayerPos;
    this -> enemies = enemies;
    selectedEnemy = -1;
    planeImage = LoadTexture("Graphics/radar_jet.png");
    radarFont = LoadFontEx("Fonts/Oxanium-SemiBold.ttf", 256, 0, 0);
    missileLockVWS = LoadSound("Sounds/missile_lock_VWS.wav");
    missileLocking = LoadMusicStream("Sounds/missile_locking.mp3");
    SetSoundVolume(missileLockVWS, 1.0f);
    SetMusicVolume(missileLocking, 1.0f);
    PlayMusicStream(missileLocking);
    outerRadius = 100.0f;
    innerRadius = 20.0f;
    thickness = 2.0f;
    fadedColor = {color.r, color.g, color.b, (unsigned char)limiter(color.a - 225, 0 , 255)};
    grey = {29, 29, 27, 255};
    radarRangeX = GetScreenWidth() / 2;
    radarRangeY =  1.5 * GetScreenHeight();
    radarUpdateCooldown = 0.0;
    radarReturnSelectCooldown = 0.0;
    missileLockMessageCooldown = 0.0;
}

Radar::Radar() {
    // missileLocking = LoadMusicStream("Sounds/missile_locking.mp3");
    // SetMusicVolume(missileLocking, 1.0f);
    // PlayMusicStream(missileLocking);
}

Radar::~Radar() {
//     UnloadMusicStream(missileLocking);
}

void Radar::Draw() {
    
    DrawCircle(position.x, position.y, outerRadius + 10.0f, fadedColor);
 
    // DrawCircleSector(position, outerRadius + 6.0f, 20.0f, 60.0f, 128, YELLOW);
    // DrawCircleSector(position, outerRadius + 2.0f, 20.0f, 60.0f, 128, grey);
    // DrawCircleSector(position, outerRadius + 2.0f, 20.0f, 60.0f, 128, fadedColor);

    for (auto& enemyReturn: enemyReturns) {
        enemyReturn.Draw();
    }

    for (auto& missile: missiles) {
        missile.Draw();
    }

    DrawRing(position, outerRadius + 10.0f, outerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
    DrawRing(position, innerRadius + 10.0f, innerRadius + thickness + 10.0f, 0.0f, 360.0f, 128, color);
    DrawTextureV(planeImage, {position.x - (planeImage.width / 2), position.y - (planeImage.height / 2)}, WHITE);
}  

void Radar::Update(Vector2 playerPos, vector<Enemy> enemies) {
    if (missiles.size() > 0) {
        for (auto& missile: missiles) {
            // Enemy enemyTargeting = enemies[0];
            // for (int i = 0; i < (int)enemies.size(); i++) {
            //     if (enemies[i].getEnemyNum() == missile.getId()) {
            //         enemyTargeting = enemies[i];
            //     }
            // }
            Enemy enemyTargeting = findEnemy(missile);
            cout << "Tracking Enemy# " << enemyTargeting.getEnemyNum() << " at x position " << enemyTargeting.getEnemyXPos() << " and y position " << enemyTargeting.getEnemyYPos() << endl;
            missile.Update({enemyTargeting.getEnemyXPos(), enemyTargeting.getEnemyYPos()}, playerWidth, playerHeight);
        }
    }

    if (GetTime() - radarUpdateCooldown > 0.6) {                
        Rectangle radarRange = {playerPos.x - (radarRangeX / 2) + (playerWidth / 2), playerPos.y - radarRangeY + (playerHeight / 2), radarRangeX, radarRangeY};
        enemyReturns.clear();

        // DrawRectangleRec(radarRange, RED);

        for (auto& enemy: enemies) {
            if (CheckCollisionRecs(enemy.getRect(), radarRange)) {
                Vector2 actualDistance = {enemy.getEnemyXPos() - playerPos.x, enemy.getEnemyYPos() - playerPos.y};
                float actualDistanceLength = sqrt((actualDistance.x * actualDistance.x) + (actualDistance.y * actualDistance.y));
                float scaleDownX = (outerRadius - innerRadius) / (radarRangeX / 2);
                float scaleDownY = (outerRadius - innerRadius) / radarRangeY;
                float innerCircleAdjust = 20 / actualDistanceLength;

                Vector2 radarPos = {(position.x + actualDistance.x * scaleDownX) + (innerCircleAdjust * actualDistance.x), (position.y + actualDistance.y * scaleDownY) + (innerCircleAdjust * actualDistance.y)};
                float radarDistanceLength = hypot(radarPos.x - position.x, radarPos.y - position.y);

                if (radarDistanceLength <= outerRadius) {
                    if (enemy.getEnemyNum() == selectedEnemy) {
                        enemyReturns.push_back(EnemyReturn(radarPos, RED, radarFont, enemy.getEnemyNum()));
                        cout << "Enemy Return: " << enemy.getEnemyNum() << endl;
                    } else {
                    enemyReturns.push_back(EnemyReturn(radarPos, color, radarFont, enemy.getEnemyNum()));
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
        if (enemyReturns.size() == 0) {
            selectedEnemy = -1;
        }
        
        for (auto& enemyReturn: enemyReturns) {
            if (!enemyNumInList(enemyReturns, selectedEnemy)) {
                selectedEnemy = -1;
            }
            if (enemyReturn.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                if (enemyReturn.getEnemyReturnNum() == selectedEnemy) {
                    enemyReturn.setColor(color);
                    selectedEnemy = -1;
                } else {
                enemyReturn.setColor(RED);
                selectedEnemy = enemyReturn.getEnemyReturnNum();
                // cout << "Selected: " << selectedEnemy << endl;
                }
                radarReturnSelectCooldown = GetTime();
            }
        }
    }

    if (IsKeyPressed(KEY_M) && selectedEnemy != -1) {
        missiles.push_back(Missile(playerPos, 3.0, selectedEnemy));
        cout << "Missile Launched at Enemy #" << selectedEnemy << endl;
        selectedEnemy = -1;
    }

    if (selectedEnemy != -1) {
        // PlaySound(missileLockVWS);
        UpdateMusicStream(missileLocking);
        // Locking ~0.96 seconds

        // missileLockMessageCooldown = 1.0;
        if (GetTime() - missileLockMessageCooldown >= 1.0 && missileLockMessageCooldown != 0) {
            PlaySound(missileLockVWS);
            missileLockMessageCooldown = 0;
        }

    } else {
        SeekMusicStream(missileLocking, 0.0f);
        missileLockMessageCooldown = GetTime();
    }
}

bool Radar::enemyNumInList(vector<EnemyReturn> enemyReturns, int enemyNum) {
    for (auto& enemyReturn: enemyReturns) {
        if (enemyReturn.getEnemyReturnNum() == enemyNum) {
            return true;
        }
    }
    return false;
}
Enemy Radar::findEnemy(Missile missile) {
    Enemy enemyTarget = enemies[0];
    for (int i = 0; i < (int)enemies.size(); i++) {
        if (enemies[i].getEnemyNum() == missile.getId()) {
            enemyTarget = enemies[i];
        }
    }
    return enemyTarget;
}

void Radar::clearMissiles() {
    missiles.clear();
}

void Radar::setSelectedEnemy(int newSelectedEnemy) {
    selectedEnemy = newSelectedEnemy;
}

int Radar::limiter(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}