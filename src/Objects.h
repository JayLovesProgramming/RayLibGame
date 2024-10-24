#pragma once

static constexpr int DEFAULT_MAP_X_POS = -1000; // ! Set DEFAULT_MAP_POS back to 0 when debugging camera
static constexpr int DEFAULT_MAP_Y_POS = 900;
static constexpr int DEFAULT_MAP_HEIGHT = 2000;
static constexpr int DEFAULT_MAP_WIDTH = 13000;
static constexpr int DEFAULT_PLATFORM_X_POS = (DEFAULT_MAP_X_POS / 6) + 1000;

struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
};
// typedef struct EnvItem EnvItem; // For C compatability

EnvItem envItems[] = {
    {{DEFAULT_PLATFORM_X_POS, 400, 600, 10}, 1, BLUE},  
    {{DEFAULT_PLATFORM_X_POS + 700, 420, 400, 10}, 1, GREEN},  
    {{DEFAULT_MAP_X_POS, DEFAULT_MAP_Y_POS, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT}, 1, RED},  
};

int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
