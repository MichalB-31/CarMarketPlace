#include "Table.h"


Table::Table(string &name, string &whichTab)
{
	this->tableName = name;
	this->whichTable = whichTab;
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

int callbackSale(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej 
	cout << "ID Pojazdu: " << argv[0] << endl;
	cout << argv[2] << " " << argv[3] << " rok " << argv[4] << endl;
	cout << "Przebieg: " << argv[5] << "km , nadwozie " << argv[6] << endl;
	cout << "Cena: " << argv[7] << " zl" << endl;

	cout << "===========" << endl;
	return 0;
}

int callbackProfile(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej 
	cout << argv[2];
	cout << " ";
	cout << argv[3];
	cout << ", rok ";
	cout << argv[4];

	cout << endl;
	return 0;
}

int callbackPrice(void* data, int columnCount, char** columnValues, char** columnNames)
{
	double* pricePtr = static_cast<double*>(data);
	*pricePtr = std::stod(columnValues[7]);
	return 0;
}

int Table::createTable()
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

	string createTableSQL;
	//Instrukcje SQL do stworzenia nowej tabeli
	if (whichTable == "Users") 
	{
		createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Name TEXT NOT NULL,"
			"Surname TEXT NOT NULL,"
			"Login TEXT NOT NULL,"
			"Password TEXT NOT NULL,"
			"Email TEXT NOT NULL,"
			"Balance DOUBLE NOT NULL)";
	}
	else //Tabela dla pojazdow
	{
		createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"OwnerID INTEGER NOT NULL,"
			"Make TEXT NOT NULL,"
			"Model TEXT NOT NULL,"
			"Year TEXT NOT NULL,"
			"Mileage TEXT NOT NULL,"
			"Body TEXT NOT NULL,"
			"Price INTEGER NOT NULL,"
			"ForSale INTEGER NOT NULL)";
	}
	//Wykonanie kodu SQL
	result = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK) {
		cout << "Blad: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);
}

int Table::readFromTable(User& u, string type)// type u - uzytkownik, cp - carprofile, cs - carsale, co - cars owned
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

	string selectSQL;
	if (type == "u")
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE ID = " + to_string(u.id) + "; ";
		result = sqlite3_exec(db, selectSQL.c_str(), callbackUser, nullptr, &err);
	}
	else if (type == "cp")
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE OwnerID = " + to_string(u.id) + "; ";
		result = sqlite3_exec(db, selectSQL.c_str(), callbackProfile, nullptr, &err);
	}
	else if (type == "cs")
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE ForSale = 1;";
		result = sqlite3_exec(db, selectSQL.c_str(), callbackSale, nullptr, &err);
	}

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

	// Ustawienie parametrÛw z danymi
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

int Table::carAddRow(string &ownerID, string &make, string &model, string &year, string &mileage, string &body, string &price, string &forSale)
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
	string insertSQL = "INSERT INTO " + tableName + " (OwnerID, Make, Model, Year, Mileage, Body, Price, ForSale) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametrÛw z danymi
	result = sqlite3_bind_text(stmt, 1, ownerID.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, make.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, model.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, year.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, mileage.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 6, body.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 7, price.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 8, forSale.c_str(), -1, SQLITE_STATIC);


	// Wykonanie zapytania
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
	{
		cout << "Blad: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 1;
}

int Table::deleteRow(string &id)
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

	string deleteSQL = "DELETE FROM " + this->tableName + " WHERE ID = "+ id +"; ";

	result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	//Zamkniecie bazy danych
	sqlite3_close(db);

	cout << "Pojazd usunito pomyúnie!" << endl;
}

int Table::setSaleAndPrice(int& id, double& price)
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

	string selectSQL = "UPDATE " + tableName + " SET Price = " + to_string(price) + ", ForSale = 1 " + " WHERE ID = " + to_string(id) + "; ";
	result = sqlite3_exec(db, selectSQL.c_str(), nullptr, nullptr, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad:" << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
}

int Table::swapOwner(User& u, int& id)
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

	string selectSQL = "UPDATE " + tableName + " SET OwnerID = " + to_string(u.id) + " WHERE ID = " + to_string(id) + "; ";
	result = sqlite3_exec(db, selectSQL.c_str(), nullptr, nullptr, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad:" << err << endl;
		sqlite3_free(err);
		return result;
	}
}

int Table::showCarsForSale()
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

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ForSale = 1;";
	result = sqlite3_exec(db, selectSQL.c_str(), callbackSale, nullptr, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	sqlite3_close(db);
}

double Table::getPriceOfCar(int& id) //do zmodyfikowania
{
	double price = 0.0;

	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ID = " + to_string(id) + ";";


	result = sqlite3_exec(db, selectSQL.c_str(), callbackPrice, nullptr, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad: " << sqlite3_errmsg(db) << endl;
	}
	return price;
}

bool Table::checkIfOwnedCar(User& u, int id)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarket.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ID = ? AND OwnerID = ?;";
	sqlite3_stmt* stmt;
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas przygotowywania zapytania: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return false;
	}

	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_int(stmt, 2, u.id);

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		cout << "To Twoj pojazd! Nie mozesz go zakupic." << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}
	else
	{
		cout << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return false;
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




