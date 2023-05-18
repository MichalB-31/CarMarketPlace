#include "Table.h"

int Table::create_table()
{
	//funkcja tworzaca nowa tabele jesli jeszcze jej nie ma

	sqlite3* db; //wskaŸnik z biblioteki potrzebny do bazy danych
	char* err = nullptr; //wskaznik na blad gdyby cos bylo nie tak


	//Stworzenie lub otwarcie bazy danych:
	string file_name = (this->table_name + ".db");
	int result = sqlite3_open(file_name.c_str(), &db); //c_str() sie powtarza w kodzie bo funkcje z bibilioteki wymagaja uzycia typu char a nie string
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych:" << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Instrukcje SQL do stworzenia nowej tabeli
	string createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->table_name + "("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"Name TEXT NOT NULL,"
		"Surname TEXT NOT NULL,"
		"Nickname TEXT MOT NULL,"
		"Email TEXT NOT NULL)";

	//Wykonanie kodu SQL
	result = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK) {
		cout << "Blad podczas tworzenia tabeli: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);

	cout << "Tabela stworzona pomyslnie!" << endl;
}


int callback(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej 
	for (int i = 0; i < argc; i++)
	{
		std::cout << azColName[i] << ": " << argv[i] << endl;
	}
	cout << endl;
	return 0;
}


int Table::read_from_table()
{
	//Odczytywanie danych z tabeli
	sqlite3* db;
	char* err = nullptr;

	string file_name = (this->table_name + ".db");
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Kod SQL do wybrania wartosci z tabeli
	string selectSQL = "SELECT * FROM "+ table_name + "; ";

	//Wykonanie kodu SQL
	result = sqlite3_exec(db, selectSQL.c_str(), callback, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas wybierania wartosci " << err << endl;
		sqlite3_free(err);
		return result;
	}

	sqlite3_close(db);
}

int Table::add_row(string name, string surname, string nickname, string email)
{
	sqlite3* db;
	char* err = nullptr;

	//Otwarce bazy
	string file_name = (this->table_name + ".db");
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwerania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Kod SQL dodawania danych do wiersza
	string insertSQL = "INSERT INTO " + table_name + " (Name, Surname, Nickname, Email) VALUES('"+name+"', '"+surname+"', '"+nickname+"', '"+email+"'); ";

	//Wykonanie kodu SQL
	result = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas wstawania wiersza: " << err << endl;
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);

	cout << "Wiersz dodany pomyslnie!" << endl;
}


int Table::delete_row(string id)
{
	sqlite3* db;
	char* err = nullptr;

	//Otwarcie bazy danych
	string file_name = (this->table_name + ".db");
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Kod SQL do usuniecia wiersza
	string deleteSQL = "DELETE FROM " + this->table_name + " WHERE ID = "+ id +"; ";

	//Wykonanie kodu SQL
	result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas usuwania weirsza: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);

	cout << "Wiersz usunito pomyœnie!" << endl;
}