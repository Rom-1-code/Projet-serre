#pragma once
class VerifSeuil
{
	private:
		
		
		float TempInt = 20;
		float TempExt = 18;
		int Hygro = 60; //60%
		int HumiSol = 49; //49%
		float SeuilTempInt = 25;
		float SeuilTempExt = 30;
		int SeuilHygro = 85;
		int SeuilHumiSol = 55;
		int Plageheure = 16;
		int Plageminute = 31;
		int horaire[2];
		

	public:
	
		float Get_TempInt();
		float Get_TempExt();
		int Get_Hygro();
		int Get_HumiSol();
		int* Get_PlageHoraire();
		void SetHygro(int SeuilHygro);
		void SetTempInt(float SeuilTempInt);
		void SetTempExt(float SeuilTempExt);
		void SetHumiSol(int SeuilHumiSol);
		void SetPlage(int heure,int minute);
		bool AllumeVasistas();
		bool AllumeBrumi();
		bool AllumeChauffage();
		bool AllumeArrosage();
		bool GetMailAlert(int TempInttest, int Hygrotest, int HumiSoltest);

};

