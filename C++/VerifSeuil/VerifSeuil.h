#pragma once
class VerifSeuil
{

private:
	float TempInt, TempExt;
	int Hygro;

public:
	bool Verif_Brumisation(float TempInt , int Hygro);
	bool Verif_Chauffage(float TempInt);
	bool Verif_Vasistas(float TempInt, float TempExt, int Hygro);
};

