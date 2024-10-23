#pragma once

#include "raylib.h"
#include "Debug.h"
#include <thread>

int MusicSampleRate = 0;

class MusicPlayer
{
private:
    Music music;
    std::thread musicThread;
    std::atomic<bool> isPlaying; // Atomic flag to indicate if music is playing

public:
    MusicPlayer() : isPlaying(false) {} // Constructor initializes isPlaying to false
    void StartMainGameMusic(const char *filePath, bool &loadingComplete); // Initialize the audio device and load the music stream
    void UnloadMusicPlayer(); // Update the music stream
    void UpdateMusic();
    ~MusicPlayer() // Destructor to clean up the thread and unload music
    {
        UnloadMusicPlayer(); // Ensure proper cleanup of the music and thread
    }
};
