#pragma once
#include "Player/Player.h"

void UpdateGameCamera(Camera2D &camera, Player &player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
