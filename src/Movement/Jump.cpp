#include "Jump.h"

// Jumping Logic. Press space bar or the up arrow (if the arrows are activated via the defined variable) to jump - checks that we are on a surface before we can jump again
void CheckForPlayerJump(Player &player)
{
    if ((IsKeyDown(KEY_SPACE) || (IsKeyDown(KEY_UP) && ARE_ARROWS_ACTIVATED) || (IsKeyDown(KEY_W) && SHOULD_W_KEY_JUMP)) && player.canJump)
    {
        float jumpValue = getRandomFloatValue(JUMP_MIN, JUMP_MAX); // Gets a random float value that is randomized between JUMP_MIN and JUMP_MAX
        player.speed = -jumpValue;                                 // Makes the character jump
        // player.canJump = false; // ! Seems to not be needed but could be needed in the future when adding super powers etc. canJump gets reset when we touch the ground
    }
}

