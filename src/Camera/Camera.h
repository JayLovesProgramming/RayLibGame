#pragma once

#include "Player.h"
#include "Objects.h"

void UpdateCamera(Camera2D &camera, Player &player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
