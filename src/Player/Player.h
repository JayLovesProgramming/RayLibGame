#pragma once

#include "raylib.h"
#include "Main.h"
#include <chrono>

struct Player
{
    Vector2 position;
    float speed;
    bool canJump;
    Texture2D sprite;
    // Destructor
    ~Player()
    {
        auto start = std::chrono::high_resolution_clock::now();
        UnloadTexture(sprite);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Destructor: Game unloaded successfully in " << duration.count() << " ms" << std::endl;
    }
};
// typedef struct Player Player; // For C compatability
