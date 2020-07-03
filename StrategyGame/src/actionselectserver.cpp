#include "pch.h"
#include "actionselectserver.h"
#include "assetmgr.h"

ActionSelectServer::ActionSelectServer()
{
}

bool ActionSelectServer::Process(double time)
{
    eTime += time;
    if ((eTime > 3) || (clicked)) {
        int bp = 0;
        
        return true;
    }
    draw();
    return false;
}

void ActionSelectServer::Click()
{
    clicked = true;
}

void ActionSelectServer::Mouse(int x, int y, int b)
{
}

void ActionSelectServer::draw()
{

    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("MENUBKG", rect);
    int i = SDL_SetTextureAlphaMod(img, 0);
    int x = (Display::Width - 600) >> 1;
    int y = (Display::Height - 300) >> 1;
    SDL_Rect dest{ x,y,600,300 };
    SDL_SetRenderDrawBlendMode(Display::GetRenderer(), SDL_BLENDMODE_BLEND);
    Display::DrawTexture(img, &rect, &dest);
    SDL_SetRenderDrawBlendMode(Display::GetRenderer(), SDL_BLENDMODE_NONE);
    return;
   
}
