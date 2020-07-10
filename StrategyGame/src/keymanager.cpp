#include "pch.h"
#include "keymanager.h"

KeyboardManager::KeyboardManager()
{
	
}

void KeyboardManager::Process(double ms) {
    if (KeyManager == nullptr) {
        KeyManager = new KeyboardManager();
    }
    if (keyQueue.size() > 0) {
        int val = *(keyQueue.begin());
        keyQueue.pop_front();
        if (callBack) callBack(val);
    }
}

void KeyboardManager::SetCallBack(std::function<void(const int)> a)
{
   callBack = a;
}

void KeyboardManager::AddKeyDown(int key, bool shift)
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
    keyQueue.push_back(key);
}

void KeyboardManager::SetShift(bool state)
{
    shiftState = state;
}


std::list<int> KeyboardManager::keyQueue;
KeyboardManager *KeyboardManager::KeyManager;
