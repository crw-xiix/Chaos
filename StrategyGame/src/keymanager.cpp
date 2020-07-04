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

void KeyboardManager::AddKeyDown(int key)
{
    keyQueue.push_back(key);
}


std::list<int> KeyboardManager::keyQueue;
KeyboardManager *KeyboardManager::KeyManager;
