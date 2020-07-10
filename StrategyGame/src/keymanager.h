#pragma once
#include "pch.h"



class KeyboardManager {
public:
    KeyboardManager();
    static KeyboardManager* KeyManager;
    void Process(double ms);
    void SetCallBack(std::function<void(const int)> a);
    static void AddKeyDown(int key, bool shift);
    void SetShift(bool state);
private:
    static std::list<int> keyQueue;

    bool shiftState { false };
    std::function<void(int)> callBack;
    
};
