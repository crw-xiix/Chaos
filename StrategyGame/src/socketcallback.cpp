#include "pch.h"
#include "socketcallback.h"

MessageCallBack::MessageCallBack(std::function<void(std::string)> iCallBack):callBack(iCallBack)
{
	Game::gameInstance->AddCallBack(callBack);
}

MessageCallBack::~MessageCallBack()
{
	Game::gameInstance->RemoveCallBack();
}
