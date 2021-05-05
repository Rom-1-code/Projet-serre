
#include "VerifSeuil.h"
#include "Serveurcpp.h"
#include "ES.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int main(int argc, char *argv[])
{
	int* horairerecup;
	VerifSeuil* Verif;
	Verif = new VerifSeuil;
	Verif->SetHumiSol(40);
	Verif->SetHygro(60);
	Verif->SetPlage(15,31);
	Verif->SetTempExt(28);
	Verif->SetTempInt(26);
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
	Verif->GetMailAlert();
/*
	Serveurcpp* serveur;
	serveur = new Serveurcpp();
	serveur->createsocket();
	serveur->connect();
	serveur->receiv();
	//serveur->readbuffer();
*/
	
	system("PAUSE");
	return 0;
	
}

