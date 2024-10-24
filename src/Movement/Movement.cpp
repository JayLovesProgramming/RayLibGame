#include "Movement.h"

WalkAnimation walkAnimation;

void HandleMovement(Player &player, float deltaTime)
{
    bool movingLeft = (IsKeyDown(KEY_LEFT) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_A);
    bool movingRight = (IsKeyDown(KEY_RIGHT) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_D);
    bool justStoppedMoving = (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D));

    if (justStoppedMoving)
    {
        walkAnimation.isRunning = false;
    }
    else if (movingLeft)
    {
        player.position.x -= PLAYER_HOR_SPD * deltaTime;
        walkAnimation.isRunning = true;
        if (player.sprite.width > 0) // Only negate if it's positive (facing right)
        {
            player.sprite.width = -player.sprite.width; // Flip sprite to face left
        }
    }
    else if (movingRight)
    {
        player.position.x += PLAYER_HOR_SPD * deltaTime;
        walkAnimation.isRunning = true;
        if (player.sprite.width <= 0) // Only negate if it's positive (facing right)
        {
            player.sprite.width = -player.sprite.width; // Flip sprite to face left
        }
    }
}
