#pragma once
#include "pch.h"
#include "game.h"
#include <functional>
#include "../3rd/jute.h"


class MessageCallBack {
public:
	/// <summary>
	/// Allows callbacks on network messages.  Warning!! You need to SetActive and Turn it off or timing issues.
	/// </summary>
	/// <param name="iCallBack">A callback function returning bool, taking a json object</param>
	/// <returns>True if it's ready, false if msg needs to chill</returns>
	MessageCallBack(std::function<bool(jute::jValue&)> iCallBack);
	~MessageCallBack();
	/// <summary>
	/// This need to set and checked on the callback.  Must be turned off after message sent.
	/// </summary>
	/// <param name="val">Status/bool</param>
	inline void SetActive(bool val) { isOn = val; };
	inline bool GetActive() { return isOn; };
private:
	std::function<bool(jute::jValue&)> callBack;
	bool isOn = false;
};
