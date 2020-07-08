#include "pch.h"
#include "display.h"
#include "game.h"
#include "perlinmap.h"
#include <SDL_image.h>
#include "assetmgr.h"
#include "map.h"
#include "viewport.h"
#include "../3rd/easywsclient.hpp"

#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>
#include "unit.h"
#include "../3rd/jute.h"


void test() {
    std::map<char, int> vals;

    std::string testValue = "I did this in a few minutes.";

    for (char c : testValue) {
        char cval = toupper(c);
        if (vals.find(cval) == vals.end()) {
            vals[cval] = 1;
        }
        else {
            vals[cval]++;
        }
    }
    for (char c : testValue) {
        char cval = toupper(c);
        if (vals[cval] > 1) {
            std::cout << ")";
        }
        else {
            std::cout << "(";
        }
    }
    std::cout << std::endl;
}




int main(int argc, char* argv[])
{
    test();
    //nomain2();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}
	

	Game::Create();
	Display::Create(1600, 800);
	IMG_Init(IMG_INIT_PNG);

	Game::gameInstance->StartUp(1600, 800);

	while (Game::IsRunning())
	{
		Game::ProcessEvents();
        if (!Game::gameInstance->Process()) break;
		Display::Present();
		SDL_Delay(11);
	}
	AssetMgr::Destroy();
	SDL_Quit();
	return 0;
}
