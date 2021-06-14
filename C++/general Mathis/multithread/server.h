#pragma once
#include <string>

#ifdef WIN32
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")
#endif

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h> 
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#endif

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
	tcpstruct* getstruct();
	


	static void WorkerThreadConnect(server* server);
	static void WorkerThreadConnectClient(server* server);
	static void ClientThreadLocal(SOCKET client);
};
