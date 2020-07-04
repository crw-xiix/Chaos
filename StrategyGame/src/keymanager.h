#pragma once
#include "pch.h"



class KeyboardManager {
public:
    KeyboardManager();
    static KeyboardManager* KeyManager;
    void Process(double ms);
    void SetCallBack(std::function<void(const int)> a);
    static void AddKeyDown(int key);
private:
    static std::list<int> keyQueue;
    
    std::function<void(int)> callBack;
    
};
