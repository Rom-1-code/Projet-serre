#define _CRT_SECURE_NO_WARNINGS

#include "VerifSeuil.h"
#include <iostream>
#include <string.h>
#include <ctime>
#include <time.h>

using namespace std;

/*----------Vérification des seuils pour la brumisation----------*/
bool VerifSeuil::Verif_Brumisation(float TempInt, int Hygro, float SeuilTempIntB1, float SeuilTempIntB2, int SeuilHygro)
{
	if (Hygro <= SeuilHygro && TempInt >= SeuilTempIntB1)
	{
		cout << "Condition rempli Brumisation activée" << endl;
		return true;
	}
	else if (TempInt >= SeuilTempIntB2)
	{
		cout << "Condition rempli Brumisation activée" << endl;
		return true;
	}
	else
	{
		cout << "Condition non rempli Brumisation désactivée" << endl;
		return false;
	}

}

/*----------Vérification des seuils pour le chauffage----------*/
bool VerifSeuil::Verif_Chauffage(float TempInt, float SeuilTempIntC)
{
	if (TempInt < SeuilTempIntC)
	{
		cout << "Condition rempli Chauffage activée" << endl;
		return true;
	}

	cout << "Condition non rempli Chauffage désactivée" << endl;
	return false;
}

/*----------Vérification des seuils pour le vasistas----------*/
bool VerifSeuil::Verif_Vasistas(float TempInt, float TempExt, int Hygro, float SeuilTempIntV1, float SeuilTempIntV2, float SeuilTempIntV3, int SeuilHygro)
{
	if (TempInt >= SeuilTempIntV1)
	{
		cout << "Condition rempli Vasistas activée" << endl;
		return true;
	}
	else if (TempExt >= TempInt && TempInt <= SeuilTempIntV2)
	{
		cout << "Condition rempli Vasistas activée" << endl;
		return true;
	}
	else if (Hygro >= SeuilHygro && TempInt >= SeuilTempIntV3)
	{
		cout << "Condition rempli Vasistas activée" << endl;
		return true;
	}
	else
	{
		cout << "Condition non rempli Vasistas désactivée" << endl;
		return false;
	}

}

/*----------Vérification des seuils pour l'arrosage----------*/
bool VerifSeuil::Verif_Arrosage(int Heure, int Minute, int Heure1, int Minute1)
{
	
	// date / heure actuelle basée sur le système actuel
	time_t actuel = time(0);
	cout << "Nombre de sec depuis Janvier 1,1970:" << actuel << endl;
	tm *ltm = localtime(&actuel);

	// afficher divers member de la structure tm.
	cout << "Année" << 1900 + ltm->tm_year << endl;
	cout << "Mois: " << 1 + ltm->tm_mon << endl;
	cout << "Jour: " << ltm->tm_mday << endl;
	cout << "Heure: " << ltm->tm_hour << " Minute: " << ltm->tm_min;

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
