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

	bool Brumi, Chauf, Vasis, Arros;

	VerifSeuil *Verif = new VerifSeuil();
	Client *client = new Client();

	client->CreateSocket();
	client->ConnectCarte();

	/*----------Appel des méthodes pour la vérification des seuils----------*/

	Brumi = Verif->Verif_Brumisation(TempInt, Hygro, 5, 25, 50);
	Chauf = Verif->Verif_Chauffage(TempInt, 1);
	Vasis = Verif->Verif_Vasistas(TempInt, TempExt, Hygro, 25, 10, 10, 85);
	Arros = Verif->Verif_Arrosage(5, 40, 7, 55);

	/*----------Écriture sur la carte E/S----------*/

	//while (1)
	//{
		//client->SendData(Brumi, Chauf, Vasis, false);

		//Sleep(5000);
		//client->SendData(false, false, false, false);
		//Sleep(500);

	//}
	_getch();
	client->Close();

	system("PAUSE");
}