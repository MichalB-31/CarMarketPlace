#include "Table.h"


Table::Table(string &name)
{
	this->tableName = name;
}

int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej 
	cout << "Twoje dane: " << endl;
	cout << "Imie: " << argv[1] << endl;
	cout << "Nazwsiko: " << argv[2] << endl;
	cout << "Nazwa uzytkownika: " << argv[3] << endl;
	cout << "Adres email: " << argv[5] << endl;

	cout << endl;
	return 0;
}

int Table::createTable()
{
	//funkcja tworzaca nowa tabele jesli jeszcze jej nie ma

	sqlite3* db; //wskaŸnik z biblioteki potrzebny do bazy danych
	char* err = nullptr; //wskaznik na blad gdyby cos bylo nie tak


	//Stworzenie lub otwarcie bazy danych:
	string file_name = "CarMarket.db";     //stworzenie odpowiedniego stringa ktora bedzie potrzebny do otwarcia bazy danych
	int result = sqlite3_open(file_name.c_str(), &db); //c_str() sie powtarza w kodzie bo funkcje z bibilioteki wymagaja uzycia typu char a nie string
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych:" << sqlite3_errmsg(db) << endl;
		return result;
	}

	string createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Name TEXT NOT NULL,"
			"Surname TEXT NOT NULL,"
			"Login TEXT NOT NULL,"
			"Password TEXT NOT NULL,"
			"Email TEXT NOT NULL,"
			"Balance DOUBLE NOT NULL)";

	result = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK) {
		cout << "Blad: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);
}

int Table::readFromTable(User& u, string type)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK) 
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ID = " + to_string(u.id) + "; ";
	result = sqlite3_exec(db, selectSQL.c_str(), callbackUser, nullptr, &err);
	
	if (result != SQLITE_OK)
	{
		cout << "Blad: " << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
}

int Table::addRow(string &name, string &surname, string &login, string &password, string &email, string &balance)
{
	sqlite3* db;
	sqlite3_stmt* stmt;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	// Sprawdzenie czy u¿ytkownik istnieje w bazie
	string selectSQL = "SELECT Login FROM " + tableName + " WHERE Login = ?";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas przygotowywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametru z loginem
	result = sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		cout << "Blad: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	// Wykonanie zapytania
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		cout << "Uzytkownik o podanym loginie juz istnieje." << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 2;  
	}
	else if (result != SQLITE_DONE)
	{
		cout << "Blad podczas wykonywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}


	selectSQL = "SELECT Email FROM " + tableName + " WHERE Email = ?";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas przygotowywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametru z emailem
	result = sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas ustawiania parametru email: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	// Wykonanie zapytania
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		cout << "Ten adres email jest juz uzywany w serwisie" << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 3;
	}
	else if (result != SQLITE_DONE)
	{
		cout << "Blad podczas wykonywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}


	sqlite3_finalize(stmt);

	// Dodanie wiersza jesli nie ma takiego uzytkownika
	string insertSQL = "INSERT INTO " + tableName + " (Name, Surname, Login, Password, Email, Balance) VALUES (?, ?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas przygotowywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametrów z danymi
	result = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, surname.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, login.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, password.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, email.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 6, balance.c_str(), -1, SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
	{
		cout << "Blad podczas wstawiania wiersza: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 1;
}

int Table::deleteRow(int &id)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string deleteSQL = "DELETE FROM " + this->tableName + " WHERE ID = "+ to_string(id) +"; ";

	result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);

}

bool Table::loginCheck(string& username, const string& password)
{
	sqlite3* db;
	sqlite3_stmt* stmt;


	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK) {
		cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	//Kod SQL do wybrania loginow i hasel z bazy danych
	string selectSQL = "SELECT Login, Password FROM " + this->tableName + " WHERE Login = ?;";
	//Przygotowanie kodu SQL
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cerr << "Blad: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		cerr << "Blad: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		// Jesli uzytkownik istnieje to dojdzie do sprawdzenia hasla
		string storedPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		if (password == storedPassword) {
			cout << "Zalogowano!" << endl;
			return true;
		}
		else {
			cout << "Niepoprawne haslo!" << endl;
			return false;
		}
	}
	else 
	{
		std::cout << "Niepoprawna nazwa uzytkownika!" << std::endl;
		return false;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return false;
}

int Table::getIDfromLogin(string& login, int& id, double& balance)
{
	sqlite3* db;
	sqlite3_stmt* stmt;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL = "SELECT ID, Balance FROM " + this->tableName + " WHERE Login = ?";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad : " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		cout << "Blad: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		id = sqlite3_column_int(stmt, 0);
		balance = sqlite3_column_double(stmt, 6);
	}
	else if (result == SQLITE_DONE)
	{
		cout << "Uzytkownik o podanym loginie nie istnieje." << endl;
	}
	else
	{
		cout << "Blad: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}




