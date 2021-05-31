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


void SendThread(SOCKET socketsend)
{
	send(socketsend,"yo bb",5, 0); 
}

void client::WorkerThreadSend(client* client)
{
	while (1)
	{
		std::thread clientThread(SendThread, client->mystruct.sock);
		clientThread.detach();
	}

}

void client::createsocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	mystruct.sock = socket(AF_INET, SOCK_STREAM, 0);

	if (mystruct.sock == INVALID_SOCKET)
	{
		printf("socket invalide \n");
	}
	else
	{
		printf("\n");
		printf("socket cree \n");
	}
}

void client::connectnode()
{
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
	const char *hostname = "192.168.65.70";

	

		/*
			if (hostinfo == NULL)
			{
				fprintf(stderr, "Unknown host %s.\n", hostname);
				exit(EXIT_FAILURE);
			}
		*/

	
	
	mystruct.sin.sin_addr.s_addr = inet_addr(hostname);
	mystruct.sin.sin_family = AF_INET;
	mystruct.sin.sin_port = htons(3000); 

	if (connect(mystruct.sock, (SOCKADDR *)&mystruct.sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("erreur de connexion \n");
	}
	else
	{
		printf("connecte \n");
		std::thread workersend(WorkerThreadSend,this);
		workersend.detach();
	}
	//std::thread workerconnect(WorkerThreadConnect,&mystruct);
	

	
}
/*
void client::senddata()
{
	send(sock, buffertosend, strlen(buffertosend), 0);
}
*/
clienttcpstruct* client::getstruct()
{
	return &this->mystruct;
}

void client::close()
{
	closesocket(mystruct.sock);
}