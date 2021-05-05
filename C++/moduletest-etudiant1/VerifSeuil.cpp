#include "VerifSeuil.h"
#include <ctime>
#include "SMTPMail.h"
#include <iostream>
//#include <err.h>
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
	
	int* ptr_horaire = this->horaire;

	return ptr_horaire; //retour bateau car probleme avec les pointeurs

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

bool VerifSeuil::GetMailAlert()
{
	/*if (TempInttest >= 30 || Hygrotest >= 90 || TempInttest <= -5 || Hygrotest <= 36 || HumiSoltest <= 40 || HumiSoltest >= 67) //on envoie une alerte au serveur node car les valeurs mettent en péril la serre
	{
		

	}

	*/

	SMTPMail *mail;

	mail = new SMTPMail();

	try 
	{ 
		mail->open("smtp.gmail.com", "465", SMTP_SECURITY_NONE, SMTP_DEBUG, NULL);
		mail->auth(SMTP_AUTH_NONE, NULL, NULL);
		mail->address_add(SMTP_ADDRESS_FROM,"clermont.mailpro@gmail.com","From Address");
		mail->address_add(SMTP_ADDRESS_TO,"clermont.mailpro@gmail.com","To Address");
		//mail->header_add("Message test", "Test email (SMTPMail)"); //probleme here
		mail->mail("Email sent using CPP SMTPMail class"); //probleme here
		mail->close();

	}
	catch (SMTPMailException sme) 
	{
		//errx(1, "Failed to send email: %s\n", sme.what());//printf("erreur d'envoi \n");
		cout << sme.what() << endl;
	}

	delete mail;

	return true;
}