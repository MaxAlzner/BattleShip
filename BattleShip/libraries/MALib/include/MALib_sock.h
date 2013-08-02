#pragma once

#include <MALib.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

#ifndef _MA_SOCK_H_
#define _MA_SOCK_H_
_MALIB_BEGIN

MALIB_API bool InitializeSock();
MALIB_API bool UninitializeSock();

MALIB_API bool HostConnection(uint port, string* outIP);

MALIB_API bool ConnectTo(uint port, const string ip);

MALIB_API bool CheckConnection();

MALIB_API bool Send(string buffer, uint size);
MALIB_API bool Receive(string buffer, uint size);

_MALIB_END
#endif