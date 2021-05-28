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
	int socketclient;
	char buffer[10];
	int taille = 10;
	tcpstruct mystruct;



public:

	void createsocket();
	tcpstruct* getstruct();
	void connect();
	void receiv();
	void readbuffer();
	void close();


	static void WorkerThreadConnect(server* server);
};
