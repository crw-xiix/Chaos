/* Written by Mikol/JJJ based on crw-xiix AssetManager class 
https://github.com/Me43489
*/

#include "audiomanager.hpp"
#include <iostream>

bool AudioManager::LoadEffect(const char* filename,std::string name){
   
    Mix_Chunk* effect = Mix_LoadWAV(filename);
    
    if (effect == nullptr) {
        std::cout << "Failed to load:" << filename << "\n";
    }
    Effects[name] = effect;
    return false;
}

bool AudioManager::LoadMusic(const char* filename, std::string name){

    Mix_Music* soundtrack = Mix_LoadMUS(filename);
    if (soundtrack == nullptr) {
        std::cout << "Failed to load:" << filename << "\n";
    }
    SoundTracks[name] = soundtrack;
    return false;
}

Mix_Chunk* AudioManager::GetEffect(std::string name) {

    Mix_Chunk* effect = Effects[name];      
    return effect;
}
Mix_Music* AudioManager::GetMusic(std::string name) {
    Mix_Music* music = SoundTracks[name];
    return music;
}

void AudioManager::Clean() {
    for (auto i : SoundTracks) {
        Mix_FreeMusic(i.second);
    }
    for (auto j : Effects) {
        Mix_FreeChunk(j.second);
    }
    Mix_CloseAudio();
}


/****************************
    statics of mixer.hpp
*****************************/

 std::map<std::string,Mix_Music*> AudioManager::SoundTracks;
 std::map<std::string, Mix_Chunk*> AudioManager::Effects;
