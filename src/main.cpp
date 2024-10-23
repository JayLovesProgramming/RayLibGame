#include "main.h"
#include "WalkAndRunAnimations.h"
#include "Screen.h"
#include "Debug.h"
#include "Levels.h"

// Main update loop
void updateLoop()
{
    updateScreen();
}

// Jumping logic
void playerJump(Player *player)
{
    if ((IsKeyDown(KEY_SPACE) || (IsKeyDown(KEY_UP) && ARE_ARROWS_ACTIVATED) || (IsKeyDown(KEY_W) && SHOULD_W_KEY_JUMP)) && player->canJump)
    {
        player->canJump = false;
        float jumpValue = getRandomFloatValue(JUMP_MIN, JUMP_MAX);
        std::cout << "Jump value: " << jumpValue << std::endl;
        player->speed = -jumpValue; // Apply jump speed
    }
}

void collisionCheck(Player *player, float deltaTime)
{
     // Collision detection with environment items
    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = &envItems[i];
        if (ei->blocking && 
        // CheckCollisionRecs(player->rect, ei->rect) &&
            ei->rect.x <= player->position.x &&
            ei->rect.x + ei->rect.width >= player->position.x &&
            ei->rect.y >= player->position.y &&
            ei->rect.y <= player->position.y + player->speed * deltaTime)
        {
            hitObstacle = true;
            player->speed = 0.0f;
            player->position.y = ei->rect.y; // Snap player to the top of the obstacle
            break;
        }
    }
    // Update player vertical position and apply gravity if not hitting an obstacle
    if (!hitObstacle)
    {
        player->position.y += player->speed * deltaTime;
        player->speed += PLAYER_GRAVITY * deltaTime; // Apply gravity
        player->canJump = false;                     // Can't jump while falling
    }
    else
    {
        player->canJump = true; // Can jump again if hit obstacle
    }
}

void HandleMovement(Player *player, float deltaTime)
{
    // Movement
    bool movingLeft = (IsKeyDown(KEY_LEFT) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_A);
    bool movingRight = (IsKeyDown(KEY_RIGHT) && ARE_ARROWS_ACTIVATED) || IsKeyDown(KEY_D);
    bool justStoppedMoving = (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D));

    if (justStoppedMoving)
    {
        isRunning = false;
    }
    else if (movingLeft)
    {
        player->position.x -= PLAYER_HOR_SPD * deltaTime;
        isRunning = true;
        if (player->sprite.width > 0) // Only negate if it's positive (facing right)
        {
            player->sprite.width = -player->sprite.width; // Flip sprite to face left
        }
    }
    else if (movingRight)
    {
        player->position.x += PLAYER_HOR_SPD * deltaTime;
        isRunning = true;
        if (player->sprite.width <= 0) // Only negate if it's positive (facing right)
        {
            player->sprite.width = -player->sprite.width; // Flip sprite to face left
        }
    }
}

// Update player loop
void UpdatePlayer(Player *player, float deltaTime)
{
    HandleMovement(player, deltaTime);
    playerJump(player);
    collisionCheck(player, deltaTime);
}

void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float deltaTime, int width, int height)
{
    camera->target = player->position;
    camera->offset = Vector2{width / 2.0f, height / 2.0f};
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
    if (camera->target.x < minX + width / 2)
        camera->target.x = minX + width / 2;
    if (camera->target.x > maxX - width / 2)
        camera->target.x = maxX - width / 2;
    if (camera->target.y < minY + height / 2)
        camera->target.y = minY + height / 2;
    if (camera->target.y > maxY - height / 2)
        camera->target.y = maxY - height / 2;
}

void loadGameWindowIcon()
{
    Image windowIcon = LoadImage("assets/logo/logo.png");
    SetWindowIcon(windowIcon);
}

void ResetCameraZoom(Camera2D camera, Player player)
{
    if (IsKeyPressed(KEY_R))
    {
        camera.zoom = 1.0f;
        player.position = Vector2{400, 280};
    }
}

// Program main entry point
int main(void)
{
    // Randomize the seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialization
    InitWindow(screenWidth, screenHeight, "JAY");
    // loadGameWindowIcon();
    SetTraceLogLevel(7);
    SetExitKey(KEY_BACKSPACE);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_VSYNC_HINT);
    // SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    // double time = GetTime();

    Texture2D playerTexture = LoadTexture("C:/Users/jayxw/Desktop/RayLibGame/assets/sprites/scarfy.png");
    frameWidth = playerTexture.width / 6;
    frameHeight = playerTexture.height;

    // Source rectangle (part of the texture to use for drawing)
    sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = {screenWidth / 2.0f, screenHeight / 2.0f, frameWidth * 2.0f, frameHeight * 2.0f};

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size

    Player player = {0};
    player.position = Vector2{400, 280};
    player.speed = 0;
    player.canJump = false;
    player.sprite = playerTexture;

    // Vector2 origin = {(float)frameWidth, player.sprite.height / 1.0};
    Vector2 origin = {(float)frameWidth, (float)frameHeight * 1.2}; // Set the origin to the center of width and bottom of the height

    

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = Vector2{screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(3000);
    // TODO: Use origin to calc properly
    destRec.width = destRec.width / 1.4;
    destRec.height = destRec.height / 1.4;

    // player.sprite.width =  player.sprite.width / 1.5;
    // Main game loop
    while (!WindowShouldClose())
    {

        // Update loading progress
        if (!loadingComplete)
        {
            loadingProgress += loadingSpeed;
            if (loadingProgress >= 1.0f)
            {
                loadingProgress = 1.0f;
                loadingComplete = true; // Set loading complete when progress reaches 100%
            }
        }

        updateLoop();
        // Update
        float deltaTime = GetFrameTime();


        UpdatePlayer(&player, deltaTime);

        camera.zoom += ((float)GetMouseWheelMove() * 0.02f);

        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f)
            camera.zoom = 0.25f;
        // ResetCameraZoom(camera, player);

        // if (IsKeyPressed(KEY_C))
        //     cameraOption = (cameraOption + 1) % cameraUpdatersLength;

        // Call update camera function by its pointer
        // cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        UpdateCameraCenterInsideMap(&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);
        // Draw loading text
        if (!loadingComplete)
        {
            DrawRectangle(0, 0, 1000000, 1000000, GRAY);
            DrawText("Loading...", screenWidth / 2 - 50, screenHeight / 2 - 40, 20, DARKGRAY);
            DrawRectangle(screenWidth / 2 - 100, screenHeight / 2, 200, 20, LIGHTGRAY);
            DrawRectangle(screenWidth / 2 - 100, screenHeight / 2, (int)(200 * loadingProgress), 20, GREEN);
            // DrawText("Loading Complete!", screenWidth / 2 - 80, screenHeight / 2 + 30, 20, DARKGREEN);
        }
        if (loadingComplete)
        {
            BeginMode2D(camera);
            for (int i = 0; i < envItemsLength; i++)
            {
                DrawRectangleRec(envItems[i].rect, envItems[i].color);
            }
            destRec.x = player.position.x;
            destRec.y = player.position.y;

            DrawTexturePro(player.sprite, sourceRec, destRec, origin, (float)rotation, WHITE);
            DrawCircleV(player.position, 8.0f, BLACK);
            walkAnimation();
            EndMode2D();
            DrawText(TextFormat("FPS: %d", GetFPS()), 40, 40, 40, MAROON);
        }
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}
