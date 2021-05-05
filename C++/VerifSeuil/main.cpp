
#include <iostream>
#include "VerifSeuil.h"

using namespace std;

int main()
{
	float TempInt = 20, TempExt = 22;		//Température en °C
	int Hygro = 45;							//Hygrometrie en %

	VerifSeuil *Verif = new VerifSeuil();

	Verif->Verif_Brumisation(TempInt, Hygro);
	Verif->Verif_Chauffage(TempInt);
	Verif->Verif_Vasistas(TempInt, TempExt, Hygro);

	system("PAUSE");

}

