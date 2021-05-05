#include <iostream>
#include "mysql.h"
#include <cstring>

int main() {

		MYSQL *mysql;
		MYSQL_ROW row = NULL;
		MYSQL_RES *res = NULL;

		mysql = mysql_init(NULL);

		if (mysql) {
			std::cout << "mySql initialisee !" << std::endl;
		}
		else
		{
			std::cout << "Impossible d'initialisee !" << std::endl;
		}
	}
	/*//Déclaration de la structure de type MYSQL
	MYSQL mysql;
	char response;
	int result;
	const char * request = "INSERT INTO `ValeurNum` (`ID_Valeur`, `Température_int`, `Température_Ext`, `HumiditéAir`, `HumiditéTerre`, `Date`, `Heure`, `Etat`) VALUES ('2', '30', '40', '40', '30', '2021-02-01', '07:00:00', '1');";
	const char * host = "mysql-projetserre.alwaysdata.net";
	const char * login = "231031_admin";
	const char * password = "serre1234";
	const char * bdd = "projetserre_sql";


	mysql_init(&mysql);
	//Si la connexion réussie..
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
		cout << "Une erreur s'est produite lors de la connexion à la BDD!" << endl;
	}

	mysql_close(&mysql);

	return 0; */
	
}