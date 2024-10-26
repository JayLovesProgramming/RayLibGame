
#pragma once

#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include "Objects.h"
#include "Player/Player.h"

// TODO: Make gravity value reverse
// Learn: Difference between defining stuff like below or using const float or const bool for example
static constexpr float spriteRotation = 0.0f;
static constexpr float PLAYER_JUMP_SPD = 350.0f; 
static constexpr float PLAYER_HOR_SPD = 200.0f; 
static constexpr bool SHOULD_W_KEY_JUMP = false;
static constexpr bool ARE_ARROWS_ACTIVATED = true;
static constexpr int PLAYER_GRAVITY = 800; // Lower values = floater
static constexpr int JUMP_MIN = 30;
static constexpr int JUMP_MAX = 36;
static int screenWidth = 1920;
static int screenHeight = 1080;

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, Rectangle sourceRec);
