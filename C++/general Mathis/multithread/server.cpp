#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "server.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>


#ifdef WIN32
#include <stdlib.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")
#endif

#include "DataQueue.h"
#include <algorithm>



std::mutex server::synchro;
std::vector<SOCKET> server::connectedClients;

void ClientThread(SOCKET client)
{
	send(client, "Coucou", 6, 0);
}

void server::ClientThreadLocal(SOCKET client)
{
	char buffer[500];
	int n = 0;

		n = recv(client, buffer, 500, 0);

		for (int i = 0; i < n; i++)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");

	

	printf("Client deconnecte\n");
	synchro.lock();

	std::vector<SOCKET>::iterator it = std::find(connectedClients.begin(), connectedClients.end(), client);
	if (it != connectedClients.end())
	{
		connectedClients.erase(it);
	}

	synchro.unlock();
}

void server::WorkerThreadConnect(server* server)
{
	int sinsize = sizeof(server->mystruct.csinrecup);

	SOCKET clientSock = accept(server->mystruct.sockrecup,(SOCKADDR *)&server->mystruct.csinrecup, &sinsize);

	if (clientSock != INVALID_SOCKET)
	{
		synchro.lock();
		connectedClients.push_back(clientSock);
		synchro.unlock();
		std::thread clientThread(ClientThread, server->mystruct.sockrecup);
		clientThread.detach();
	}
	
}

void server::WorkerThreadConnectClient(server* server)
{
	while (1)
	{
		SerreData * data = DataQueue::getInstance()->getData();
		if (data != nullptr)
		{
			synchro.lock();
			char buffer[500];
			snprintf(buffer, 500, "%.2f;%.2f;%.2f;%.2f\n", data->temperatureInterieure, data->humiditeInterieure, data->temperatureExterieure, data->humiditeSol);
			
			for(int i = 0; i < connectedClients.size(); i++)
			{
				send(connectedClients[i], buffer, strlen(buffer), 0);
			}

			synchro.unlock();
		}

		Sleep(50);
	}
}


void server::createsocket()
{
#ifdef WIN32


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

#endif
	int sock2 = socket(AF_INET, SOCK_STREAM, 0);

	if (sock2 == INVALID_SOCKET)
	{
		std::cout << "erreur de creation du socket local" << std::endl;
	}
	else
	{
		mystruct.sockrecup = sock2;
		std::cout << "socket local valide" << std::endl;
	}
	

}

void server::connect()
{

	int resbindfct2;

	
	mystruct.sin = { 0 };
	mystruct.sin.sin_addr.s_addr = htonl(INADDR_ANY);
	mystruct.sin.sin_family = AF_INET;
	mystruct.sin.sin_port = htons(port1);

	resbindfct2 = bind(mystruct.sockrecup, (SOCKADDR *)&mystruct.sin, sizeof(mystruct.sin));


	if (resbindfct2 != SOCKET_ERROR)
	{
		std::cout << "client local connecte sur le port " << port1 << std::endl;
		listen(mystruct.sockrecup, 5);
	}
	else
	{
		std::cout << "erreur de bind sur le port local " <<port1<< std::endl;
	}
	

	//mystruct.csin = { 0 };
	mystruct.csinrecup = { 0 };
	
	std::thread workerconnect(WorkerThreadConnect,this);
	workerconnect.detach();
	std::thread workerconnectclient(WorkerThreadConnectClient,this);
	workerconnectclient.detach();
	
}


void server::readbuffer()
{
	std::cout << buffer << std::endl;
}


tcpstruct* server::getstruct()
{
	return &mystruct;
}
