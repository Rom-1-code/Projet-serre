#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <mysql.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#include "VerifSeuil.h"
#include "TCPClient.h"
#include "../../BDD/Module de test 2/Module de test 2/bdd.h"

using namespace std;

int main()
{
	float TempInt = 20, TempExt = 22;		//Température en °C
	int Hygro = 45;							//Hygrometrie en %

	bool Brumi, Chauf, Vasis, Arros;

	VerifSeuil Verif;
	Client client ;
	bdd BDD;

	const char * host = "192.168.65.216";
	const char * login = "root";
	const char * password = "root";
	const char * bdd = "Projet_Serre";

	bool resultStartBdd;
	bool resultConnexionBdd;
	char resultQuery [20];

	resultStartBdd = BDD.StartBdd();

	if (resultStartBdd == true)
	{
		//connexion à la base de donnée
		resultConnexionBdd = BDD.connexionBdd(host, login, password, bdd);

		if (resultConnexionBdd == true)
		{
			cout << "Connexion a la BDD OK !" << endl << endl;
		}
		else
		{
			cout << "Connection a la BDD NOK !" << endl;
		}
	}
	else
	{
		cout << "erreur";
	}

	resultQuery[0] = BDD.queryaff();
	cout << resultQuery[0];

	//client.CreateSocket();
	//client.ConnectCarte();

	/*----------Appel des méthodes pour la vérification des seuils----------*/

	Brumi = Verif.Verif_Brumisation(TempInt, Hygro, 5, 25, 50);
	Chauf = Verif.Verif_Chauffage(TempInt, 1);
	Vasis = Verif.Verif_Vasistas(TempInt, TempExt, Hygro, 25, 10, 10, 85);
	Arros = Verif.Verif_Arrosage(5, 40, 7, 55);

	/*----------Écriture sur la carte E/S----------*/

	//while (1)
	//{
		//client->SendData(Brumi, Chauf, Vasis, false);

		//Sleep(5000);
		//client->SendData(false, false, false, false);
		//Sleep(500);

	//}
	_getch();
	client.Close();
	BDD.closeBdd();

	system("PAUSE");
}