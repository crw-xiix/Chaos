#include "pch.h"
#include "action.h"


bool ActionPlayLocal::Process(double time)
{
    return false;
}

void ActionPlayLocal::Click()
{
}

ActionMovePlayer::ActionMovePlayer(Unit& who, int x, int y): actor(who)
{
    tx = x;
    ty = y;
}

bool ActionMovePlayer::Process(double time)
{
    float dx = tx - actor.GetXF();
    float dy = ty - actor.GetYF();
    float l = sqrt(dx * dx + dy * dy);
    dx /= l; 
    dy /= l;
    actor.MoveF(actor.GetXF() + dx*(float)time*4.0f, actor.GetYF() + dy*(float)time*4.0f);
    //XXXC CRW - need to store old direction to see if we reversed - went too far, lag, etc.
    if (l < 0.05) {
        actor.Move(tx, ty);
        return true;
    }
    return false;
}

void ActionMovePlayer::Click()
{
}

void Action::Mouse(int mx, int my, int b)
{
    //Do nothing.
}

Action::Action()
{
}
