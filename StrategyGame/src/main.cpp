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





int nomain2()
{
    using easywsclient::WebSocket;
#ifdef _WIN32
    INT rc;
    WSADATA wsaData;
    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return 1;
    }
#endif
    

    //XXXC CRW need to thread this, thread safe queue for send/recv

    GamePlayer gp;
    std::unique_ptr<WebSocket> ws(WebSocket::from_url("ws://71.56.75.25:82/chat"));
    assert(ws);
    ws->send("goodbye");
    ws->send("hello");
    while (ws->getReadyState() != WebSocket::CLOSED) {
        WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
        ws->poll();
        ws->dispatch([wsp,&gp](const std::string& message) {
            printf(">>> %s\n", message.c_str());
            if (message == "world") { wsp->close(); }

            //XXXC some bullshit.....
            //we got a message, lets reply with status
            std::string wtf = gp.GetJson();
            wsp->send(wtf);
            });
    }
#ifdef _WIN32
    WSACleanup();
#endif
    // N.B. - unique_ptr will free the WebSocket instance upon return:
    return 0;
}


int main(int argc, char* argv[])
{
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
