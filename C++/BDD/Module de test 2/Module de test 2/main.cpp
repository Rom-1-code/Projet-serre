#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "bdd.h"
#include "ES.h"
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

int main() {
	//Déclaration de la structure de type MYSQL
	time_t actuel = time(0);
	tm *ltm = localtime(&actuel);
	ES* carte;
	carte = new ES();
	bdd BDD;
	int annee = 1900 + ltm->tm_year;
	int mois = 1 + ltm->tm_mon;
	int jour = ltm->tm_mday;
	int heures = ltm->tm_hour;
	int minutes = ltm->tm_min;
	char DATE[10];
	char archiveDate[10];
	snprintf(DATE, 11, "%d-0%d-%d\n", annee, mois, jour);
	string date = DATE;

	string heure;
	heure = to_string(heures);

	float TempInt = carte->GetTempInt();
	string tempint;
	tempint = to_string(TempInt);
	float TempExt = carte->GetTempExt();
	string tempext;
	tempext = to_string(TempExt);
	float HygroAir = carte->GetHygroAir();
	string hygroair;
	hygroair = to_string(HygroAir);
	float HygroTerre = carte->GetHygroTerre();
	string hygroterre;
	hygroterre = to_string(HygroTerre);

	const char * host = "192.168.65.216";
	const char * login = "root";
	const char * password = "root";
	const char * bdd = "Projet_Serre";

	string request = "INSERT INTO `ValeurNum` ( `Temperature_int`, `Temperature_Ext`, `HumiditeAir`, `HumiditeTerre`, `Date`, `Heure`, `Etat`) VALUES ("+ tempint +", "+tempext+", " + hygroair + ", "+hygroterre+", '"+DATE+"', '"+heure+"', '1');";
	
	bool resultInitializeBdd;
	bool resultConnectBdd;
	bool resultQuery;

	resultInitializeBdd = BDD.initializeBdd();

	if (resultInitializeBdd == true)
	{
		resultConnectBdd = BDD.connectBdd(host, login, password, bdd);

		if (resultConnectBdd == true)
		{
			cout << "Connexion a la BDD OK !" << endl;
			resultQuery = BDD.query(request.c_str());

			if (resultQuery == true)
			{
				cout << "Insertion en base OK" << endl;
			}
			else
			{
				cout << "Insertion en base PAS OK" << endl;
			}
		}
	}

	

	

	return 0;
}