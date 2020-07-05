/*
Author:
Charles Wood
7-2-2020
*/

#include "pch.h"
#include "actionselectserver.h"
#include "assetmgr.h"
#include "game.h"
#include "actionjoincreate.h"


ActionSelectServer::ActionSelectServer()
{
    location = SDL_Rect {
        (Display::Width - 600) >> 1,
        (Display::Height - 300) >> 1,
        600, 300};

    SDL_Rect temp;
    SDL_Texture* bTex = AssetMgr::GetAll("BUTTON",temp);

    Button *bRemote = new Button(location.x+10, location.y+20, 256, 48);
    bRemote->SetText("Remote:82");
    bRemote->SetTexture(bTex);
    bRemote->SetOnClick(std::bind(&ActionSelectServer::remoteClick,this));
    

    Button *bLocal = new Button(location.x+10, location.y+80, 256, 48);
    bLocal->SetText("127.0.0.1:82");
    bLocal->SetTexture(bTex);
    bLocal->SetOnClick(std::bind(&ActionSelectServer::localClick, this));

    Button* bExit = new Button(location.x + 10, location.y + 140, 256, 48);
    bExit->SetText("Quit");
    bExit->SetTexture(bTex);
    bExit->SetOnClick(std::bind(&ActionSelectServer::quitClick, this));

    controls.push_back(bRemote);
    controls.push_back(bLocal);
    controls.push_back(bExit);
    mouseMan = new MouseManager(&controls);
}

ActionSelectServer::~ActionSelectServer()
{
    for (auto i : controls) delete i;
    delete mouseMan;
}

bool ActionSelectServer::Process(double time)
{
    int mx, my;
    uint32_t mouseState = SDL_GetMouseState(&mx, &my);
    mouseMan->Process(mx, my, mouseState);

    eTime += time;
    if ((eTime > 30000) || (clicked)) {
        int bp = 0;
        return true;
    }
    draw();
    return false;
}

void ActionSelectServer::Click()
{
    //clicked = true;
}

void ActionSelectServer::Mouse(int x, int y, int b)
{
}

void ActionSelectServer::localClick()
{
    
    Game::gameInstance->onSelectServerCallback("ws://127.0.0.1:82/chat");
    nextActions.push_back(new ActionJoinCreate());
    
    clicked = true;
}

void ActionSelectServer::remoteClick()
{
    
    Game::gameInstance->onSelectServerCallback("ws://71.56.75.25:82/chat");
    nextActions.push_back(new ActionJoinCreate());
    clicked = true;
}

void ActionSelectServer::quitClick()
{
    
    Game::gameInstance->onSelectServerCallback("QUIT");
    clicked = true;
}

void ActionSelectServer::draw()
{
    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("MENUBKG", rect);
    int i = SDL_SetTextureAlphaMod(img, 0);
    int x = (Display::Width - 600) >> 1;
    int y = (Display::Height - 300) >> 1;
    SDL_Rect dest{ x,y,600,300 };
    Display::DrawTexture(img, &rect, &dest);
    for (auto c : controls) {
        c->Draw();
    }
    return;
}
