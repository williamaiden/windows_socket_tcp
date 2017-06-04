#include "Server.h"
#include <stdio.h>

Server::Server(int port)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		perror("WSASartup error !");
		return;
	}
	_tcp_socket_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_tcp_socket_listen == INVALID_SOCKET){
		perror("socket error !");
		WSACleanup();
		return;
	}
	SOCKADDR_IN local_config;
	local_config.sin_port = htons(port);
	local_config.sin_family = AF_INET;
	local_config.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(_tcp_socket_listen, (struct sockaddr *)&local_config, sizeof(local_config)) == SOCKET_ERROR){
		perror("bind error !");
		closesocket(_tcp_socket_listen);
		WSACleanup();
		return;
	}
	if (listen(_tcp_socket_listen, SOMAXCONN) == SOCKET_ERROR){
		perror("listen error !");
		closesocket(_tcp_socket_listen);
		WSACleanup();
		return;
	}
}


Server::~Server()
{
	if (_tcp_socket_listen != INVALID_SOCKET){
		if (closesocket(_tcp_socket_listen) == 0){
			_tcp_socket_listen = INVALID_SOCKET;
			WSACleanup();
			return;
		}
		perror("close socket error.");
	}
}

void Server::acceptTcpSocket(){
	bool flag = true;
	while (flag){
		SOCKADDR_IN client_config;
		int addr_len = sizeof(client_config);
		SOCKET tcp_socket = accept(_tcp_socket_listen, (struct sockaddr*)&client_config, &addr_len);
		if (tcp_socket == SOCKET_ERROR){
			perror("accept socket error !");
			break;
		}
		while (flag){
			char recv[1024];
			if (recvTcpData(&tcp_socket, recv, sizeof(recv)) <= 0){
				perror("recv error !");
				break;
			}
			char* data = "Hi, I'm William Aiden !";
			if (sendTcpData(&tcp_socket, data, strlen(data)) <= 0){
				perror("send error !");
				break;
			}
		}
	}
}

int Server::sendTcpData(SOCKET* socket, const char* data, const int dataLength){
	if (data != NULL && *socket != INVALID_SOCKET && dataLength > 0){
		return send(*socket, data, dataLength, 0);
	}
	return 0;
}

int Server::recvTcpData(SOCKET* socket, char* data, int bufferLength){
	int ret = 0;
	if (data != NULL && *socket != INVALID_SOCKET && bufferLength > 0){
		ret = recv(*socket, data, bufferLength, 0);
		if (ret > 0){
			data[ret] = '\0';
			printf("%s\n", data);
		}
	}
	return ret;
}

int main(){
	Server s(8086);
	s.acceptTcpSocket();

	return 0;
}
