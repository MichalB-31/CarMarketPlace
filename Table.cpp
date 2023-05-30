#include "Table.h"


Table::Table(string name, string whichTab)
{
	this->tableName = name;
	this->whichTable = whichTab;
}

int Table::create_table()
{
	//funkcja tworzaca nowa tabele jesli jeszcze jej nie ma

	sqlite3* db; //wskaünik z biblioteki potrzebny do bazy danych
	char* err = nullptr; //wskaznik na blad gdyby cos bylo nie tak


	//Stworzenie lub otwarcie bazy danych:
	string file_name = "CarMarket.db";     //stworzenie odpowiedniego stringa ktora bedzie potrzebny do otwarcia bazy danych
	int result = sqlite3_open(file_name.c_str(), &db); //c_str() sie powtarza w kodzie bo funkcje z bibilioteki wymagaja uzycia typu char a nie string
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych:" << sqlite3_errmsg(db) << endl;
		return result;
	}

	string createTableSQL = {};
	//Instrukcje SQL do stworzenia nowej tabeli
	if (whichTable == "Users") //U poniewaz tabela dla uzytkownikow
	{
		createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Name TEXT NOT NULL,"
			"Surname TEXT NOT NULL,"
			"Login TEXT NOT NULL,"
			"Password TEXT NOT NULL,"
			"Email TEXT NOT NULL)";
	}
	else //Tabela dla pojazdow
	{
		createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Make TEXT NOT NULL,"
			"Model TEXT NOT NULL,"
			"Year TEXT NOT NULL,"
			"Mileage TEXT NOT NULL,"
			"Body TEXT NOT NULL)";
	}
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
		if (i == 1 || i == 2 || i == 3 || i == 5)
		{
			cout << azColName[i] << ": " << argv[i] << endl;
		}
	}
	cout << endl;
	return 0;
}



int Table::read_from_table(User& u)
{
	//Odczytywanie danych z tabeli
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Kod SQL do wybrania wartosci z tabeli
	string selectSQL = "SELECT * FROM " + tableName + " WHERE Login = "+ u.login +"; ";

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


int Table::read_from_table_TEST()
{
	//Odczytywanie danych z tabeli
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Kod SQL do wybrania wartosci z tabeli
	string selectSQL = "SELECT * FROM "+ tableName + "; ";

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

int Table::add_row(string name, string surname, string login, string password, string email)
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

	// Sprawdzenie czy uøytkownik istnieje w bazie
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
		cout << "Blad podczas ustawiania parametru loginu: " << sqlite3_errmsg(db) << endl;
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
		return 2;  // Return an error code to indicate duplicate login
	}
	else if (result != SQLITE_DONE)
	{
		cout << "Blad podczas wykonywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	//////
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
		return 3;  // Return an error code to indicate duplicate login
	}
	else if (result != SQLITE_DONE)
	{
		cout << "Blad podczas wykonywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}



	/////
	sqlite3_finalize(stmt);

	// Dodanie wiersza jesli nie ma takiego uzytkownika
	string insertSQL = "INSERT INTO " + tableName + " (Name, Surname, Login, Password, Email) VALUES (?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas przygotowywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametrÛw z danymi
	result = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, surname.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, login.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, password.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, email.c_str(), -1, SQLITE_STATIC);


	// Wykonanie zapytania
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

	//cout << "Wiersz dodany pomyslnie!" << endl;
	return 1;
}

int Table::car_add_row(string make, string model, string year, string mileage, string body)
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

	// Dodanie wiersza jesli nie ma takiego uzytkownika
	string insertSQL = "INSERT INTO " + tableName + " (Make, Model, Year, Mileage, Body) VALUES (?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas przygotowywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametrÛw z danymi
	result = sqlite3_bind_text(stmt, 1, make.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, model.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, year.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, mileage.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, body.c_str(), -1, SQLITE_STATIC);


	// Wykonanie zapytania
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

	cout << "Wiersz dodany pomyslnie!" << endl;
	return 1;
}

int Table::delete_row(string id)
{
	sqlite3* db;
	char* err = nullptr;

	//Otwarcie bazy danych
	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	//Kod SQL do usuniecia wiersza
	string deleteSQL = "DELETE FROM " + this->tableName + " WHERE ID = "+ id +"; ";

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

	cout << "Wiersz usunito pomyúnie!" << endl;
}

bool Table::login_check(const string& username, const string& password)
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
		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	//Ustawienie uzykownikow jako paramter
	result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		cerr << "Error binding username parameter: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	//Wykonanie
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		// Jesli uzytkownik istnieje to dojdzie do sprawdzenia hasla
		string storedPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		if (password == storedPassword) {
			//Haslo pasuje
			cout << "Zalogowano!" << endl;
			return true;
		}
		else {
			// Haslo nie pasuje
			cout << "Niepoprawne haslo!" << endl;
			return false;
		}
	}
	else {
		// Niepoprawny login
		std::cout << "Niepoprawna nazwa uzytkownika!" << std::endl;
		return false;
	}


	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return false;
}





