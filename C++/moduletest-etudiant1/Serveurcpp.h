#pragma once
#include <string>
class Serveurcpp
{
	private:

		int port = 2135;
		std::string ip = "127.0.0.1";
		int sock;
		int socketclient;
		char buffer[10];
		int taille=10;

	public:

		void createsocket();
		void connect();
		void receiv();
		void readbuffer();



			

};

