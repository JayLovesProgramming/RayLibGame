#pragma once

#include "raylib.h"

class LoadingScreen
{
private:
    float loadingProgress;          // Progress of loading from 0.0 to 1.0
    float loadingSpeed;             // Speed of loading progress increment
    Texture2D backgroundTexture;    // Background texture for the loading screen
    Font loadingFont;               // Font for loading text
    Rectangle startButton;          // Rectangle for the Start Game button
    Rectangle settingsButton;       // Rectangle for the Settings button

public:
    bool loadingComplete = false;
    bool onMainMenu;          
    bool clickedStartGame;          

    LoadingScreen();
    ~LoadingScreen();

    void InitLoadingScreen(const char* backgroundPath, const char* fontPath);
    void UpdateLoadingBar();
    void DrawLoadingBar(int screenWidth, int screenHeight);
    void HandleInput(); // Method to handle input for buttons

    bool IsLoadingComplete() const { return loadingComplete; }
};
