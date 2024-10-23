#include "WalkAndRunAnimations.h"

WalkAnimation walkAnimation;

void WalkAnimation::DebugWalkAnimation()
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

void WalkAnimation::DoWalkAnimation()
{
    // DebugWalkAnimation();
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
