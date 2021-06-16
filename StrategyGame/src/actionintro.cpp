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
    eTime += time;
    if ((eTime > showTime) || (clicked)) {
        int bp = 0;
        //This pointer gets owned by game.
        nextAction = new ActionSelectServer();
        return true;
    }
    return false;
}

void ActionIntro::Click()
{
    clicked = true;
}

void ActionIntro::Draw()
{
    int alpha = 255;

    if (eTime < 1) {
        alpha = (int((255) * eTime));
    }
    if (eTime > ((showTime - 1l))) {
        alpha = (int((255) * (showTime - eTime)));
    }

    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("INTRO", rect);
    int i = SDL_SetTextureAlphaMod(img, alpha);

    //GoodDoge found the line below
    i = SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);

    int x = (Display::Width - 600) >> 1;
    int y = (Display::Height - 300) >> 1;
    SDL_Rect dest{ x,y,600,300 };
    SDL_SetRenderDrawBlendMode(Display::GetRenderer(), SDL_BLENDMODE_BLEND);
    Display::DrawTexture(img, &rect, &dest);
    SDL_SetRenderDrawBlendMode(Display::GetRenderer(), SDL_BLENDMODE_NONE);
}
