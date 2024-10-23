#include "LoadingScreen.h"

LoadingScreen::LoadingScreen()
    : loadingProgress(0.0f), loadingSpeed(0.01f), loadingComplete(false)
{

    // Define button rectangles
    startButton = {0, 0, 200, 50};    // Placeholder values, will set position later
    settingsButton = {0, 0, 200, 50}; // Placeholder values, will set position later
}

LoadingScreen::~LoadingScreen()
{
    UnloadTexture(backgroundTexture); // Unload background texture
    // Unload the font if it's dynamically loaded
    // UnloadFont(loadingFont);
}

void LoadingScreen::InitLoadingScreen(const char *backgroundPath, const char *fontPath)
{
    // Load background texture
    backgroundTexture = LoadTexture(backgroundPath);
    // Load custom font
    loadingFont = LoadFont(fontPath);

    // Set button positions
    startButton.x = (GetScreenWidth() / 2) - (startButton.width / 2);
    startButton.y = (GetScreenHeight() / 2) + 60; // Positioned below loading bar

    settingsButton.x = (GetScreenWidth() / 2) - (settingsButton.width / 2);
    settingsButton.y = startButton.y + 60; // Positioned below the Start button
}

void LoadingScreen::UpdateLoadingBar()
{
    // Update loading progress
    if (!loadingComplete)
    {
        loadingProgress += loadingSpeed;
        if (loadingProgress >= 1.0f)
        {
            loadingProgress = 1.0f;
            loadingComplete = true; // Set loading complete when progress reaches 100%
            onMainMenu = loadingComplete;
        }
    }
}

void LoadingScreen::DrawLoadingBar(int screenWidth, int screenHeight)
{
    if (!loadingComplete)
    {
        DrawTexture(backgroundTexture, screenWidth / 2 - backgroundTexture.width / 2, screenHeight / 2 - backgroundTexture.height / 2, WHITE);
        // Draw loading text
        DrawTextEx(loadingFont, "Loading...", {static_cast<float>(screenWidth) / 2 - 50, static_cast<float>(screenHeight) / 2 - 40}, 20, 2, WHITE);
        // Draw loading bar background
        DrawRectangle(screenWidth / 2 - 100, screenHeight / 2, 200, 20, LIGHTGRAY);
        // Draw loading progress
        DrawRectangle(screenWidth / 2 - 100, screenHeight / 2, (int)(200 * loadingProgress), 20, GREEN);
        char percentageText[10];
        snprintf(percentageText, sizeof(percentageText), "%.0f%%", loadingProgress * 100);
        DrawText(percentageText, screenWidth / 2 - 25, screenHeight / 2 + 30, 20, DARKGREEN);
    }
    else if (onMainMenu && !loadingScreen.clickedStartGame)
    {
        DrawTexture(backgroundTexture, screenWidth / 2 - backgroundTexture.width / 2, screenHeight / 2 - backgroundTexture.height / 2, WHITE);
        DrawText("Loading Complete!", screenWidth / 2 - 80, screenHeight / 2 + 30, 20, DARKGREEN);
        // Draw buttons
        DrawRectangleRec(startButton, DARKGRAY);
        DrawText("Start Game", startButton.x + 10, startButton.y + 10, 20, WHITE);
        DrawRectangleRec(settingsButton, DARKGRAY);
        DrawText("Settings", settingsButton.x + 10, settingsButton.y + 10, 20, WHITE);
    }
}

void LoadingScreen::HandleInput()
{
    if (loadingComplete && onMainMenu)
    {
        Vector2 mousePosition = GetMousePosition();

        // Check if the Start Game button is clicked
        if (CheckCollisionPointRec(mousePosition, startButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            onMainMenu = false;
            loadingScreen.clickedStartGame = true;
            std::cout << "Started game" << std::endl;
            // Logic to start the game
            // e.g., Set game state to START
        }

        // Check if the Settings button is clicked
        if (CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            // Logic to open settings
            // e.g., Set game state to SETTINGS
        }
    }
}
