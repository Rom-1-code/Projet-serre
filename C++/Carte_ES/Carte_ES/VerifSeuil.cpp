#include "VerifSeuil.h"
#include <iostream>

using namespace std;

bool VerifSeuil::Verif_Brumisation(float TempInt, int Hygro)
{
	if (Hygro <= 50 && TempInt >= 5)
	{
		cout << "Condition rempli Brumisation activ�e" << endl;
		return true;
	}
	else if (TempInt >= 25)
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

bool VerifSeuil::Verif_Chauffage(float TempInt)
{
	if (TempInt < 1)
	{
		cout << "Condition rempli Chauffage activ�e" << endl;
		return true;
	}

	cout << "Condition non rempli Chauffage d�sactiv�e" << endl;
	return false;
}

bool VerifSeuil::Verif_Vasistas(float TempInt, float TempExt, int Hygro)
{
	if (TempInt >= 25)
	{
		cout << "Condition rempli Vasistas activ�e" << endl;
		return true;
	}
	else if (TempExt >= TempInt && TempInt <= 10)
	{
		cout << "Condition rempli Vasistas activ�e" << endl;
		return true;
	}
	else if (Hygro >= 85 && TempInt >= 10)
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

