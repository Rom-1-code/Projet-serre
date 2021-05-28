#include <iostream>
#include "VerifSeuil.h"
#include "TCPClient.h"

#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

int main()
{

	float TempInt = 20, TempExt = 22;		//Température en °C
	int Hygro = 45;							//Hygrometrie en %

	bool Brumi, Chauf, Vasis;

	VerifSeuil *Verif = new VerifSeuil();
	Client *client = new Client();

	client->CreateSocket();
	client->ConnectCarte();

	Brumi = Verif->Verif_Brumisation(TempInt, Hygro);
	Chauf = Verif->Verif_Chauffage(TempInt);
	Vasis = Verif->Verif_Vasistas(TempInt, TempExt, Hygro);

	//while (1)
	//{
		client->SendData(Brumi, Chauf, Vasis, false);

		Sleep(5000);
		client->SendData(false, false, false, false);
		Sleep(500);
	//}
	_getch();
	client->Close();

	system("PAUSE");
}