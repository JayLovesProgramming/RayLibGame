// Music.h
#pragma once

#include "raylib.h"
#include "Debug.h"
#include <iostream>

int MusicSampleRate;

class MusicPlayer
{
private:
    Music music;

public:
    // Initialize the audio device and load the music stream
    void StartMusic(const char *filePath)
    {
        InitAudioDevice(); // Initialize audio device
        if (MUSIC_ENABLED)
        {
            MusicSampleRate = music.stream.sampleRate;
            music = LoadMusicStream(filePath); // Load music file
            PlayMusicStream(music);            // Play the music stream
        }
    }

    void UnloadMusicPlayer()
    {
        if (MUSIC_ENABLED && MusicSampleRate != 0)
        {
            UnloadMusicStream(music); // Unload the music stream
        }
        CloseAudioDevice(); // Close audio device if it was initialized
        std::cout << "Destructor: Music unloaded and audio device closed" << std::endl;
    }

    // Update the music stream
    void UpdateMusic()
    {
        if (MUSIC_ENABLED && MusicSampleRate != 0)
        {
            UpdateMusicStream(music); // Update music buffer with new stream data
        }
    }

    // ~MusicPlayer()
    // {

    // }
};
