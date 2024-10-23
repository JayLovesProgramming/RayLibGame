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
#define JAY_WHITE      CLITERAL(Color){ 255, 255, 255, 235 }
static const float PLAYER_JUMP_MULTIPLAYER_JAY = 13.0f; // Just a multipler, nothing special to see here
static constexpr int JUMP_MIN = 30;
static constexpr int JUMP_MAX = 36;
static constexpr int DEFAULT_MAP_X_POS = -5000; // ! Set DEFAULT_MAP_POS back to 0 when debugging camera
static constexpr int DEFAULT_MAP_Y_POS = 500;
static constexpr int DEFAULT_MAP_HEIGHT = 5000;
static constexpr int DEFAULT_MAP_WIDTH = 13000;

static constexpr int DEFAULT_PLATFORM_X_POS = (DEFAULT_MAP_X_POS / 6) + 1000;

MusicPlayer musicPlayer;
// LoadingScreen loadingScreen;

void UnloadGame(Texture2D sprite)
{
    auto start = std::chrono::high_resolution_clock::now();

    UnloadTexture(sprite);
    musicPlayer.UnloadMusicPlayer();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Destructor: Game unloaded successfully in " << duration.count() << " ms" << std::endl;
}

struct Player
{
    Vector2 position;
    Texture2D sprite; 
    float speed;
    bool canJump;
    // Destructor
    ~Player()
    {
        UnloadGame(sprite);
    }
};
// typedef struct Player Player; // For C compatability

struct EnvItem
{
    Rectangle rect;
    Color color;
    int blocking;
};
// typedef struct EnvItem EnvItem; // For C compatability

EnvItem envItems[] = {
    {{DEFAULT_PLATFORM_X_POS, 400, 600, 10}, 1, BLUE},  
    {{DEFAULT_PLATFORM_X_POS + 700, 420, 400, 10}, 1, GREEN},  
    {{DEFAULT_MAP_X_POS, DEFAULT_MAP_Y_POS, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT}, 1, RED},  
};

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


