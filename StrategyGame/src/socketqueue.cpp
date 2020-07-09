#include "pch.h"
#include "socketqueue.h"
#include "../3rd/easywsclient.hpp"

/* Ugly Windows code.....*/

#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif

SocketQueue::SocketQueue(std::string url)
{
    this->url = url;
	instance = this;
}

bool SocketQueue::Send(std::string val)
{
    qOut.Enqueue(val);
    return true;
}

bool SocketQueue::Avail()
{
    return (qIn.Size() > 0);
}

std::string SocketQueue::Get()
{
    return qIn.Dequeue();
}

bool SocketQueue::Start()
{
    using easywsclient::WebSocket;
    //More ugly Windows code.
#ifdef _WIN32
    INT rc;
    WSADATA wsaData;
    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return true;
    }
#endif
    ws = std::unique_ptr<WebSocket>(WebSocket::from_url(url));
    return true;
}

void SocketQueue::Process()
{
    using easywsclient::WebSocket;
    if (ws) {
        if (ws->getReadyState() != WebSocket::CLOSED) {
            WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
            
            //Send if there is something to send.
            if (SocketQueue::instance->qOut.Size() > 0) {
                ws->send(qOut.Dequeue());
            }
            ws->poll();
            ws->dispatch([wsp](const std::string& message) {
                printf(">>> %s\n", message.c_str());
                SocketQueue::instance->qIn.Enqueue(message);
                //we got a message, lets reply with status
                //std::string wtf = p.GetJson();
                //wsp->send(wtf);
                });
        }
        else {
            Stop();
        }
    }
}

void SocketQueue::Stop()
{
#ifdef _WIN32
    WSACleanup();  //More Windows slop
#endif
    //This is to notify the game that the socket died.
    SocketQueue::instance->qIn.Enqueue("{\"socket\":\"closed\"}");
    // N.B. - unique_ptr will free the WebSocket instance upon return:
}

//statics
SocketQueue* SocketQueue::instance = nullptr;

