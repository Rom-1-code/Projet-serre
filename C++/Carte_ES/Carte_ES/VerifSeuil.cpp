#define _CRT_SECURE_NO_WARNINGS

#include "VerifSeuil.h"
#include <iostream>
#include <string.h>
#include <ctime>
#include <time.h>

using namespace std;

/*----------V�rification des seuils pour la brumisation----------*/
bool VerifSeuil::Verif_Brumisation(float TempInt, int Hygro, float SeuilTempIntB1, float SeuilTempIntB2, int SeuilHygro)
{
	if (Hygro <= SeuilHygro && TempInt >= SeuilTempIntB1)
	{
		cout << "Condition rempli Brumisation activ�e" << endl;
		return true;
	}
	else if (TempInt >= SeuilTempIntB2)
	{
		cout << "Condition rempli Brumisation activ�e" << endl;
		return true;
	}
	else
	{
		cout << "Condition non rempli Brumisation d�sactiv�e" << endl;
		return false;
	}

}

/*----------V�rification des seuils pour le chauffage----------*/
bool VerifSeuil::Verif_Chauffage(float TempInt, float SeuilTempIntC)
{
	if (TempInt < SeuilTempIntC)
	{
		cout << "Condition rempli Chauffage activ�e" << endl;
		return true;
	}

	cout << "Condition non rempli Chauffage d�sactiv�e" << endl;
	return false;
}

/*----------V�rification des seuils pour le vasistas----------*/
bool VerifSeuil::Verif_Vasistas(float TempInt, float TempExt, int Hygro, float SeuilTempIntV1, float SeuilTempIntV2, float SeuilTempIntV3, int SeuilHygro)
{
	if (TempInt >= SeuilTempIntV1)
	{
		cout << "Condition rempli Vasistas activ�e" << endl;
		return true;
	}
	else if (TempExt >= TempInt && TempInt <= SeuilTempIntV2)
	{
		cout << "Condition rempli Vasistas activ�e" << endl;
		return true;
	}
	else if (Hygro >= SeuilHygro && TempInt >= SeuilTempIntV3)
	{
		cout << "Condition rempli Vasistas activ�e" << endl;
		return true;
	}
	else
	{
		cout << "Condition non rempli Vasistas d�sactiv�e" << endl;
		return false;
	}

}

/*----------V�rification des seuils pour l'arrosage----------*/
bool VerifSeuil::Verif_Arrosage(int Heure, int Minute, int Heure1, int Minute1)
{
	string test;

	// date / heure actuelle bas�e sur le syst�me actuel
	time_t actuel = time(0);
	tm *ltm = localtime(&actuel);

	// afficher divers member de la structure tm.
	int mois = 1 + ltm->tm_mon;
	int jour = ltm->tm_mday;
	int heure = ltm->tm_hour;
	int minute = ltm->tm_min;

	cout << "On est le " << jour << "/" << mois << " a " << heure << ":" << minute << endl;

	//std::string request = "SELECT `Date_Debut`FROM `PlageHorraire` WHERE NumPlage = 1";
	

	/*float HeureActuel;
	float MinuteActuel;

	if (HeureActuel >= Heure || HeureActuel <= Heure1)
	{
		if (HeureActuel == Heure && MinuteActuel < Minute)
		{
			return false;
		}
		if (HeureActuel == Heure1 && MinuteActuel < Minute1)
		{
			return false;
		}

		cout << "Vous pouvez arroser" << endl;

	}*/


	return true;
}
