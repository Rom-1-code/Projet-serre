#include "server.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <stdlib.h>



using namespace std;

void ClientThread(SOCKET client)
{
	send(client, "Coucou", 6, 0);
}

void server::WorkerThreadConnect(server* server)
{
	while (1)
	{
		int sinsize = sizeof(server->mystruct.csin);
		SOCKET clientSocket = accept(server->mystruct.sock,(SOCKADDR *)&server->mystruct.csin, &sinsize);

		std::thread clientThread(ClientThread, clientSocket);
		clientThread.detach();
	}
	
}


tcpstruct* server::getstruct()
{
	return &this->mystruct;
}

void server::createsocket()
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
		mystruct.sock = sock1;
		cout << "socket serveur valide" << endl;
	}
	
	
	
	
		
	
	
#endif
}

void server::connect()
{
	int resbindfct;


	
	mystruct.sin = { 0 };

	mystruct.sin.sin_addr.s_addr = htonl(INADDR_ANY);

	mystruct.sin.sin_family = AF_INET;

	mystruct.sin.sin_port = htons(2500);
																																																																																	
	resbindfct = bind(mystruct.sock, (SOCKADDR *)&mystruct.sin, sizeof(mystruct.sin));
	
	if (resbindfct != SOCKET_ERROR)
	{
		cout << "client connecte sur le port " <<port<<endl;
		listen(mystruct.sock, 5);
	}
	else
	{
		cout << "erreur de bind" << endl;
	}
	

	//mystruct.csin = { 0 };
	
	std::thread workerconnect(WorkerThreadConnect,this);
	workerconnect.detach();
}

void server::receiv()
{
	int recvLen = 0;
	int recvsock;
	bool findetrame = false;
	int i = 0;



	recvsock = recv(socketclient, buffer, taille - 1, 0);



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
	else if (strlen(buffer) == 4 && buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 's' && buffer[3] == 't')
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




void server::readbuffer()
{
	cout << buffer << endl;
}

void server::close()
{
	
	closesocket(mystruct.sock);
}
