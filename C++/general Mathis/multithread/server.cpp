#include "server.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")



//using namespace std;
/*
void ReceivThread(SOCKET client)
{
	send(client, "Coucou", 6, 0);
}
*/
void ClientThread(SOCKET client)
{
	send(client, "Coucou", 6, 0);
}

void server::WorkerThreadConnect(server* server)
{
	while (1)
	{
		int sinsize = sizeof(server->mystruct.csin);
		server->mystruct.csock = accept(server->mystruct.sock,(SOCKADDR *)&server->mystruct.csin, &sinsize);

		std::thread clientThread(ClientThread, server->mystruct.csock);
		clientThread.detach();
	}
	
}


void server::createsocket()
{
#ifdef WIN32


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	int sock1 = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock1 == INVALID_SOCKET)
	{
		std::cout << "erreur de creation" << std::endl;
	}
	else
	{
		mystruct.sock = sock1;
		std::cout << "socket serveur valide" << std::endl;
	}
	
#endif
}

void server::connect()
{
	int resbindfct;
	

	
	mystruct.sin = { 0 };

	mystruct.sin.sin_addr.s_addr = htonl(INADDR_ANY);

	mystruct.sin.sin_family = AF_INET;

	mystruct.sin.sin_port = htons(port);
	
	resbindfct = bind(mystruct.sock, (SOCKADDR *)&mystruct.sin,sizeof(mystruct.sin));
	
	
	if (resbindfct != SOCKET_ERROR)
	{
		std::cout << "client connecte sur le port " <<port<< std::endl;
		listen(mystruct.sock, 5);
	}
	else
	{
		std::cout << "erreur de bind" << std::endl;
	}
	

	mystruct.csin = { 0 };
	
	std::thread workerconnect(WorkerThreadConnect,this);
	workerconnect.detach();
}


void server::readbuffer()
{
	std::cout << buffer << std::endl;
}

void server::close()
{
	closesocket(mystruct.sock);
}

/*
void server::sethygro(float hygro)
{
	this->hygro = hygro;
}

void server::settempint(float tempint)
{
	this->tempint = tempint;
}
*/