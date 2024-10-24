#pragma once

#include "raylib.h"
#include "Debug.h"
#include <thread>
#include <chrono>
#include <iostream>

int MusicSampleRate = 0;

class MusicPlayer
{
private:
    Music music;

public:
    void StartMainGameMusic(const char *filePath); 
    void UnloadMusicPlayer();
    void MusicLoop();
    // Destructor
    ~MusicPlayer()
    {
        UnloadMusicPlayer();
    }
};
