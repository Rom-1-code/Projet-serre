#include "bdd.h"

bool bdd::StartBdd()
{
	MYSQL * resultMysql_init;

	resultMysql_init = mysql_init(&mysql);

	if (resultMysql_init != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool bdd::connexionBdd(const char *host, const char *login, const char *password, const char *bdd)
{
	MYSQL * resultConnexionBdd;

	resultConnexionBdd = mysql_real_connect(&mysql, host, login, password, bdd, 0, NULL, 0);

	if (resultConnexionBdd != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool bdd::query(const char *request)
{
	bool resultQuery;

	resultQuery = mysql_real_query(&mysql, request, strlen(request));

	if (resultQuery == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char bdd::queryaff()
{
	int resultat[20];

	mysql_query(&mysql, "SELECT `Heure_Debut`FROM `PlageHorraire` WHERE NumPlage = 1");
	
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	unsigned int i = 0;
	unsigned int num_champs = 0;

	//On met le jeu de résultat dans le pointeur result
	result = mysql_use_result(&mysql);

	//On récupère le nombre de champs
	num_champs = mysql_num_fields(result);

	//Tant qu'il y a encore un résultat ...
	while ((row = mysql_fetch_row(result)))
	{
		//On déclare un pointeur long non signé pour y stocker la taille des valeurs
		unsigned long *lengths;

		//On stocke ces tailles dans le pointeur
		lengths = mysql_fetch_lengths(result);

		//On fait une boucle pour avoir la valeur de chaque champs
		for (i = 0; i < num_champs; i++)
		{
			//On ecrit toutes les valeurs
			resultat[i] = printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	return 0;
}

void bdd::closeBdd()
{
	mysql_close(&mysql);
}