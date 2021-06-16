#include "pch.h"
#include "socketcallback.h"


MessageCallBack::MessageCallBack(std::function<bool(jute::jValue&)> iCallBack):callBack(iCallBack)
{
	Game::gameInstance->SetMsgCallBack(callBack);
}

MessageCallBack::~MessageCallBack()
{
	Game::gameInstance->RemoveCallBack();
}
