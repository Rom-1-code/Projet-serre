#pragma once
class VerifSeuil
{

private:
	float TempInt, TempExt;
	int Hygro;

	float SeuilTempIntB1, SeuilTempExt, SeuilTempIntC, SeuilTempIntV1, SeuilTempIntB2, SeuilTempIntV2, SeuilTempIntV3;
	int SeuilHygro;

public:
	bool Verif_Brumisation(float TempInt, int Hygro, float SeuilTempIntB1, float SeuilTempIntB2, int SeuilHygro);
	bool Verif_Chauffage(float TempInt, float SeuilTempIntC);
	bool Verif_Vasistas(float TempInt, float TempExt, int Hygro, float SeuilTempIntV1, float SeuilTempIntV2, float SeuilTempIntV3, int SeuilHygro);
	bool Verif_Arrosage(int Heure, int Minute, int Heure1, int Minute1);

};
