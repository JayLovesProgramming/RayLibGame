#include "Music.h"
#include <chrono>
#include <iostream>

void MusicPlayer::StartMainGameMusic(const char *filePath, bool &loadingComplete)
{
    musicThread = std::thread([this, filePath, &loadingComplete]()
                              {
        InitAudioDevice(); // Initialize the audio device in the thread

        if (MUSIC_ENABLED) // Once loading is done, load and play the music if enabled
        {
            while (!loadingComplete) // Wait until loading is complete
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep to avoid CPU overload
            }
            music = LoadMusicStream(filePath);   // Load music file
            MusicSampleRate = music.stream.sampleRate; // Set the sample rate
            PlayMusicStream(music);              // Play the music
            isPlaying.store(true); // Set playing flag to true
            std::cout << "Music started." << std::endl;
            // Keep updating the music stream while it plays
            while (isPlaying.load() && IsMusicStreamPlaying(music))
            {
                UpdateMusicStream(music);
                std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Approximate 60 FPS
            }
        }
        // Close audio device when done
        CloseAudioDevice(); });
}

void MusicPlayer::UnloadMusicPlayer()
{
    isPlaying.store(false); // Signal to stop music
    if (musicThread.joinable())
    {
        musicThread.join(); // Ensure the thread completes before unloading
    }
    if (MusicSampleRate != 0)
    {
        CloseAudioDevice();
        UnloadMusicStream(music); // Unload the music stream
    }
    std::cout << "Deststructor: Music stopped and unloaded." << std::endl;
}
