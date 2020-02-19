#include "Sound.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

using namespace std;

Sound::Sound() {

}

Sound::~Sound() {

}

void Sound::playSFX(string soundFilePath) {
    Mix_Chunk *sound = Mix_LoadWAV(soundFilePath.c_str());
    Mix_PlayChannel( -1, sound, 0 );
}

void Sound::playMusic(string soundFilePath) {
    Mix_Music *music = Mix_LoadMUS(soundFilePath.c_str());
    Mix_PlayMusic(music, -1);
}

