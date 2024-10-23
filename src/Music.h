// MusicPlayer.h
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "raylib.h"

class MusicPlayer {
private:
    Music music;
    bool isLoaded; // To check if music is loaded

public:
    MusicPlayer() : isLoaded(false) {}

    // Initialize the audio device and load the music stream
    void StartMusic(const char* filePath) {
        if (!isLoaded) {
            InitAudioDevice();  // Initialize audio device
            music = LoadMusicStream(filePath); // Load music file
            PlayMusicStream(music); // Play the music stream
            isLoaded = true; // Mark music as loaded
        }
    }

    // Update the music stream
    void UpdateMusic() {
        if (isLoaded) {
            UpdateMusicStream(music); // Update music buffer with new stream data
        }
    }

    // Cleanup music resources
    void CleanupMusic() {
        if (isLoaded) {
            UnloadMusicStream(music); // Unload the music stream
            CloseAudioDevice(); // Close audio device if it was initialized
            isLoaded = false; // Mark music as unloaded
        }
    }

    // Check if music is playing
    bool IsPlaying() const {
        // return isLoaded && IsMusicPlaying(music);
    }
};

#endif // MUSIC_PLAYER_H
