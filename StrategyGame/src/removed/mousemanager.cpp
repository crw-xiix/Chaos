#include "pch.h"
#include "mousemanager.h"

/*
MouseManager::MouseManager(std::vector<VisualBase*>* items)
{
    viewItems = items;
}

void MouseManager::Process(int mx, int my, int mb)
{
    VisualBase* found = nullptr;
    SDL_Point pt{ mx,my };
    for (auto visBase : *viewItems) {
        if (SDL_PointInRect(&pt, &visBase->location)) {
            found = visBase;
        }
    }
    if (found != lastHover) {
        if (lastHover) {
            lastHover->MouseOut();
            lastHover->MouseUp();
            lastDown = nullptr;
        }
        if (found) {
            found->MouseIn();
        }
        lastHover = found;
    }
    if (lastHover != nullptr) {
        if (mouseDown != mb) {
            if (mb == 1) {
                lastHover->MouseDown(mx,my);
                lastDown = lastHover;
            }
            else {
                lastHover->MouseUp();
                if (lastDown == lastHover) lastHover->MouseClick(mx, my);
            }
        }
        mouseDown = mb;
    }
}

MouseManager::~MouseManager()
{
    //if (viewItems != nullptr) delete viewItems;
}
*/