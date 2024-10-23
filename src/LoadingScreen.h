#pragma once

#include "raylib.h"
#include "Debug.h"

float loadingProgress = 0.0f;
bool loadingComplete = !LOADING_SCREEN_ENABLED;
const float loadingSpeed = 0.005f;

class LoadingScreen
{
private:

public:
    void UpdateLoadingBar()
    {
        // Update loading progress
        if (!loadingComplete && LOADING_SCREEN_ENABLED)
        {
            loadingProgress += loadingSpeed;
            if (loadingProgress >= 1.0f)
            {
                loadingProgress = 1.0f;
                loadingComplete = true; // Set loading complete when progress reaches 100%
            }
        }
    }

    void DrawLoadingBar(int screenWidth, int screenHeight)
    {
        if (!loadingComplete && LOADING_SCREEN_ENABLED)
        {
            DrawRectangle(0, 0, 1000000, 1000000, GRAY);
            DrawText("Loading...", screenWidth / 2 - 50, screenHeight / 2 - 40, 20, DARKGRAY);
            DrawRectangle(screenWidth / 2 - 100, screenHeight / 2, 200, 20, LIGHTGRAY);
            DrawRectangle(screenWidth / 2 - 100, screenHeight / 2, (int)(200 * loadingProgress), 20, GREEN);
            // DrawText("Loading Complete!", screenWidth / 2 - 80, screenHeight / 2 + 30, 20, DARKGREEN);
        }
    }
};
