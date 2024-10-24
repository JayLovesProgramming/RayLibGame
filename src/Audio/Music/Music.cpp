#include "Music.h"

void MusicPlayer::StartMainGameMusic(const char *filePath)
{
    InitAudioDevice(); // Initialize the audio device in the thread
    if (MUSIC_ENABLED) // Once loading is done, load and play the music if enabled
    {
        music = LoadMusicStream(filePath);         // Load music file
        MusicSampleRate = music.stream.sampleRate; // Set the sample rate
        PlayMusicStream(music);                    // Play the music
        SetMusicVolume(music, 0.25f);
        std::cout << "Music started." << std::endl;
        // while (isPlaying.load() && IsMusicStreamPlaying(music))
        // {
        //     UpdateMusicStream(music);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Approximate 60 FPS
        // }
    }
    // Close audio device when done
    // CloseAudioDevice();
}

void MusicPlayer::MusicLoop()
{
    if (!IsMusicStreamPlaying(music))
        return;


    UpdateMusicStream(music);
}

void MusicPlayer::UnloadMusicPlayer()
{
    if (MusicSampleRate != 0)
    {
        CloseAudioDevice();
        UnloadMusicStream(music); // Unload the music stream
    }
    std::cout << "Deststructor: Music stopped and unloaded." << std::endl;
}
