#include "pch.h"
#include "ActionIntro.h"
#include "assetmgr.h"
#include "SDL.h"

ActionIntro::ActionIntro()
{
    //Assets are loaded, nothing to do...
}

bool ActionIntro::Process(double time)
{
    eTime += time;
    if ((eTime > 3) || (clicked)) {
        int bp = 0;
        return true;
    }
    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("INTRO",rect);
    int i = SDL_SetTextureAlphaMod(img, 0);
    int x = (Display::Width - 600) >> 1;
    int y = (Display::Height- 300) >> 1;
    SDL_Rect dest{ x,y,600,300 };
    SDL_SetRenderDrawBlendMode(Display::GetRenderer(), SDL_BLENDMODE_BLEND);
    Display::DrawTexture(img, &rect, &dest);
    SDL_SetRenderDrawBlendMode(Display::GetRenderer(), SDL_BLENDMODE_NONE);
    return false;
}

void ActionIntro::Click()
{
    clicked = true;
}
