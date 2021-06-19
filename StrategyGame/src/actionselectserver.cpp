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
#include "label.h"


ActionSelectServer::ActionSelectServer()
{
    //center us up
    location = SDL_Rect {
        (Display::Width - 600) >> 1,
        (Display::Height - 300) >> 1,
        600, 300};
    int sx = (Display::Width - 600) >> 1;
    int sy = (Display::Height - 300) >> 1;
    
    SDL_Texture* bTex = AssetMgr::GetAll("BUTTON");

//    SDL_Rect labelPos = SDL_Rect(location.x + 3, loction.y + 3, location.w - 6, 20);
    SDL_Rect labelPos  { location.x + 3, location.y + 8, location.w - 6, 20 };
    Label* lTitle = new Label(labelPos);
    lTitle->SetText("Select Server");

    location.y += 30;
    //Have to center this up now.
    //Location.x 
    location.x = (Display::Width - 256) >> 1;  //It's gotta be centered..........

    Button *bRemote = new Button(location.x, location.y+20, 256, 48);
    bRemote->SetText("Cabbage:82");
    bRemote->SetTexture(bTex);
    bRemote->SetOnClick(std::bind(&ActionSelectServer::remoteClick,this));
    

    Button *bLocal = new Button(location.x, location.y+80, 256, 48);
    bLocal->SetText("127.0.0.1:82");
    bLocal->SetTexture(bTex);
    bLocal->SetOnClick(std::bind(&ActionSelectServer::localClick, this));

    Button* bPi = new Button(location.x, location.y + 140, 256, 48);
    bPi->SetText("192.168.89.250:82");
    bPi->SetTexture(bTex);
    bPi->SetOnClick(std::bind(&ActionSelectServer::piClick, this));

    
    Label* lUserName = new Label(location.x, location.y + 200, 256, 48);
    lUserName->SetText("Enter User Name");
    tUserName = new TextBox(location.x , location.y + 240, 256, 20);
    tUserName->SetText("");
    tUserName->SetFont(std::make_unique<Font16>());
    tUserName->SetText("");
    tUserName->SetMaxLength(16);


    location.y += 80;
    Button* bExit = new Button(location.x, location.y + 200, 256, 48);
    bExit->SetText("Quit");
    bExit->SetTexture(bTex);
    bExit->SetOnClick(std::bind(&ActionSelectServer::quitClick, this));




    controls.push_back(lTitle);
    controls.push_back(bRemote);
    controls.push_back(bLocal);
    controls.push_back(bPi);

    controls.push_back(lUserName);
    controls.push_back(tUserName);
    
    controls.push_back(bExit);

    keyMan.Add(controls);
}

void ActionSelectServer::keyPressed(int val)
{
    //We don't really care for now.
   
   
}
ActionSelectServer::~ActionSelectServer()
{
    for (auto& i : controls) {
        delete i;
        i = nullptr;
    }

}

bool ActionSelectServer::Process(double time)
{
    int mx, my;
    uint32_t mouseState = SDL_GetMouseState(&mx, &my);
    keyMan.Process(mx, my, mouseState);
    eTime += time;
    keyMan.Process(mx, my, mouseState);
    keyMan.Process(time);
    return clicked;
}

void ActionSelectServer::Click()
{
    //clicked = true;
}

void ActionSelectServer::Mouse(int x, int y, int b)
{
    //Using a mouse controller, so it don't matter......
    std::string st = "";
}

void ActionSelectServer::Draw()
{
    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("MENUBKG", rect);
    int x = (Display::Width - 600) >> 1;
    int y = (Display::Height - 300) >> 1;
    
    SDL_Rect dest{ x,y,600,300 };
    SDL_Color back{ 20, 50, 20, 0 };
    SDL_Color edge{ 120, 150, 120, 0 };

    Action::DrawWindow(dest, back, edge);
//    Display::DrawTexture(img, &rect, &dest);
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
