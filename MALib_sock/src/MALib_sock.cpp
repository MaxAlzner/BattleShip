#include "..\include\MALib_sock.h"

#ifdef _MA_SOCK_H_
_MALIB_BEGIN

WSAData SockInfo;
SOCKET MySocket;
sockaddr_in MySocketAddress;

ULONG Address = 0;
USHORT Port = 0;

bool Initialized = false;
bool Connected = false;

bool InitializeSock()
{
	WSAStartup(0x202, &SockInfo);
	MySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	Initialized = true;
	return true;
}
bool UninitializeSock()
{
	closesocket(MySocket);
	WSACleanup();
	Initialized = false;
	return true;
}

bool HostConnection(uint port, string* outIP)
{
	if (!Initialized) return false;

	Port = port;

	MySocketAddress.sin_family = AF_INET;
	MySocketAddress.sin_port = htons(port);
	MySocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;
	int error = bind(MySocket, (const sockaddr*)&MySocketAddress, sizeof(MySocketAddress));
	if (error != 0)
	{
		Connected = false;
		return false;
	}

	if (outIP != NULL)
	{
		char* hostname = new char[64];
		gethostname(hostname, 64);

		addrinfo* result = 0;
		DWORD retreival = getaddrinfo(hostname, 0, 0, &result);
		addrinfo* link = 0;
		for (link = result; link != 0; link = link->ai_next)
		{
			if (link->ai_addr->sa_family == AF_INET)
			{
				SOCKADDR_IN* sockaddr = (SOCKADDR_IN*)link->ai_addr;
				*outIP = inet_ntoa(sockaddr->sin_addr);
			}
		}
		delete [] hostname;
	}

	error = listen(MySocket, 10);
	if (error != 0)
	{
		Connected = false;
		return false;
	}
	return true;
}

bool ConnectTo(uint port, const string ip)
{
	if (!Initialized) return false;
	
	Port = port;
	Address = inet_addr(ip);

	MySocketAddress.sin_family = AF_INET;
	MySocketAddress.sin_port = htons(20533);
	MySocketAddress.sin_addr.S_un.S_addr = Address;
	int error = connect(MySocket, (const sockaddr*)&MySocketAddress, sizeof(MySocketAddress));
	if (error != 0)
	{
		Connected = false;
		return false;
	}

	return true;
}

bool CheckConnection()
{
	return Connected;
}

bool Send(string buffer, uint size)
{
	if (buffer == 0 || size < 1) return false;
	int result = send(MySocket, buffer, size, 0);
	if (result != 0) return false;
	return true;
}
bool Receive(string buffer, uint size)
{
	if (buffer == 0 || size < 1) return false;
	int result = recv(MySocket, buffer, size, 0);
	if (result != 0) return false;
	return true;
}

_MALIB_END
#endif

void __stdcall DllMain()
{
	return;
}