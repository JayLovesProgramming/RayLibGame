#include "Main.h"
#include "Debug.h"

#include "Audio/Music/Music.cpp"
#include "Movement/Jump.cpp"
#include "Movement/Movement.cpp"
#include "Animations/WalkAndRunAnimations.cpp"
#include "Camera/Camera.cpp"

#include "Utils/Utils.h" // TODO: Implement the above includes to use the header file and implement the CPP file in the CMakeLists.txt when it's ready

Texture2D groundTexture;
Texture2D backgroundTexture;
float backgroundScroll = 0;

void DrawEssentials(Rectangle destRec, Player &player, Vector2 origin, Texture2D groundTexture)
{
    for (int i = 0; i < envItemsLength; i++)
    {
        if (USE_CUSTOM_GROUND_TEXTURE)
        {
            EnvItem *ei = &envItems[i];
            if (ei->blocking)
            {
                Rectangle destGroundRec = {ei->rect.x, ei->rect.y, ei->rect.width, ei->rect.height};
                DrawTexture(groundTexture, destGroundRec.x, destGroundRec.y, WHITE);
            }
        }
        else
        {
            DrawRectangleRec(envItems[i].rect, envItems[i].color); // Ground surface rectangle
        }
    }
    destRec.x = player.position.x;
    destRec.y = player.position.y;
    DrawTexturePro(player.sprite, sourceRec, destRec, origin, (float)spriteRotation, WHITE);
    DrawCircleV(player.position, 8.0f, BLACK);
    walkAnimation.DrawWalkAnim();
}

// Checks if you are on top of a platform a.k.a a rectangle or platform
// TODO: Add more collision checks to check the bottom and sides of the rectangle so the player collides with the rectangle all round (a bit like super mario)
void CheckForCollisionCollide(Player &player, float deltaTime)
{
    // Collision detection with environment items
    bool onGround = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = &envItems[i];
        if (ei->blocking &&
            // CheckCollisionRecs(player.rect, ei.rect) &&
            ei->rect.x <= player.position.x &&
            ei->rect.x + ei->rect.width >= player.position.x &&
            ei->rect.y >= player.position.y &&
            ei->rect.y <= player.position.y + player.speed * deltaTime)
        {
            onGround = true;
            player.speed = 0.0f;
            player.position.y = ei->rect.y; // Snap player to the top of the obstacle
            break;
        }
    }

    if (onGround)
    {
        player.canJump = true; // Can jump again if hit obstacle
        return;
    }
    // Update player vertical position and apply gravity if not hitting an obstacle
    player.position.y += player.speed * deltaTime;
    player.speed += PLAYER_GRAVITY * deltaTime; // Apply gravity
    player.canJump = false;                     // Can't jump while falling
}

void DrawSkyBackground(float deltaTime)
{
    backgroundScroll -= 100 * (deltaTime * 1.1f);
    // Reset backgroundScroll to loop seamlessly
    if (backgroundScroll <= -backgroundTexture.width)
    {
        backgroundScroll += backgroundTexture.width;
    }
    else if (backgroundScroll >= backgroundTexture.width)
    {
        backgroundScroll -= backgroundTexture.width;
    }
    if (walkAnimation.isRunning)
    {
        backgroundScroll -= 1.1f;
    }
    else
    {
        backgroundScroll += 1.01f;
    }
    ClearBackground(PINK);
    DrawTextureEx(backgroundTexture, Vector2{backgroundScroll, 0}, 0.0f, 1.0f, WHITE);                               // Center instance
    DrawTextureEx(backgroundTexture, Vector2{backgroundScroll + backgroundTexture.width, 0}, 0.0f, 1.0f, WHITE);     // Right instance
    DrawTextureEx(backgroundTexture, Vector2{backgroundScroll - backgroundTexture.width, 0}, 0.0f, 1.0f, WHITE);     // Left instance
    DrawTextureEx(backgroundTexture, Vector2{backgroundScroll + 2 * backgroundTexture.width, 0}, 0.0f, 1.0f, WHITE); // Extra right instance
}

// Update player loop
void UpdatePlayer(Player &player, float deltaTime)
{
    HandleMovement(player, deltaTime);
    CheckForCollisionCollide(player, deltaTime);
    CheckForPlayerJump(player);
}

// Main update loop
void UpdateGameLoop(Player &player, float deltaTime)
{
    UpdatePlayer(player, deltaTime);
}

void InitalizeGame()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Randomize the seed
    InitWindow(screenWidth, screenHeight, "JAY");
    SetTraceLogLevel(7);
    SetExitKey(KEY_BACKSPACE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetWindowState(FLAG_VSYNC_HINT);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    // SetWindowState(FLAG_WINDOW_UNDECORATED);
    backgroundTexture = LoadTexture("assets/images/sky.png");

    if (USE_CUSTOM_GROUND_TEXTURE)
    {
        groundTexture = LoadTexture("assets/sprites/Brick_Block.png");
    }
}

// Program main entry point
int main(void)
{
    InitalizeGame();

    MusicPlayer musicPlayer = {};
    musicPlayer.StartMainGameMusic("assets/music/country.mp3");

    Texture2D playerTexture = LoadTexture("C:/Users/jayxw/Desktop/RayLibGame/assets/sprites/scarfy.png");
    frameWidth = playerTexture.width / 6;
    frameHeight = playerTexture.height;

    Vector2 origin = {static_cast<float>(frameWidth), static_cast<float>(frameHeight * (1.0f + PLAYER_ORIGIN_HEIGHT))}; // Set the origin to the center of width and bottom of the height
    sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};                                                    // Source rectangle (part of the texture to use for drawing)

    Player player = {0};
    player.position = Vector2{0, 0};
    player.speed = 0;
    player.canJump = false;
    player.sprite = playerTexture;

    Camera2D camera = {};
    camera.target = player.position;
    camera.offset = Vector2{screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(5000);

    // TODO: Use origin to calc properly
    Rectangle destRec = {screenWidth / 2.0f, screenHeight / 2.0f, frameWidth * 2.0f, frameHeight * 2.0f}; // by doing / 2 and * 2 here we can center the sprite with the circle
    destRec.width = destRec.width;
    destRec.height = destRec.height;

    // Main game loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        UpdateGameLoop(player, deltaTime);
        UpdateGameCamera(camera, player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        musicPlayer.MusicLoop();
        // Drawing
        BeginDrawing();
        DrawSkyBackground(deltaTime);
        BeginMode2D(camera);
        DrawEssentials(destRec, player, origin, groundTexture);
        EndMode2D();
        DrawText(TextFormat("FPS: %d", GetFPS()), 40, 40, 40, MAROON);
        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(backgroundTexture);
    UnloadTexture(playerTexture);
    UnloadTexture(groundTexture);
    CloseWindow();
    return 0;
}

// Something Amit on Twitch taught me, legend
// int a[] = {0, 1, 2}; // Declare an array 'a' with elements 0, 1, and 2.
// int b = 2[a];       // Equivalent to a[3], which is out of bounds.
// std::cout << b << std::endl;
