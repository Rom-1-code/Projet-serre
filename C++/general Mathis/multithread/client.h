#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

#include <stdint.h>
#include <map>
#include <mutex>



struct clienttcpstruct
{
	SOCKET sock;
	SOCKET sockparameters;
	SOCKADDR_IN sin;
	SOCKADDR_IN sinparameters;
	
	char buffer[60];
};

struct modbusrequest
{
	uint16_t transactionId;
	int function;
	uint16_t startAddress;
	uint16_t nbData;
};

class client
{
private:
	uint16_t transactionId = 0;
	std::mutex synchro;
	std::map<uint16_t, modbusrequest> requests;
	clienttcpstruct mystruct;

	float hygrometrie;
	float temperature;
	bool hygroset=false;
	bool tempset=false;

		
public:

	void addModbusRequest(modbusrequest request) 
	{
		synchro.lock();
		requests[request.transactionId] = request;
		synchro.unlock();
	}

	modbusrequest getModbusRequest(uint16_t transactionId)
	{
		synchro.lock();
		if (requests.find(transactionId) != requests.end())
		{
			modbusrequest request = requests[transactionId];
			requests.erase(transactionId);
			synchro.unlock();
			return request;
		}
		synchro.unlock();
		modbusrequest error;
		error.function = -1;
		return error;
	}

	clienttcpstruct* getstruct();
	void createsocket();
	void connectcard();
	static void WorkerThreadSend(client* client);
	static void WorkThreadReceiv(client* client);
	static void sendReadRequest(client* client, int startAddress, int nbWord);
	
	
};