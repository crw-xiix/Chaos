/* Written by Mikol/JJJ based on crw-xiix AssetManager class */

#pragma once

#include <string>
#include <map>
#include<SDL_mixer.h>

class AudioManager {
private:
	
public:
	static std::map<std::string,Mix_Music*> SoundTracks;
	static std::map<std::string,Mix_Chunk*> Effects;

	static bool LoadEffect(const char* filename, std::string name);
	static bool LoadMusic(const char* filename, std::string name);

	static Mix_Chunk* GetEffect(std::string name);
	static Mix_Music* GetMusic(std::string name);
	static void Clean();
};
