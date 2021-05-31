#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")



	struct clienttcpstruct
	{
		SOCKET sock;
		SOCKADDR_IN sin;
		char buffertosend[9] = " yo node";
	};

	class client
	{
	private:

		
		
		clienttcpstruct mystruct;


	public:

		clienttcpstruct* getstruct();
		void createsocket();
		void connectnode();
		static void WorkerThreadSend(client* client);
		//void senddata();
		void close();
	};

