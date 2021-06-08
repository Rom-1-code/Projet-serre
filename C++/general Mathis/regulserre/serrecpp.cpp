
#include "VerifSeuil.h"
#include "Serveurcpp.h"
#include "ES.h"
#include <iostream>
#include <stdio.h>
#include "smtp.h"
#include <stdlib.h>
#include <thread>
#pragma comment (lib,"ws2_32.lib")
#define CTR_SECURE_NO_WARNINGS
using namespace std;


int main(int argc, char *argv[])
{
	int* horairerecup;
	VerifSeuil* Verif;
	Verif = new VerifSeuil;
	Verif->SetHumiSol(20);
	Verif->SetHygro(10);
	Verif->SetPlage(20,10);
	Verif->SetTempExt(40);
	Verif->SetTempInt(1);
	horairerecup = Verif->Get_PlageHoraire();
	

	cout << "la plage horaire est de " <<horairerecup[0] << " heure et " <<horairerecup[1]<<" minutes"<<endl;
	ES* cartees;
	cartees = new ES;

	cartees->lireHumiSol();
	cartees->lirehygro();
	cartees->lireTempExt();
	cartees->lireTempInt();

	Verif->AllumeArrosage();
	Verif->AllumeBrumi();
	Verif->AllumeChauffage();
	Verif->AllumeVasistas();

	Verif->GetMailAlert(-5, 100, 30);
	
	
	


	
	system("PAUSE");
	return 0;
	
}

