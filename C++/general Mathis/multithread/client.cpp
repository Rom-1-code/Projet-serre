#include "client.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")


void SendThread(client * client)
{
	while (1)
	{
		client::sendReadRequest(client, 100, 4);

		Sleep(100);
	}
}

void SendParameters(client* client)
{
	char buffer[6];
	std::stringstream ss;


	ss << std::hex << client->gethygro();
	while (1)
	{
	
	}
}

void client::sendReadRequest(client* client, int startAddress, int nbWord)
{
	char buffer[12];

	int transactionId = client->transactionId++;

	buffer[0] = (transactionId & 0xFF00) >> 8;
	buffer[1] = transactionId & 0x00FF;
	buffer[2] = 0x00;
	buffer[3] = 0x00;
	buffer[4] = 0x00;
	buffer[5] = 0x06;
	buffer[6] = 0xFF;
	buffer[7] = 0x03;
	buffer[8] = (startAddress & 0xFF00) >> 8;
	buffer[9] = startAddress & 0x00FF;
	buffer[10] = (nbWord & 0xFF00) >> 8;
	buffer[11] = nbWord & 0x00FF;

	modbusrequest readRequest;
	readRequest.function = 0x03;
	readRequest.transactionId = transactionId;
	readRequest.startAddress = startAddress;
	readRequest.nbData = nbWord;
	client->addModbusRequest(readRequest);

	send(client->mystruct.sock, buffer, 12, 0);
}

void ReceivThread(client* client)
{
	char buffer[200];
	float f;
	uint32_t tempint;
	uint32_t hygro;
	uint32_t restoanalyse;

	while (1)
	{
		int n = 0;

		if ((n = recv(client->getstruct()->sock, buffer, 200, 0)) < 0)
		{
			printf(" Erreur de reception \n");
		}

		buffer[n] = '\0';

		client->getModbusRequest(buffer[0]);

		uint16_t transactionId = ((unsigned char)buffer[0] << 8) | (unsigned char)buffer[1];
		printf("Numero de transaction : %d", transactionId);
		printf("\n");

		modbusrequest request = client->getModbusRequest(transactionId);
		
		
		std::string str = "0x";
		char* buffertemp = new char[n];

		if (request.startAddress == 100 && request.function == 3)
		{
			for (int i = 0; i < n; i++)
			{
				printf("%2.2hhx ", buffer[i]);
			}
			printf("\n");
			for (int i = 9; i < (9+4); i++)
			{
				snprintf(buffertemp,4, "%2.2hhx", buffer[i]);
				str += buffertemp;
			}
			printf("\n");

			sscanf_s(str.c_str(), "%x", &tempint);
			f = *((float*)&tempint);
			printf(" la temperature est a %.3f degre avec le code hexa 0x%08x  \n",f,tempint);
			client->settemp(tempint);
			

			str = "0x";
			for (int i = 13; i < (13 + 4); i++)
			{
				snprintf(buffertemp, 4, "%2.2hhx", buffer[i]);
				str += buffertemp;
			}
			printf("\n");
			sscanf_s(str.c_str(), "%x", &hygro);
			f = *((float*)&hygro);
			printf(" l'hygrometrie est a %.3f pourcent avec le code hexa 0x%08x  \n",f, hygro);
			client->sethygro(hygro);
		}
		else
		{
			printf("Erreur - mauvaise adresse \n");
		}

		

		if (request.function >= 0)
		{
			printf("Requete %d trouvee :\n", transactionId);
			printf("Fonction : %d\n", request.function);
			printf("Adresse debut : %d\n", request.startAddress);
			printf("Nombre mots : %d\n", request.nbData);
		}
		else
		{
			printf("Erreur - Requete %d inconnue\n", transactionId);
		}


	}
}

void client::WorkThreadReceiv(client* client)
{
	std::thread clientThread(ReceivThread, client);
	clientThread.detach();
}

void client::WorkerThreadSend(client* client)
{
	std::thread clientThread(SendThread, client);
	clientThread.detach();
}

void client::WorkerThreadParameters(client* client)
{
	std::thread clientparameters(SendParameters, client);
}

void client::createsocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	mystruct.sock = socket(AF_INET, SOCK_STREAM, 0);
	mystruct.sockparameters = socket(AF_INET, SOCK_STREAM, 0);

	if (mystruct.sock == INVALID_SOCKET)
	{
		printf("socket carte invalide \n");
	}
	else
	{
		printf("\n");
		printf("socket carte cree \n");
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
	mystruct.sin.sin_port = htons(502);

	mystruct.sinparameters.sin_addr.s_addr = inet_addr("127.0.0.1");
	mystruct.sin.sin_family = AF_INET;
	mystruct.sin.sin_port = htons(2525);

	if (connect(mystruct.sock, (SOCKADDR *)&mystruct.sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("erreur de connexion a la carte \n");
	}
	else
	{
		printf("connecte a la carte \n");
		std::thread workersend(WorkerThreadSend, this);
		workersend.detach();
		std::thread workerreceiv(WorkThreadReceiv, this);
		workerreceiv.detach();
	}

	if (connect(mystruct.sockparameters, (SOCKADDR *)&mystruct.sinparameters, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("erreur de connexion au serveur tcp \n");
	}
	else
	{
		printf("connecte au serveur tcp \n");
		std::thread workerparameters(WorkerThreadParameters, this);
		workerparameters.detach();
	}
}

clienttcpstruct* client::getstruct()
{
	return &mystruct;
}

float client::gethygro()
{
	return this->hygrometrie;
}

float client::gettemp()
{
	return this->temperature;
}


void client::settemp(uint32_t temp)
{
	this->temperature = (float)temp;
	this->tempset = true;
}

void client::sethygro(uint32_t hygro)
{
	this->hygrometrie = (float)hygro;
	this->hygroset = true;
}

