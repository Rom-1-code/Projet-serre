#include "client.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

void WorkerThreadConnect(clienttcpstruct* mystruct)
{
	while (1)
	{
		if (connect(mystruct->sock, (SOCKADDR *)&mystruct->sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
		{
			printf("erreur de connexion \n");
		}
		else
		{
			printf("connecte \n");
		}
	}

}

void client::createsocket()
{
	

	mystruct.sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		printf("socket invalide \n");
	}
	else
	{
		printf("socket cree \n");
	}
}

void client::connectnode()
{
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
	const char *hostname = "192.168.65.8";

	

		/*
			if (hostinfo == NULL)
			{
				fprintf(stderr, "Unknown host %s.\n", hostname);
				exit(EXIT_FAILURE);
			}
		*/

	
	
	mystruct.sin.sin_addr.s_addr = inet_addr(hostname);
	mystruct.sin.sin_family = AF_INET;
	mystruct.sin.sin_port = htons(2500); 

	std::thread workerconnect(WorkerThreadConnect,&mystruct);
	

	
}

void client::senddata()
{
	send(sock, buffertosend, strlen(buffertosend), 0);
}

clienttcpstruct* client::getstruct()
{
	return &this->mystruct;
}

void client::close()
{
	closesocket(sock);
}