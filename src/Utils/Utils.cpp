#include "Utils.h"

const float getRandomFloatValue(int min, int max)
{
    return (float)(rand() % (min - max + 1) + min) * PLAYER_JUMP_MULTIPLAYER;
};
