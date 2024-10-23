#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

void UnloadGame(std::chrono::steady_clock::time_point start)
{
    // TODO: Measure the time it takes to unload
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Game unloaded successfully in " << duration.count() << " ms" << std::endl;
}

typedef struct Player
{
    Vector2 position;
    float speed;
    bool canJump;
    Texture2D sprite; // Add a Texture2D to hold the player sprite
    // Get the start time
    // Destructor
    ~Player()
    {
        auto start = std::chrono::high_resolution_clock::now();
        UnloadTexture(sprite);
        UnloadGame(start);
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

float loadingProgress = 0.0f;
const float loadingSpeed = 0.005f; // Adjust this value to control loading speed
bool loadingComplete = false;
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


