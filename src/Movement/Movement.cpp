#include "Movement.h"

WalkAnimation walkAnimation;

void HandleMovement(Player &player, float deltaTime)
{
    bool movingLeft = (IsKeyDown(KEY_LEFT) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_A);
    bool movingRight = (IsKeyDown(KEY_RIGHT) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_D);
    // bool movingDown = (IsKeyDown(KEY_DOWN) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_S);
    // bool movingUp = (IsKeyDown(KEY_UP) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_W);

    bool justStoppedMoving = (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D));

    if (justStoppedMoving)
    {
        walkAnimation.isRunning = false;
    }

    if (movingLeft)
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

    // else if (movingDown)
    // {
    //     std::cout << "Walking down..." << std::endl;
    //     player.position.y += PLAYER_HOR_SPD * deltaTime;
    //     walkAnimation.isRunning = true;
    //     // if (player.sprite.height > 0) // Only negate if it's positive (facing right)
    //     // {
    //     //     player.sprite.height = -player.sprite.height; // Flip sprite to face left
    //     // }
    // }
    // else if (movingUp)
    // {
    //     std::cout << "Walking up..." << std::endl;
    //     player.position.y -= PLAYER_HOR_SPD * deltaTime;
    //     walkAnimation.isRunning = true;
    // }
}
