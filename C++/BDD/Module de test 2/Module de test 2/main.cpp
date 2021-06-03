#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "bdd.h"
#include "ES.h"
#include <cstring>
#include <string>
#include <ctime>

//using namespace std;




int main() {
	//Déclaration de la structure de type MYSQL
	time_t actuel = time(0);
	tm *ltm = localtime(&actuel);
	
	int annee = 1900 + ltm->tm_year;
	int mois =  1 + ltm->tm_mon;
	int jour = ltm->tm_mday;
	int heures = ltm->tm_hour;
	int minutes = ltm->tm_min;
	int secondes = ltm->tm_sec;
	char DATE[11];
	snprintf(DATE, 11, "%d-0%d-%d\n", annee, mois, jour);
	string date = DATE;

	char HEURE[10];
	snprintf(HEURE, 10, "%d:%d:%d\n", heures, minutes, secondes);
	string heure = HEURE;

	ES* carte;
	carte = new ES();
	bdd BDD;
	float TempInt = carte->GetTempInt();
	std::string tempint;
	tempint = to_string(TempInt);
	float TempExt = carte->GetTempExt();
	std::string tempext;
	tempext = to_string(TempExt);
	float HygroAir = carte->GetHygroAir();
	std::string hygroair;
	hygroair = to_string(HygroAir);
	float HumiTerre = carte->GetHumiTerre();
	std::string humiterre;
	humiterre = to_string(HumiTerre);

	const char * host = "192.168.65.216";
	const char * login = "root";
	const char * password = "root";
	const char * bdd = "Projet_Serre";

	std::string request = "INSERT INTO `ValeurNum` ( `Temperature_int`, `Temperature_Ext`, `HumiditeAir`, `HumiditeTerre`, `Date`, `Heure`, `Etat`) VALUES ("+ tempint +", "+tempext+", " + hygroair + ", "+humiterre+", '"+DATE+"', '" + HEURE + "', '1');";
	
	bool resultStartBdd;
	bool resultConnexionBdd;
	bool resultQuery;

	resultStartBdd = BDD.StartBdd();

	if (resultStartBdd == true)
	{
		resultConnexionBdd = BDD.connexionBdd(host, login, password, bdd);

		if (resultConnexionBdd == true)
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