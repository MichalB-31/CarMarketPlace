#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "Table.h"
#include "User.h"
#include "Interface.h"
using namespace std;

/*
int main()
{
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("myDB.db", &db);
	int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS cars(x1 INT, x2 INT, name varchar(100));", NULL, NULL, &err);
	
	if (rc != SQLITE_OK) {
			cout << "error: " << err;
	}

	for (int i = 0; i < 10; i++)
	{
		string query = "insert into cars VALUES ("+to_string(i)+", " +to_string(i + 5)+", 'xyz'); ";
		cout << query << '\n';
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
		if (rc != SQLITE_OK)
		{
			cout << "error: " << err;
		}
	}
}*/

int main()
{
	Table t1;
	Interface i1;
	i1.welcome();
	int d = i1.log_reg();
	if (d == 1)
	{
		t1.login_check("x", "y");
	}
	else
	{
		User u1(t1);
	}
	t1.read_from_table();
}

//Legenda jesli mozna to tak nazwac:

//Table - klasa do obslugi zapytan SQL
//Interface - typowo wyglad, staram sie zeby te funkcjonalnego wykonywala klasa User - niesty troche w siebie wchodza. Chodzi o to ze klasa Interface mam miec tylko funkcje wygladu.
//User - przekazywanie wszystkiego co uzytkownikiem, pobieranie do bazy danych i przechowywanie atrybutow


