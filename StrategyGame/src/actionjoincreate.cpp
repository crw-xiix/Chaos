#include "pch.h"
#include "actionjoincreate.h"
#include "assetmgr.h"
#include "display.h"
#include "label.h"
#include "textbox.h"
#include <functional>
#include "game.h"


using std::placeholders::_1;

ActionJoinCreate::ActionJoinCreate():
    //Fire up the callback message, no need to delete this way
    ourCallBack(std::bind(&ActionJoinCreate::MessageIn, this, _1))
{
    using namespace std::placeholders;
    location = SDL_Rect{
        (Display::Width - 600) >> 1,
        (Display::Height - 300) >> 1,
        600, 300 };

    SDL_Rect temp;
    SDL_Texture* bTex = AssetMgr::GetAll("BUTTON", temp);

    Label *lTitle = new Label(location.x, location.y+5, location.w, 20);
    lTitle->SetText("Join a current room or create a new one");

    Button* bJoin = new Button(location.x + 10, location.y + 30, 256, 48);
    bJoin->SetText("Join Room");
    bJoin->SetTexture(bTex);
    bJoin->SetOnClick(std::bind(&ActionJoinCreate::joinClick, this));

    tRoomCode = new TextBox(location.x + 300, location.y + 35, 256, 20);
    tRoomCode->SetText("");
    tRoomCode->SetMaxLength(4);
    tRoomCode->SetCaps(true);
    tRoomCode->SetLetters("abcdefghijklmnopqrstuvwxyz");


    Button* bCreate = new Button(location.x + 10, location.y + 90, 256, 48);
    bCreate->SetText("Create Room");
    bCreate->SetTexture(bTex);
    bCreate->SetOnClick(std::bind(&ActionJoinCreate::createClick, this));

    Button* bExit = new Button(location.x + 10, location.y + 150, 256, 48);
    bExit->SetText("Just Wander");
    bExit->SetTexture(bTex);
    bExit->SetOnClick(std::bind(&ActionJoinCreate::backClick, this));

    controls.push_back(lTitle);
    controls.push_back(bJoin);
    controls.push_back(tRoomCode);
    controls.push_back(bCreate);
    controls.push_back(bExit);

    mouseMan = new MouseManager(&controls);
    
    keyMan.SetCallBack(std::bind(&ActionJoinCreate::keyPressed,this, _1));
   
}

ActionJoinCreate::~ActionJoinCreate()
{
    for (auto i : controls) delete i;
    delete mouseMan;
}

bool ActionJoinCreate::Process(double time)
{
    //should ::Process() here
    int mx, my;
    uint32_t mouseState = SDL_GetMouseState(&mx, &my);
    for (auto c : controls) {
        c->Process(time);
    }

    mouseMan->Process(mx, my, mouseState);
    keyMan.Process(time);


    if (clicked) {
        int bp = 0;
        return true;
    }
    draw();
    return false;
}

void ActionJoinCreate::Click()
{
}

void ActionJoinCreate::Mouse(int x, int y, int b)
{
}

void ActionJoinCreate::joinClick()
{
}

void ActionJoinCreate::createClick()
{
    std::string st = "{\"request\":\"create\", \"game\" : \"chaos\" }";
    Game::gameInstance->SendMessage(st);

}

void ActionJoinCreate::backClick()
{
    clicked = true;
}

void ActionJoinCreate::MessageIn(std::string val)
{
    int bp = 0;
}

void ActionJoinCreate::keyPressed(int val)
{
    tRoomCode->KeyIn(val);
}

void ActionJoinCreate::draw()
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
