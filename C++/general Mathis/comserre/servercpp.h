#pragma once
class servercpp
{

	private:

		int port = 502;
		const char ip[13] = "192.168.65.8";
		int sock;
		int socketclient;
		char buffer[11];
		char bufferreceivs1[13];
		char bufferreceivs2[13];
		int transac = 0;

	public:

		void createsocket();
		void connectsock();
		void sendtrameReadHoldingTempWire();
		void sendtrameReadHoldingHumiWire();
		void receivReadHoldingResgisterTempWire();
		void receivReadHoldingResgisterHumiWire();
		void readbufferTempWire();
		void readbufferHumiWire();






};

