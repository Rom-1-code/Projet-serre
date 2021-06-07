#pragma once
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

#include <mutex>
#include <vector>


struct tcpstruct
{
	SOCKET sock;
	SOCKET csock;
	SOCKET sockrecup;
	SOCKET csockrecup;
	SOCKADDR_IN sin;
	SOCKADDR_IN csin;
	SOCKADDR_IN sinrecup;
	SOCKADDR_IN csinrecup;
};

class server
{
private:

	int port = 2590;
	int port1 = 2525;
	char buffer[10];
	int taille = 10;
	tcpstruct mystruct;


	static std::mutex synchro;
	static std::vector<SOCKET> connectedClients;


public:

	void createsocket();
	void connect();
	void readbuffer();
	void close();
	tcpstruct* getstruct();
	


	static void WorkerThreadConnect(server* server);
	static void WorkerThreadConnectClient(server* server);
	static void ClientThreadLocal(SOCKET client);
};
