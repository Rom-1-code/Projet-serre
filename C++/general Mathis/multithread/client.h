#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")



	struct clienttcpstruct
	{
		SOCKET sock;
		SOCKADDR_IN sin;
	};

	class client
	{
	private:

		SOCKET sock;
		char buffertosend[9] = " yo node";
		clienttcpstruct mystruct;


	public:

		clienttcpstruct* getstruct();
		void createsocket();
		void connectnode();
		void senddata();
		void close();
	};

