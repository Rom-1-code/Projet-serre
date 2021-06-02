#pragma once
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")




struct tcpstruct
{
	SOCKET sock;
	SOCKET csock;
	SOCKADDR_IN sin;
	SOCKADDR_IN csin;
};

class server
{
private:

	int port = 2590;
	char buffer[10];
	int taille = 10;
	tcpstruct mystruct;
	float hygro;
	int tempext = 25;
	float tempint;



public:

	void createsocket();
	void connect();
	void readbuffer();
	void close();
	/*
	void sethygro(float hygro);
	void settempint(float tempint);
	*/


	static void WorkerThreadConnect(server* server);
};
