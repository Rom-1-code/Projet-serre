#include "VerifSeuil.h"
#include <iostream>

using namespace std;

bool VerifSeuil::Verif_Brumisation(float TempInt, int Hygro)
{
	if (Hygro <= 50 && TempInt >= 5)
	{
		return true;
	}
	else if (TempInt >= 25)
	{
		return true;
	}
	else
	{
		return false;
	}

}	
