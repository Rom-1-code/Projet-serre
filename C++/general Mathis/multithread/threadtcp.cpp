#include <iostream>
#include <thread>
#include "client.h"
#include "server.h"
#include <stdlib.h>
#include <mutex>



void workerThreadsend()
{
	client* clienttcp;
	clienttcp = new client();
	clienttcp->createsocket();
	clienttcp->connectcard();
	
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

	
	
	system("pause");

	return 0;
}

