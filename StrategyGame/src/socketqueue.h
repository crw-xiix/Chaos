#pragma once
#include "pch.h"
#include "threadqueue.h"
#include "../3rd/easywsclient.hpp"

class SocketQueue {
public:
	SocketQueue(std::string url );
	bool Send(std::string val);
	bool Avail();
	std::string Get();
	bool Start();
	void Process();
	void Stop();

private:
	std::unique_ptr<easywsclient::WebSocket> ws;
	std::string url;
	ThreadQueue<std::string> qOut;
	ThreadQueue<std::string> qIn;
//Stuff for thread access...
	static SocketQueue *instance;
};
