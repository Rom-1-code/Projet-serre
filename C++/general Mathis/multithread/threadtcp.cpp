#include <iostream>
#include <thread>
#include "client.h"
#include "server.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <mutex>
#include <conio.h>


void workerThreadsend()
{
	client* clienttcp;
	clienttcp = new client();
	clienttcp->createsocket();
	clienttcp->connectnode();
	
}

void workerThreadreceiv()
{
	server* servertcp;
	servertcp = new server();
	servertcp->createsocket();
	servertcp->connect();

}

int main(int argc, char ** argv)
{
    

	
	std::thread worker(workerThreadreceiv);
	worker.detach();
	std::thread worker2(workerThreadsend);
	worker2.detach();

	
	_getch();
		//system("pause");

	return 0;
}

