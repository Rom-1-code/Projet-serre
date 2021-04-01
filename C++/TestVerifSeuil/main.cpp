
#include <iostream>
#include "VerifSeuil.h"

using namespace std;

int main()
{
	float TempInt = 25;		//Température en °C
	int Hygro = 35;			//Hygrometrie en %
	bool Condition;

	VerifSeuil *Verif = new VerifSeuil();

	Condition = Verif->Verif_Brumisation(TempInt, Hygro);
	if (Condition == true)
	{
		cout << "Condition rempli Brumisation activée" << endl;
	}
	else
	{
		cout << "Condition non rempli Brumisation désactivée" << endl;
	}

	system("PAUSE");
}
