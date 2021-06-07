#include "TCPClient.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

void Client::CreateSocket()
{

	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		printf("Socket Invalide \n");
	}
	else
	{
		printf("Socket Cree \n");
	}
}

void Client::ConnectCarte()
{
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 _CRT*/
	const char *hostname = "192.168.65.8";

	sin.sin_addr.s_addr = inet_addr(hostname);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(502);

	if (connect(sock, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("Erreur de connexion \n");
	}
	else
	{
		printf("Connecter \n\n");
	}
}

/*----------Envoi d'une trame à la carte E/S----------*/
void Client::SendData(bool relay1, bool relay2, bool relay3, bool relay4)
{
	cout << "\nEnvoi d'une trame\n";
	buffer[0] = 0x00;
	buffer[1] = 0x00;
	buffer[2] = 0x00;
	buffer[3] = 0x00;
	buffer[4] = 0x00;
	buffer[5] = 0x08;
	buffer[6] = 0x00;
	buffer[7] = 0x0F;
	buffer[8] = 0x00;
	buffer[9] = 0x64; // Adresse du capteur.
	buffer[10] = 0x00;
	buffer[11] = 0x04;
	buffer[12] = 0x01;

	char processedValue = (relay4 ? 1 : 0) << 3 | (relay3 ? 1 : 0) << 2 | (relay2 ? 1 : 0) << 1 | (relay1 ? 1 : 0);

	buffer[13] = processedValue;

	int i = 0;

	while (i < 14)
	{
		printf ("%2.2hhx ", buffer[i]);
		i++;
	}

	cout << "\n \n";

	send(sock, buffer, 14, 0);

}

void Client::Close()
{
	cout << "C'est CIAO \n";
	closesocket(sock);
}

