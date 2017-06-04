#pragma once

#include <windows.h>
#pragma comment(lib,"ws2_32.lib") 

class Server
{
public:
	Server(int port);
	~Server();
	void acceptTcpSocket();
	int sendTcpData(SOCKET* socket, const char* data, const int dataLength);
	int recvTcpData(SOCKET* socket, char* data, int bufferLength);
private:
	SOCKET _tcp_socket_listen;
};

