#include <iostream>
#include "mysql.h"
#include <cstring>

using namespace std;

int main() {
	//D�claration de la structure de type MYSQL
	MYSQL mysql;
	char response;
	int result;
	const char * request = "INSERT INTO `ValeurNum` (`ID_Valeur`, `Temp�rature_int`, `Temp�rature_Ext`, `Humidit�Air`, `Humidit�Terre`, `Date`, `Heure`, `Etat`) VALUES ('2', '30', '40', '40', '30', '2021-02-01', '07:00:00', '1');";
	const char * host = "mysql-projetserre.alwaysdata.net";
	const char * login = "231031_admin";
	const char * password = "serre1234";
	const char * bdd = "projetserre_sql";

	
	mysql_init(&mysql);
	//Si la connexion r�ussie..
	if (mysql_real_connect(&mysql, host, login, password, bdd, 0, NULL, 0))
	{
		
		result = mysql_real_query(&mysql, request, strlen(request));

		if (result == 0)
		{
			cout << "Insertion en base OK !" << endl;
		}
		else
		{
			cout << "Insertion en base PAS OK ! " << endl;
		}
	}
	//Sinon ...
	else
	{
		cout << "Une erreur s'est produite lors de la connexion � la BDD!" << endl;
	}

	mysql_close(&mysql);

	return 0;
}

