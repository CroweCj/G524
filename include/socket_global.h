#pragma once
#include <WINSOCK2.H>

class UdpSocket
{
public:
	~UdpSocket();
	static SOCKET getSocket();
	static bool sockBind(const char* ip, int port,int timeout);
private:
	UdpSocket();
	static SOCKET mSocket;
	static bool mIsBind;
};