#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Music.h"

const float rotation = 0.0f;

// TODO: Make gravity value reverse
// Learn: Difference between defining stuff like below or using const float or const bool for example
#define PLAYER_GRAVITY 800 // Lower values = floater
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f
#define SHOULD_W_KEY_JUMP false
#define ARE_ARROWS_ACTIVATED true
// #define ARE_ARROWS_SUPER_POWERS_READY false
#define JUMP_MIN 30
#define JUMP_MAX 35
#define PLAYER_JUMP_MULTIPLAYER_JAY 13.0f // Just a multipler, nothing special to see here
#define JAY_WHITE      CLITERAL(Color){ 255, 255, 255, 235 }

MusicPlayer musicPlayer;

void UnloadGame(Texture2D sprite)
{
    auto start = std::chrono::high_resolution_clock::now();

    UnloadTexture(sprite);
    musicPlayer.UnloadMusicPlayer();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Destructor: Game unloaded successfully in " << duration.count() << " ms" << std::endl;
}

typedef struct Player
{
    Vector2 position;
    float speed;
    bool canJump;
    Texture2D sprite; 
    // Destructor
    ~Player()
    {
        UnloadGame(sprite);
    }
} Player;

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

EnvItem envItems[] = {
        {{0,
          400,
          13000,
          200},
         1,
         BLUE},
        {{300,
          200,
          100,
          10},
         1,
         BLUE},
        {{
             650, // Lower value goes left, higher value goes right meaning it's the X axis
             300, // Lower value goes up, higher value goes down meaning it's the Y axis
             200, // The width of the rect
             10   // The height of the rect
         },
         1,
         RED},
        {{950,
          300,
          100,
          10},
         1,
         RED}};

int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

const float getRandomFloatValue(int min, int max)
{
    return (float)(rand() % (min - max + 1) + min) * PLAYER_JUMP_MULTIPLAYER_JAY;
};

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, Rectangle sourceRec);
void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height); // The camera we are using











// TODO: Implement these cameras when the game is at a good playing stage
// void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
// void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
// void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);
// void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height);


