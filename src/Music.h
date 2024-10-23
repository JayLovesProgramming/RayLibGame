#include "raylib.h"

Music music = LoadMusicStream("assets/music/country.mp3");

void StartMusic()
{
    InitAudioDevice();
    PlayMusicStream(music);
}
