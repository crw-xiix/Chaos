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
    //center us up
    location = SDL_Rect {
        (Display::Width - 600) >> 1,
        (Display::Height - 300) >> 1,
        600, 300};

    
    SDL_Texture* bTex = AssetMgr::GetAll("BUTTON");

    Button *bRemote = new Button(location.x+10, location.y+20, 256, 48);
    bRemote->SetText("Cabbage:82");
    bRemote->SetTexture(bTex);
    bRemote->SetOnClick(std::bind(&ActionSelectServer::remoteClick,this));
    

    Button *bLocal = new Button(location.x+10, location.y+80, 256, 48);
    bLocal->SetText("127.0.0.1:82");
    bLocal->SetTexture(bTex);
    bLocal->SetOnClick(std::bind(&ActionSelectServer::localClick, this));

    Button* bPi = new Button(location.x + 10, location.y + 140, 256, 48);
    bPi->SetText("192.168.89.250:82");
    bPi->SetTexture(bTex);
    bPi->SetOnClick(std::bind(&ActionSelectServer::piClick, this));

    Button* bExit = new Button(location.x + 10, location.y + 200, 256, 48);
    bExit->SetText("Quit");
    bExit->SetTexture(bTex);
    bExit->SetOnClick(std::bind(&ActionSelectServer::quitClick, this));

    controls.push_back(bRemote);
    controls.push_back(bLocal);
    controls.push_back(bPi);
    controls.push_back(bExit);
    mouseMan = new MouseManager(&controls);
}

ActionSelectServer::~ActionSelectServer()
{
    for (auto& i : controls) {
        delete i;
        i = nullptr;
    }
    if (mouseMan != nullptr) delete mouseMan;
}

bool ActionSelectServer::Process(double time)
{
    int mx, my;
    uint32_t mouseState = SDL_GetMouseState(&mx, &my);
    mouseMan->Process(mx, my, mouseState);
    eTime += time;

    return clicked;
}

void ActionSelectServer::Click()
{
    //clicked = true;
}

void ActionSelectServer::Mouse(int x, int y, int b)
{
    //Using a mouse controller, so it don't matter......
}

void ActionSelectServer::Draw()
{
    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("MENUBKG", rect);
    int x = (Display::Width - 600) >> 1;
    int y = (Display::Height - 300) >> 1;
    SDL_Rect dest{ x,y,600,300 };
    Display::DrawTexture(img, &rect, &dest);
    for (auto c : controls) {
        c->Draw();
    }
    return;
}

void ActionSelectServer::localClick()
{
    Game::gameInstance->onSelectServerCallback("ws://127.0.0.1:82/chat");
    nextAction = new ActionJoinCreate();
    clicked = true;
}

void ActionSelectServer::remoteClick()
{
    //xxxc CRW finger out how to open 82 on the PI........
    Game::gameInstance->onSelectServerCallback("ws://madcabbage.ovh:82/chat");
    nextAction = new ActionJoinCreate();
    clicked = true;
}

void ActionSelectServer::piClick()
{
    Game::gameInstance->onSelectServerCallback("ws://192.168.89.250:82/chat");
    nextAction = new ActionJoinCreate();
    clicked = true;
}

void ActionSelectServer::quitClick()
{
    Game::gameInstance->onSelectServerCallback("QUIT");
    clicked = true;
}
