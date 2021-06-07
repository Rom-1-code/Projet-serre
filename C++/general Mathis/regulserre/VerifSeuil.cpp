#include "VerifSeuil.h"
#include <ctime>
#include "SMTPMail.h"
#include <iostream>
#include "smtp.h"
#include <stdlib.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

float VerifSeuil::Get_TempInt()
{
	return this->SeuilTempInt;
}

float VerifSeuil::Get_TempExt()
{
	return this->SeuilTempExt;
}

int VerifSeuil::Get_Hygro()
{
	return this->SeuilHygro;
}

int VerifSeuil::Get_HumiSol()
{
	return this->SeuilHumiSol;
}

int* VerifSeuil::Get_PlageHoraire()
{

	horaire[0] = this->Plageheure; //indice 0 pour heure
	horaire[1] = this->Plageminute; //indice 1 pour minute
	
	

	return horaire; //probleme de valeur

}

bool VerifSeuil::AllumeVasistas()
{
	if (this->Hygro >= 85 && this->TempExt >= 10 || this->TempExt >= this->TempInt && this->TempInt <= 10 || this->TempInt >= 25)
	{
		cout << "ouverture du vasistas..." << endl;
		return true;
	}
		cout << "les conditions ne sont pas respectees pour ouvrir le vasistas..." << endl;
		return false;
}

bool VerifSeuil::AllumeBrumi()
{
	if (this->TempInt >= 25 || this->Hygro <= 50 && this->TempInt >= 5)
	{
		cout << "lancement de la brumisation..." << endl;
		return true;
	}
		cout << "les conditions ne sont pas respectees pour declencher la brumisation..." << endl;
		return false;
}

bool VerifSeuil::AllumeChauffage()
{
	if (this->TempInt <= 1)
	{
		cout << "lancement du chauffage..." << endl;
		return true;
	}
		cout << "les conditions ne sont pas respectees pour declencher le chauffage..." << endl;
		return false;
}

bool VerifSeuil::AllumeArrosage()
{
	
	struct tm newtime;
	time_t dateheureactuelle = time(NULL);
	localtime_s(&newtime, &dateheureactuelle); //on recupere l'heure et la date actuelle
	int heure = newtime.tm_hour;
	int minute = newtime.tm_min;

	cout << "il est actuellement " << heure << " h " << minute << endl;

	if (this->HumiSol < this->SeuilHumiSol && heure >= this->Plageheure  || heure <= this->Plageheure)
	{
		if (heure == this->Plageheure && minute < this->Plageminute)
		{
			cout << "les conditions ne sont pas respectees pour declencher l'arrosage..." << endl;
			return false;
		}

		if (heure == this->Plageheure && minute > this->Plageminute)
		{
			cout << "les conditions ne sont pas respectees pour declencher l'arrosage..." << endl;
			return false;
		}
		cout << "lancement de l'arrosage..." << endl;
		return true;
	}
		cout << "les conditions ne sont pas respectees pour declencher l'arrosage..." << endl;
		return false;
}

void VerifSeuil::SetHumiSol(int SeuilHumiSol)
{
	this->SeuilHumiSol = SeuilHumiSol;
}

void VerifSeuil::SetHygro(int SeuilHygro)
{
	this->SeuilHygro = SeuilHygro;
}

void VerifSeuil::SetPlage(int heure, int minute)
{
	this->Plageheure = heure;
	this->Plageminute = minute;
	
}

void VerifSeuil::SetTempExt(float SeuilTempExt)
{
	this->SeuilTempExt = SeuilTempExt;
}

void VerifSeuil::SetTempInt(float SeuilTempInt)
{
	this->SeuilTempInt = SeuilTempInt;
}

bool VerifSeuil::GetMailAlert(int TempInttest, int Hygrotest, int HumiSoltest)
{/*
	if (TempInttest >= 30 || Hygrotest >= 90 || TempInttest <= -5 || Hygrotest <= 36 || HumiSoltest <= 40 || HumiSoltest >= 67) //on envoie une alerte au serveur node car les valeurs mettent en péril la serre
	{
	*/
		struct smtp *smtp;
		int rc;
		rc = smtp_open("mail.la-providence.net",
			"25",
			SMTP_SECURITY_NONE,
			SMTP_NO_CERT_VERIFY,
			NULL,
			&smtp);
		rc = smtp_auth(smtp,
			SMTP_AUTH_NONE,
			NULL,
			NULL);
		rc = smtp_address_add(smtp,
			SMTP_ADDRESS_FROM,
			"BTSSN2-Projetserre",
			"Serre");
		rc = smtp_address_add(smtp,
			SMTP_ADDRESS_TO,
			"mclermont@la-providence.net",
			"Administration de la serre");
		rc = smtp_header_add(smtp,
			"Subject",
			"Alerte");

		/* rc = smtp_attachment_add_mem(smtp,
			"test.txt",
			"Test email attachment.",
			-1); */

		rc = smtp_mail(smtp,
			"probleme de seuil dans la serre,veuillez intervenir");
		rc = smtp_close(smtp);
		if (rc != SMTP_STATUS_OK) {
			printf("probleme %s\n", smtp_status_code_errstr((smtp_status_code)rc));
			return 1;
		}
/*
	}
	else
	{
		cout << "conditions non remplies pour alerter l'utilisateur" << endl;
	}
*/
	

	

	return true;
}