#include "main.h"
#include "Screen.h"
#include "Debug.h"
#include "Audio/Music/Music.cpp"
#include "Utils/Utils.cpp"
#include "Movement/Jump.cpp"
#include "Movement/Movement.cpp"
#include "Animations/WalkAndRunAnimations.cpp"

void DrawEssentials(Rectangle destRec, Player &player, Vector2 origin)
{
    for (int i = 0; i < envItemsLength; i++)
    {
        DrawRectangleRec(envItems[i].rect, envItems[i].color); // Ground surface rectangle
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

void UpdateCamera(Camera2D &camera, Player &player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
{
    camera.target = player.position;
    camera.offset = Vector2{width / 2.0f, height / 2.0f};
    float minX = 0, minY = 0, maxX = 0, maxY = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = &envItems[i];
        if (ei->blocking)
        {
            minX = fminf(ei->rect.x, minX);
            maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
            minY = fminf(ei->rect.y, minY);
            maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
        }
    }
    // Clamp camera within the environment
    if (camera.target.x < minX + width / 2)
        camera.target.x = minX + width / 2;
    if (camera.target.x > maxX - width / 2)
        camera.target.x = maxX - width / 2;
    if (camera.target.y < minY + height / 2)
        camera.target.y = minY + height / 2;
    if (camera.target.y > maxY - height / 2)
        camera.target.y = maxY - height / 2;

    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
    // Use std::clamp instead here
    if (camera.zoom >= 1.26f)
        camera.zoom = 1.26f;
    else if (camera.zoom < 0.54f)
        camera.zoom = 0.54f;
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
    // Randomize the seed
    srand(static_cast<unsigned int>(time(nullptr)));
    // Initialization
    InitWindow(screenWidth, screenHeight, "JAY");
    SetTraceLogLevel(7);
    SetExitKey(KEY_BACKSPACE);
    SetWindowState(FLAG_VSYNC_HINT);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    // SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
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
    
    Vector2 origin = {static_cast<float>(frameWidth), static_cast<float>(frameHeight * 1.2)}; // Set the origin to the center of width and bottom of the height
    sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight}; // Source rectangle (part of the texture to use for drawing)

    Player player = {0};
    player.position = Vector2{0, 280};
    player.speed = 0;
    player.canJump = false;
    player.sprite = playerTexture;

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = Vector2{screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(5000);
    
    // TODO: Use origin to calc properly
    Rectangle destRec = {screenWidth / 2.0f, screenHeight / 2.0f, frameWidth * 2.0f, frameHeight * 2.0f}; // Destination rectangle (screen rectangle where drawing part of texture)
    destRec.width = destRec.width / 1.4;
    destRec.height = destRec.height / 1.4;

    // Main game loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        UpdateGameLoop(player, deltaTime);
        UpdateCamera(camera, player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        musicPlayer.MusicLoop();
        // Drawing
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        DrawEssentials(destRec, player, origin);
        EndMode2D();
        DrawText(TextFormat("FPS: %d", GetFPS()), 40, 40, 40, MAROON);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}

// Something Amit on Twitch taught me, legend
// int a[] = {0, 1, 2}; // Declare an array 'a' with elements 0, 1, and 2.
// int b = 2[a];       // Equivalent to a[3], which is out of bounds.
// std::cout << b << std::endl;
