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
    double l = sqrt(dx * dx + dy * dy);
    dx /= l; 
    dy /= l;
    actor.MoveF(actor.GetXF() + dx*time*4, actor.GetYF() + dy*time*4);
    if (l < 0.05) {
        actor.Move(tx, ty);
        return true;
    }
    return false;
}

void ActionMovePlayer::Click()
{
}

Action::Action()
{
}
