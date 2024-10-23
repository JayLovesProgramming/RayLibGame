#include "raylib.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>
#include "Debug.h"

float frameWidth;
float frameHeight;
Rectangle sourceRec;
bool isRunning = false;
int currentFrame = 0;
float walkSpeed = 0.2f;
static float elapsedTime = 0.0f;
const int maxFrames = 6;
float usedToBeDeltaTime = 0.1f;

void debugWalkAnimation()
{
    if (isRunning)
    {
        JPrint("Running");
    }
    else
    {
        JPrint("Not running");
    }
}

void walkAnimation()
{
    // debugWalkAnimation();
    if (!isRunning)
        currentFrame = 5; // Set to last frame if not running
    else if (isRunning)
    {
        // Use GetFrameTime() to adjust elapsed time
        elapsedTime += GetFrameTime(); // Get the time since the last frame

        // Check if the accumulated time is greater than the time per frame
        if (elapsedTime >= (walkSpeed * 4) / maxFrames) // Divide by maxFrames for smoother animation
        {
            currentFrame++;
            if (currentFrame >= maxFrames)
            {
                currentFrame = 0; // Reset to first frame
            }
            elapsedTime = 0.0f; // Reset elapsed time
        }
        sourceRec.x = (float)(currentFrame * frameWidth);
        // JPrint(currentFrame);
    } 
}
