#include "pch.h"
#include "actionintro.h"
#include "assetmgr.h"
#include "SDL.h"
#include "game.h"
#include "actionselectserver.h"

ActionIntro::ActionIntro()
{
    //Assets are loaded, nothing to do...
}

bool ActionIntro::Process(double time)
{
    int showTime = 4;
    eTime += time;
    if ((eTime > showTime) || (clicked)) {
        int bp = 0;
        nextActions.push_back(new ActionSelectServer());
        return true;
    }
    int alpha = 255;

    if (eTime < 1) {
        alpha = (int ((255) * eTime));
    }
    if (eTime > (showTime-1)) {
        alpha = (int((255) * (showTime-eTime)));
    }
    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("INTRO",rect);
    int i = SDL_SetTextureAlphaMod(img, alpha);

    //GoodDoge found the line below
    i =SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);

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
