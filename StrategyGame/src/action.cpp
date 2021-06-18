#include "pch.h"
#include "action.h"
#include "display.h"


bool Action::Process(double time)
{
    return false;
}

void Action::Draw()
{
}

void Action::Click()
{
}

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

void Action::DrawWindow(SDL_Rect& target, SDL_Color back, SDL_Color border)
{
    int bw = 4;
    //Gonna cheat here and use 2px borders
    SDL_SetRenderDrawColor(Display::GetRenderer(), border.r, border.g, border.b, 255);
    SDL_RenderFillRect(Display::GetRenderer(), &target);
    //copy
    SDL_Rect top(target);
    SDL_Rect bot(target);

    //Gives us the top part....
    top.y += bw;
    top.x += bw;
    top.w -= bw*2;
    top.h = 18+bw*2;

    bot.y += 22 + bw * 3;
    bot.x += bw;
    bot.w -= bw*2;
    bot.h = target.h +18 + bw * 3;

    SDL_SetRenderDrawColor(Display::GetRenderer(), back.r, back.g, back.b, 255);
    SDL_RenderFillRect(Display::GetRenderer(), &top);
    SDL_SetRenderDrawColor(Display::GetRenderer(), back.r, back.g, back.b, 255);
    SDL_RenderFillRect(Display::GetRenderer(), &bot);
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

