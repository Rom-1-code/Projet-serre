#include "Serveurcpp.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")


using namespace std;


void Serveurcpp::createsocket()
{
#ifdef WIN32


	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	

	try
	{
		int sock1 = socket(AF_INET, SOCK_STREAM, 0);
		sock = sock1;
		cout << "socket valide" << endl;
	}
	catch(ErreurCreation)
	{
		cout << "erreur de creation" << endl;
	}
/*
	if (sock1 == INVALID_SOCKET)
	{
		cout << "erreur de creation" << endl;
	}
	else
	{
		sock = sock1;
		cout<<"socket valide"<<endl;
	}
*/
#endif
}

void Serveurcpp::connect()
{
	SOCKADDR_IN sin = { 0 };

	sin.sin_addr.s_addr = htonl(INADDR_ANY); 

	sin.sin_family = AF_INET;

	sin.sin_port = htons(port);
/*
	if (bind(sock, (SOCKADDR *)&sin, sizeof sin) == SOCKET_ERROR)
	{
		cout << "erreur de bind" << endl;
	}

	if (listen(sock, 5) == SOCKET_ERROR)
	{
		cout << "erreur d'ecoute" << endl;
	}
*/

	try
	{
		bind(sock, (SOCKADDR *)&sin, sizeof sin);
		listen(sock, 5);
	}
	catch(Erreurbind)
	{
		cout << "erreur de bind ou de listen, verifiez le port" << endl;
	}

	SOCKADDR_IN csin = { 0 };
	SOCKET csock;

	int sinsize = sizeof csin;

	try
	{
		csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
		socketclient = csock;
		printf("csock valide\n");

	}
	catch (Erreuraccept)
	{
		cout << "socket erreur" << endl;
	}
	
/*
	if (csock == INVALID_SOCKET)
	{
		
	}
	else
	{
		
	}

*/
}

void Serveurcpp::receiv()
{
	int recvLen = 0;
	int recvsock;
	bool findetrame = false;
	int i=0;

	
	
	recvsock = recv(socketclient, buffer, taille-1, 0);
	


	buffer[taille] = 0x00;
	 
	i = strlen(buffer);


	if (buffer[i - 1] == ';') //le message se termine bien par ;
	{
		findetrame = true;
	}



		if (findetrame == true)
		{
			if (strlen(buffer) == 5 && buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 's' && buffer[3] == 't' && buffer[4] == ';')
			{
				send(socketclient, "c'est un envoi test", 19, 0);
				send(socketclient, "\n", 2, 0);
				send(socketclient, "arret de la connexion", 21, 0);
				closesocket(socketclient);
			}
			else
			{
				send(socketclient, "bonne commande mais pas de caractere de fin de trame", 52, 0);
				send(socketclient, "\n", 2, 0);
				send(socketclient, "arret de la connexion", 21, 0);
				closesocket(socketclient);
			}
		}
		else if(strlen(buffer) == 4 && buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 's' && buffer[3] == 't')
		{
			send(socketclient, "pas de caractere de fin de trame", 51, 0);
			send(socketclient, "\n", 2, 0);
			send(socketclient, "arret de la connexion", 21, 0);
			closesocket(socketclient);
		}
		else
		{
			send(socketclient, "mauvaise commande", 17, 0);
			send(socketclient, "\n", 2, 0);
			send(socketclient, "arret de la connexion", 21, 0);
			closesocket(socketclient);
		}
}

		


void Serveurcpp::readbuffer()
{
	cout << buffer << endl;
}
