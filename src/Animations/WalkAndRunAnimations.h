#pragma once

#include "raylib.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>
#include "Debug.h"

float frameWidth;
float frameHeight;
Rectangle sourceRec;

class WalkAnimation
{
private:
    float elapsedTime = 0.0f;
    const int maxFrames = 6;

    void DebugWalkAnimation();

public:
    bool isRunning = false;
    int currentFrame = 0;
    float walkSpeed = 0.2f;

    void DrawWalkAnim();
};
