#pragma once
#include <iostream>
#include <mysql.h>
#include <cstring>

using namespace std;

class bdd
{
	private:
		MYSQL mysql;
	public:
		bool StartBdd();
		bool connexionBdd(const char *host, const char *login, const char *password, const char *bdd);
		bool query(const char *request);
		void closeBdd();
};