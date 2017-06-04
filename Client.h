#pragma once

#include <windows.h>
#pragma comment(lib,"ws2_32.lib") 

class Client
{
public:
	Client(char* addr, int port);
	~Client();
	int sendTcpData(const char* data, const int dataLength);
	int recvTcpData(char* data, int bufferLength);
private:
	SOCKET _tcp_socket;
};

