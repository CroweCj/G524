#include "socket_global.h"
#include <time.h>

SOCKET UdpSocket::mSocket = INVALID_SOCKET;
bool UdpSocket::mIsBind = false;
UdpSocket::UdpSocket()
{
}

UdpSocket::~UdpSocket()
{
	closesocket(mSocket);
	WSACleanup();
}

SOCKET UdpSocket::getSocket()
{
	if (mSocket == INVALID_SOCKET)
	{
		WSADATA  wsaData;
		WORD  sockVersion = MAKEWORD(2, 2);
		if (WSAStartup(sockVersion, &wsaData) != 0)
		{
			return INVALID_SOCKET;
		}
		mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		int mode = 1;
		ioctlsocket(mSocket, FIONBIO, (u_long FAR*) & mode);
	}

	return mSocket;
}

bool UdpSocket::sockBind(const char* ip, int port, int timeout)
{
	if (!mIsBind)
	{
		sockaddr_in mHostAddr;
		mHostAddr.sin_family = AF_INET;
		mHostAddr.sin_port = htons(port);
		mHostAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		mHostAddr.sin_addr.s_addr = htons(INADDR_ANY);
		clock_t startTime = clock();
		while (bind(mSocket, (sockaddr*)&mHostAddr, sizeof(mHostAddr)) == SOCKET_ERROR)
		{
			if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
				>= timeout)
			{
				return false;
			}
		}
		mIsBind = true;
		return true;
	}
	return true;
}
