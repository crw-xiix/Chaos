#pragma once
#include "pch.h"
#include "visualbase.h"



class InputManager {
public:
    InputManager();
    static InputManager* KeyManager;
    void Process(int mx, int my, int mb);
    void Process(double ms);
    void SetCallBack(std::function<void(const int)> a);
    static void AddKeyDown(int key, bool shift);
    void SetShift(bool state);
    void Add(std::vector<VisualBase*> items);
    //void SetFocusManager(FocusManager* fm);
    void KeyIn(int val);

private:
    static std::list<int> keyQueue;
    std::vector<VisualBase*> viewItems;
    bool shiftState { false };
    std::function<void(int)> callBack;
//  FocusManager* focusMan = nullptr;
    VisualBase* focus = nullptr;

    VisualBase* lastHover = nullptr;
    VisualBase* lastDown = nullptr;
    int mouseDown = 0;
};
