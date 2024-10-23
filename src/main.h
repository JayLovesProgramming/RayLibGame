#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Objects.h"

// TODO: Make gravity value reverse
// Learn: Difference between defining stuff like below or using const float or const bool for example
static constexpr float spriteRotation = 0.0f;
static constexpr float PLAYER_JUMP_SPD = 350.0f; 
static constexpr float PLAYER_HOR_SPD = 200.0f; 
static constexpr float PLAYER_JUMP_MULTIPLAYER_JAY = 13.0f; // Just a multipler, nothing special to see here
static constexpr bool SHOULD_W_KEY_JUMP = false;
static constexpr bool ARE_ARROWS_ACTIVATED = true;
static constexpr int PLAYER_GRAVITY = 800; // Lower values = floater
static constexpr int JUMP_MIN = 30;
static constexpr int JUMP_MAX = 36;

const float getRandomFloatValue(int min, int max);
void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, Rectangle sourceRec);
void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height); // The camera we are using











// TODO: Implement these cameras when the game is at a good playing stage
// void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
// void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
// void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
// void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);


