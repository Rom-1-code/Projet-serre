#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "servercpp.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <fstream>
#include <vector>
#include <fstream>
#include <iterator>
#include <iomanip>
#pragma comment (lib,"ws2_32.lib")



using namespace std;


void servercpp::createsocket()
{
#ifdef WIN32


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	int sock1 = socket(AF_INET, SOCK_STREAM, 0);

	if (sock1 == INVALID_SOCKET)
	{
		cout << "erreur de creation" << endl;
	}
	else
	{
		sock = sock1;
		cout << "socket valide" << endl;
	}

#endif
}

void servercpp::connectsock()
{
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
	const char *hostname = ip;

	hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
	
	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
		printf("hote inconnu \n");
	}
	else
	{
		sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
		sin.sin_port = htons(port); /* on utilise htons pour le port */
		sin.sin_family = AF_INET;

		if (connect(sock, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
		{
			printf("erreur de connexion \n");
		}
		else
		{
			printf("connexion réussie \n");
		}
	}
	
}

void servercpp::sendtrameReadHoldingTempWire() //capteur 11
{
	char buffer[20];
	

	buffer[0] = 0x00;
	buffer[1] = 0x00;
	buffer[2] = 0x00;
	buffer[3] = 0x00;
	buffer[4] = 0x00;
	buffer[5] = 0x06;
	buffer[6] = 0x00;
	buffer[7] = 0x03;
	buffer[8] = 0x00;
	buffer[9] = 0x64;		
	buffer[10] = 0x00;
	buffer[11] = 0x02;

	
	if (send(sock, buffer, 12, 0) < 0)
	{

		printf("erreur d'envoi \n");
	}
	
}

void servercpp::sendtrameReadHoldingHumiWire() //code fonction 03
{
	char buffer[20];


	buffer[0] = 0x00;
	buffer[1] = 0x00;
	buffer[2] = 0x00;
	buffer[3] = 0x00;
	buffer[4] = 0x00;
	buffer[5] = 0x06;
	buffer[6] = 0x00;
	buffer[7] = 0x03;
	buffer[8] = 0x00;
	buffer[9] = 0x66;
	buffer[10] = 0x00;
	buffer[11] = 0x02;


	if (send(sock, buffer, 12, 0) < 0)
	{

		printf("erreur d'envoi \n");
	}
}

void servercpp::receivReadHoldingResgisterTempWire() //code fonction 03
{

	int n = 0;

	if ((n = recv(sock, bufferreceivs1,13 , 0)) < 0)
	{
		printf("erreur de reception \n");
	}

	buffer[n] = '\0';
}

void servercpp::receivReadHoldingResgisterHumiWire()
{
	int n = 0;

	if ((n = recv(sock, bufferreceivs2, 13, 0)) < 0)
	{
		printf("erreur de reception \n");
	}

	buffer[n] = '\0';
}

void servercpp::readbufferTempWire()
{
	bool loop = true;
	int indice;
	int i = 0;
	int taille;
	taille =13;
	

	
	for (int i = 0; i < taille; i++)
	{
		printf("%2.2hhx ", bufferreceivs1[i]);
	}
	printf("\n");

	//pour la simulation j'utilise le meme tableau de char 
	//vous devez utilise le vrai bufferreceiv et commencer la boucle au bon endroit

	//partie simulation

/*
	bufferreceiv[0] = 0x42;
	bufferreceiv[1] = 0x96;
	bufferreceiv[2] = 0x80;
	bufferreceiv[3] = 0x00;
*/	
	char bufferTemp[60];
	string s = "0x";

	for (int i = 0; i < 13; i++)
	{
		snprintf(bufferTemp, 4, "%2.2hhx", bufferreceivs1[i]);
		s += bufferTemp;
	}

	uint32_t num;
	sscanf_s(s.c_str(), "%x", &num);
	float f = *((float*)&num);
	printf("la SIMULATION des octets :  0x%08x vaut %.3f \n", num, f);
}

void servercpp::readbufferHumiWire()
{
	bool loop = true;
	int indice;
	int i = 0;
	int taille;
	taille = 13;
	


	for (int i = 0; i < taille; i++)
	{
		printf("%2.2hhx ", bufferreceivs2[i]);
	}
	printf("\n");

	//pour la simulation j'utilise le meme tableau de char 
	//vous devez utilise le vrai bufferreceiv et commencer la boucle au bon endroit

	//partie simulation

/*
	bufferreceiv[0] = 0x42;
	bufferreceiv[1] = 0x96;
	bufferreceiv[2] = 0x80;
	bufferreceiv[3] = 0x00;
*/
	char bufferHumi[60];
	string s = "0x";

	for (int i = 0; i < 13; i++)
	{
		snprintf(bufferHumi, 4, "%2.2hhx", bufferreceivs2[i]);
		s += bufferHumi;
	}

	uint32_t num;
	sscanf_s(s.c_str(), "%x", &num);
	float f = *((float*)&num);
	printf("la SIMULATION des octets :  0x%08x vaut %.3f \n", num, f);
}

