#pragma once
class Client
{
	private:

		int sock;
		char buffer[14];

	public:

		void CreateSocket();
		void ConnectCarte();
		void SendData(bool relay1, bool relay2, bool relay3, bool relay4);
		void Close();
};
