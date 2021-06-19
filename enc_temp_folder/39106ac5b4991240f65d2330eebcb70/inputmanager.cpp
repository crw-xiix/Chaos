#include "pch.h"
#include "inputmanager.h"

InputManager::InputManager()
{
	
}

//This is a pointer to obj on stack, owned by caller.

void InputManager::Process(int mx, int my, int mb)
{
    VisualBase* found = nullptr;
    SDL_Point pt{ mx,my };
    for (auto visBase : viewItems) {
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
                lastHover->MouseDown(mx, my);
                focus->hasFocus = false;
                //Take away focus
                if (lastDown != nullptr) {
                    lastDown->hasFocus = true;
                    lastDown = lastHover;
                }
                else {

                }
                if (found->canFocus) {
                    focus = found;
                    focus->hasFocus = true;
                }

            }
            else {
                lastHover->MouseUp();
                if (lastDown == lastHover) {
                    lastHover->MouseClick(mx, my);
                }
            }
        }
        mouseDown = mb;
    }
}
void InputManager::Process(double ms) {
    
    if (keyQueue.size() > 0) {
        int val = *(keyQueue.begin());
        keyQueue.pop_front();
        //We can just sent the key direct.......
        if (callBack) {
            callBack(val);
        }
        else {
            focus->KeyIn(val);
        }
    }
    for (auto i : viewItems) {
        i->Process(ms);
    }
}

void InputManager::SetCallBack(std::function<void(const int)> a)
{
   callBack = a;
}

void InputManager::AddKeyDown(int key, bool shift)
{
    //Now we can add capital letters......
    if ((key >= 'a') && (key <= 'z') && shift) {
        key -= 32;
    }
    if (shift) {
        switch (key) {
            //number keys
        case '0': key = ')'; break;
        case '1': key = '!'; break;
        case '2': key = '@'; break;
        case '3': key = '#'; break;
        case '4': key = '$'; break;
        case '5': key = '%'; break;
        case '6': key = '^'; break;
        case '7': key = '&'; break;
        case '8': key = '*'; break;
        case '9': key = '('; break;
            //Other punctuation
        case '`': key = '~'; break;
        case '-': key = '_'; break;
        case '=': key = '+'; break;
        case '[': key = '{'; break;
        case ']': key = '}'; break;
        case ';': key = ':'; break;
        case '\'': key = '"'; break;
        case ',': key = '<'; break;
        case '.': key = '>'; break;
        case '/': key = '?'; break;
        }
    }
    //xxxc CRW - how to catch a loss of focus
    keyQueue.push_back(key);
}

void InputManager::SetShift(bool state)
{
    shiftState = state;
}

void InputManager::Add(std::vector<VisualBase*> items)
{
    //Remember, owner deletes!
    for (auto vi : items) {
        viewItems.push_back(vi);
        if (focus == nullptr) {
            if (vi->canFocus) focus = vi;
        }
    }
    if (focus != nullptr) {
        focus->hasFocus = true;
    }
}

void InputManager::KeyIn(int val)
{
}

std::list<int> InputManager::keyQueue;
InputManager *InputManager::KeyManager;
