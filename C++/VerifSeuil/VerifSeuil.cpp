#include "VerifSeuil.h"
#include <iostream>

using namespace std;

bool VerifSeuil::Verif_Brumisation(float TempInt, int Hygro)
{
	if (Hygro <= 50 && TempInt >= 5)
	{
		cout << "Condition rempli Brumisation activée" << endl;
		return true;
	}
	else if (TempInt >= 25)
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
bool VerifSeuil::Verif_Chauffage(float TempInt)
{
	if (TempInt < 1)
	{
		cout << "Condition rempli Chauffage activée" << endl;
		return true;
	}

	cout << "Condition non rempli Chauffage désactivée" << endl;
	return false;
}

