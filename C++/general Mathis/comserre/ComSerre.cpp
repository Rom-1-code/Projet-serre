// ComSerre.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "servercpp.h"
#include <stdlib.h>

using namespace std;

int main()
{
	servercpp* connexion;
	connexion = new servercpp();
	//recupération de la temperature sur l'input wire
	connexion->createsocket();
	connexion->connectsock();
	connexion->sendtrameReadHoldingTempWire();
	connexion->receivReadHoldingResgisterTempWire();
	connexion->readbufferTempWire();
	//recupération de l'hygrométrie sur l'input wire
	connexion->sendtrameReadHoldingHumiWire();
	connexion->receivReadHoldingResgisterHumiWire();
	connexion->readbufferHumiWire();

}

