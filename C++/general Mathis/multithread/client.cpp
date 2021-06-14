#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "client.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")
#endif

#include "DataQueue.h"

void SendThread(client * client)
{
	while (1)
	{
		
		client::sendReadRequest(client, 100, 4); 
		Sleep(1000);
	}
}


void client::sendReadRequest(client* client, int startAddress, int nbWord)
{
	char buffer[12];

	uint16_t transactionId = client->transactionId++;

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
	float temperatureInterieure;
	float temperatureExterieure=0; //simulee
	float humiditeInterieure;
	float humiditesol1;
	float humiditesol2;
	float humiditesol3;
	uint32_t tempint;
	uint32_t tempint2;
	uint32_t hygro;
	uint32_t humi1;
	uint32_t humi2;
	uint32_t humi3;
	uint32_t restoanalyse;

	while (1)
	{
		int n = 0;

		if ((n = recv(client->getstruct()->sock, buffer, 200, 0)) < 0)
		{
			printf(" Erreur de reception \n");
		}

		buffer[n] = '\0';

		uint16_t transactionId = ((unsigned char)buffer[0] << 8) | (unsigned char)buffer[1];
		printf("Numero de transaction : %d", transactionId);
		printf("\n");

		modbusrequest request = client->getModbusRequest(transactionId);
		
		
		std::string str = "0x";
		char* buffertemp = new char[n];

	
			if (request.startAddress == 100)
			{

				for (int i = 0; i < n; i++)
				{
					printf("%2.2hhx ", buffer[i]);
				}
			

				printf("\n");

				for (int i = 9; i < (9 + 4); i++)
				{
					snprintf(buffertemp, 4, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}
				printf("\n");


				sscanf_s(str.c_str(), "%x", &tempint);
				temperatureInterieure = *((float*)&tempint);
			
				
				if(buffer[9] & (1<<7)) //on cherche à connaitre le signe du bit de poids fort
				{
					printf("nombre negatif \n");
				}
				printf(" la température est a %.3f degre avec le code hexa 0x%08x  \n", temperatureInterieure, tempint);



				str = "0x";
				for (int i = 13; i < (13 + 4); i++)
				{
					snprintf(buffertemp, 4, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}
				printf("\n");
				sscanf_s(str.c_str(), "%x", &hygro);
				humiditeInterieure = *((float*)&hygro);
				printf(" l'hygrometrie est a %.3f pourcent avec le code hexa 0x%08x  \n", humiditeInterieure, hygro);

				
				delete buffertemp;


				client::sendReadRequest(client, 300, 8);
				
			}
			else if(request.startAddress == 300)
			{

				for (int i = 0; i < n; i++)
				{
					printf("%2.2hhx ", buffer[i]);
				}

				printf("\n");

				str = "0x";
				for (int i = 9; i < 13; i++) //premiere valeur d'humidite
				{
					snprintf(buffertemp, 8, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}
				printf("\n");

				sscanf_s(str.c_str(), "%x", &humi1);
				humiditesol1 = *((float*)&humi1);

				str = "0x";
				for (int i = 13; i < 17; i++) //deuxieme valeur d'humidite
				{
					snprintf(buffertemp, 8, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}

				sscanf_s(str.c_str(), "%x", &humi2);
				humiditesol2 = *((float*)&humi2);

				str = "0x";
				for (int i = 17; i < 21 ; i++) //troisieme valeur d'humidite
				{
					snprintf(buffertemp, 8, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}

				sscanf_s(str.c_str(), "%x", &humi3);
				humiditesol3 = *((float*)&humi3);
/*
				str = "0x";
				for (int i = 21; i < 25; i++) //valeur de temperature exterieure
				{
					snprintf(buffertemp, 8, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}

				sscanf_s(str.c_str(), "%x", &tempint2);
				temperatureExterieure = *((float*)&tempint2);

				str = "0x";
				for (int i = 25; i < 29; i++)
				{
					snprintf(buffertemp, 8, "%2.2hhx", buffer[i]);
					str += buffertemp;
				}*/
				/*
				sscanf_s(str.c_str(), "%x", &tempint2);
				temperatureExterieure = *((float*)&tempint2);
				*/
				//printf("la temperature exterieure est de %.3f degre \n", temperatureExterieure);

				//conversion et moyenne des 3 valeurs d'humidite des sols :

				float moyenne = ((humiditesol3 + humiditesol2 + humiditesol1)* 0.025) / 3;
				moyenne = moyenne * 1000;

				printf(" l humidite moyenne du sol est a %.3f pourcent \n", moyenne); //hexa 0x%08x humi1

				DataQueue::getInstance()->addData(new SerreData(temperatureInterieure, humiditeInterieure, moyenne, temperatureExterieure));
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


void client::createsocket()
{
#ifdef WIN32

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	mystruct.sock = socket(AF_INET, SOCK_STREAM, 0);

#endif

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

void client::connectcard()
{
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; 
	const char *hostname = "192.168.65.8";
	

	mystruct.sin.sin_addr.s_addr = inet_addr(hostname);
	mystruct.sin.sin_family = AF_INET;
	mystruct.sin.sin_port = htons(502);

	
	do
	{
		printf("Tentative de connexion a la carte.. \n");

	} while (connect(mystruct.sock, (SOCKADDR *)&mystruct.sin, sizeof(SOCKADDR)) == SOCKET_ERROR);

	printf("connecte a la carte \n");
	std::thread workersend(WorkerThreadSend, this);
	workersend.detach();
	std::thread workerreceiv(WorkThreadReceiv, this);
	workerreceiv.detach();
	
}

clienttcpstruct* client::getstruct()
{
	return &mystruct;
}



