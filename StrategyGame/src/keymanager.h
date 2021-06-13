#pragma once
#include "pch.h"

class FocusManager;

class KeyboardManager {
public:
    KeyboardManager();
    static KeyboardManager* KeyManager;
    void Process(double ms);
    void SetCallBack(std::function<void(const int)> a);
    static void AddKeyDown(int key, bool shift);
    void SetShift(bool state);
    void SetFocusManager(FocusManager* fm);
private:
    static std::list<int> keyQueue;
    bool shiftState { false };
    std::function<void(int)> callBack;
    FocusManager* focusMan = nullptr;
};
