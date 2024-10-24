#pragma once
#include <cstdlib> // Used for rand() in getRandomFloatValue() function

static constexpr float PLAYER_JUMP_MULTIPLAYER = 13.0f; // Just a multipler, nothing special to see here

const float getRandomFloatValue(int min, int max); // Currently used for the jump value
