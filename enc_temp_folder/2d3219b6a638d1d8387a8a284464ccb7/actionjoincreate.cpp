#include "pch.h"
#include "actionjoincreate.h"
#include "assetmgr.h"
#include "display.h"
#include "label.h"
#include "textbox.h"
#include <functional>
#include "game.h"
#include "../3rd/jute.h"
#include "json.h"
#include <memory>

const int a_val = 1;
const int b_val = 2;
const int c_val = a_val + b_val;


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

    int rSideY = location.y + 35;
    //This will be 32x32 font..
    //std::smart_ptr<FontFixed> pt(new Font16());
    tRoomCode = new TextBox(location.x + 300, rSideY, 256, 38);
    tRoomCode->SetText("");
    tRoomCode->SetFont(std::make_unique<Font32>());
    tRoomCode->SetText("Thank you");

    rSideY += 80;
    //32x32 here
    tUserName= new TextBox(location.x + 300, rSideY, 256, 20);
    tUserName->SetText("");
    tUserName->SetFont(std::make_unique<Font16>());
    tUserName->SetText("John");


    Button* bCreate = new Button(location.x + 10, location.y + 90, 256, 48);
    bCreate->SetText("Create Room");
    bCreate->SetTexture(bTex);
    bCreate->SetOnClick(std::bind(&ActionJoinCreate::createClick, this));

    Button* bExit = new Button(location.x + 10, location.y + 150, 256, 48);
    bExit->SetText("Just Wander");
    bExit->SetTexture(bTex);
    bExit->SetOnClick(std::bind(&ActionJoinCreate::wanderClick, this));

    controls.push_back(lTitle);
    controls.push_back(bJoin);
    controls.push_back(tRoomCode);
    controls.push_back(tUserName);
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
    int mx, my;
    //Need this so we stay in sync changing menus with lag
    if (first) {
        ourCallBack.SetActive(true);
        first = false;
    }
    else {
        int bp = 0;
    }
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
  
    return false;
}

void ActionJoinCreate::Click()
{
}

void ActionJoinCreate::Mouse(int x, int y, int b)
{
}

void ActionJoinCreate::Draw()
{
    draw();
}

void ActionJoinCreate::joinClick()
{
}

void ActionJoinCreate::createClick()
{
    std::string st = "{" +
        Json::Jsonify("request", "create") + "," +
        Json::Jsonify("game", "chaos") + "," +
        Json::Jsonify("username", tUserName->GetText()) +
        "}";
    Game::gameInstance->SendMessage(st);
    
}

void ActionJoinCreate::wanderClick()
{
    clicked = true;
}

/// <summary>
/// 
/// </summary>
/// <param name="val"></param>
/// <returns>True if the message was handled.....</returns>
bool ActionJoinCreate::MessageIn(jute::jValue& v)
{
    //have to handle situations where we sent a message, but the internet 
    //could be fast than we are.....  Gonna leave it in the queue if we
    //are not ready, or have finished our job..
    if (ourCallBack.GetActive() == false) return false;
    try {
        std::string resp = v["request"].as_string();
        if (resp == "create") {
            std::string roomCode = v["roomcode"].as_string();
            if (roomCode.length() == 4) {
                //Trigger game, send room code.
                Game::gameInstance->SetRoomCode(roomCode);
                std::string st =
                    "{" +
                    Json::Jsonify("request", "join") + "," +
                    Json::Jsonify("roomcode", roomCode) + "," +
                    Json::Jsonify("username", tUserName->GetText()) + "," +
                    Json::Jsonify("game", "chaos") + "}";
                Game::gameInstance->SendMessage(st);

                //Turn off messages for this function...
                //xxxc crw need to automate this somehow
                ourCallBack.SetActive(false);
            }
        }
        
    }
    catch (...) {
        //Failed......
    }
    int bp = 0;
    return true;
    
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
