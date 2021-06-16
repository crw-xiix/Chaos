#include "pch.h"
#include "action.h"


void Action::Mouse(int mx, int my, int b)
{
    //Testing 1234 -- webhooks

    //Do nothing.
}

Action::Action()
{
}

Action::~Action() {
}

bool ActionPlayLocal::Process(double time)
{
    return false;
}

void ActionPlayLocal::Click()
{
}

ActionMovePlayer::ActionMovePlayer(Unit& who, int x, int y): actor(who)
{
    targetX = x;
    targetY = y;
}

bool ActionMovePlayer::HasKeyboardControl()
{
    return false;
}

bool ActionMovePlayer::Process(double time)
{
    float dx = targetX - actor.GetXF();
    float dy = targetY - actor.GetYF();
    float len = sqrt(dx * dx + dy * dy);
    dx /= len; 
    dy /= len;
    actor.MoveF(actor.GetXF() + dx*(float)time*4.0f, actor.GetYF() + dy*(float)time*4.0f);
    //need to store old direction to see if we reversed - went too far, lag, etc.
    if (len < 0.05) {
        actor.Move(targetX, targetY);
        return true;
    }
    return false;
}

void ActionMovePlayer::Click()
{
}

void ActionMovePlayer::Draw()
{
    //we don't have to do anything here....
}

