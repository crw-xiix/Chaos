#pragma once
#include "pch.h"
#include "game.h"
#include <functional>


class MessageCallBack {
public:
	MessageCallBack(std::function<void(std::string)> iCallBack);
	~MessageCallBack();
private:
	std::function<void(std::string)> callBack;
};
