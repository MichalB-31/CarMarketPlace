#include "Car.h"

Car::Car(string& name)
{
	this->tableName = name;
}

int Car::carCreateTable()
{
	sqlite3* db; 
	char* err = nullptr; 


	//Stworzenie lub otwarcie bazy danych:
	string file_name = "CarMarketCars.db";    
	int result = sqlite3_open(file_name.c_str(), &db); 
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji:" << sqlite3_errmsg(db) << endl;
		return result;
	}

	string createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"OwnerID INTEGER NOT NULL,"
			"Make TEXT NOT NULL,"
			"Model TEXT NOT NULL,"
			"Year TEXT NOT NULL,"
			"Mileage TEXT NOT NULL,"
			"Body TEXT NOT NULL,"
			"Price DOUBLE NOT NULL,"
			"ForSale INTEGER NOT NULL)";

	result = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK) {
		cout << "Blad aplikacji: " << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
	return 0;
}

int carcallbackSale(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej
	cout << "  ___________" << endl;
	cout << " | ID Pojazdu: " << argv[0] << endl;
	cout << " | " << argv[2] << " " << argv[3] << " rok " << argv[4] << endl;
	cout << " | Przebieg: " << argv[5] << "km , nadwozie " << argv[6] << endl;
	cout << " | Cena: " << argv[7] << " zl" << endl;
	cout << " |___________" << endl;
	return 0;
}

int carcallbackSetSale(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej
	cout << "  ___________" << endl;
	cout << " |ID Pojazdu: " << argv[0] << endl;
	cout << " |" << argv[2] << " " << argv[3] << " rok " << argv[4] << endl;
	cout << " | Przebieg: " << argv[5] << "km , nadwozie " << argv[6] << endl;
	cout << " |___________" << endl;
	return 0;
}

int carcallbackPrice(void* data, int columnCount, char** argv, char** azColName)
{
	double* pricePtr = static_cast<double*>(data);
	*pricePtr = stod(argv[7]);
	return 0;
}

int carcallbackOwnerID(void* data, int columnCount, char** argv, char** azColName)
{
	int* ownerIdPtr = static_cast<int*>(data);
	*ownerIdPtr = stoi(argv[1]);
	return 0;
}

int carcallbackProfile(void* data, int argc, char** argv, char** azColName)
{
	//Funckja potrzebna do odczytywania danych pobranych z tabeli, uzyta w metodzie z funkcji ponizej
	cout << "  ______________________" << endl;
	cout << " | " << argv[2];
	cout << " ";
	cout << argv[3];
	cout << ", rok ";
	cout << argv[4];
	cout << endl;
	cout<<  " |______________________"<<endl;
	return 0;
}

int Car::carReadFromTable(User& u, string type)// cp - carprofile, cs - carsale, co - cars owned
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad podczas otwierania bazy danych: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL;
	if (type == "cp") //profil
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE OwnerID = " + to_string(u.id) + "; ";
		result = sqlite3_exec(db, selectSQL.c_str(), carcallbackProfile, nullptr, &err);
	}
	else if (type == "cs") //sprzedaz
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE ForSale = 1;";
		result = sqlite3_exec(db, selectSQL.c_str(), carcallbackSale, nullptr, &err);
	}
	else if (type == "co") //samochody do wystawienia na sprzedaz 
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE OwnerID = " + to_string(u.id) + "; ";
		result = sqlite3_exec(db, selectSQL.c_str(), carcallbackSetSale, nullptr, &err);
	}
	else if (type == "cd") //samochody co sa juz wystawione na sprzedaz
	{
		selectSQL = "SELECT * FROM " + tableName + " WHERE OwnerID = " + to_string(u.id) + " AND ForSale = 1; ";
		result = sqlite3_exec(db, selectSQL.c_str(), carcallbackSale, nullptr, &err);
	}

	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
	return 0;
}

int Car::carAddRow(string& ownerID, string& make, string& model, string& year, string& mileage, string& body, string& price, string& forSale)
{
	sqlite3* db;
	sqlite3_stmt* stmt;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string insertSQL = "INSERT INTO " + tableName + " (OwnerID, Make, Model, Year, Mileage, Body, Price, ForSale) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Ustawienie parametrów z danymi
	result = sqlite3_bind_text(stmt, 1, ownerID.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, make.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, model.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, year.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, mileage.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 6, body.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 7, price.c_str(), -1, SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 8, forSale.c_str(), -1, SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 1;
}

int Car::carDeleteRow(int& id)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string deleteSQL = "DELETE FROM " + this->tableName + " WHERE ID = " + to_string(id) + "; ";

	result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji : " << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
	return 0;
}

int Car::carSetSaleAndPrice(int& id, double& price)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL = "UPDATE " + tableName + " SET Price = " + to_string(price) + ", ForSale = 1 " + " WHERE ID = " + to_string(id) + "; ";
	result = sqlite3_exec(db, selectSQL.c_str(), nullptr, nullptr, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji:" << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
	return 0;
}

int Car::carSwapOwner(User& u, int& id)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string updateSQL = "UPDATE " + tableName + " SET OwnerID = " + to_string(u.id) + ", ForSale = 0 WHERE ID = " + to_string(id) + "; ";

	result = sqlite3_exec(db, updateSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << err << endl;
		sqlite3_free(err);
		sqlite3_close(db);
		return result;
	}

	sqlite3_close(db);
	return 0;
}

int Car::carShowCarsForSale()
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ForSale = 1;";
	result = sqlite3_exec(db, selectSQL.c_str(), carcallbackSale, nullptr, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << err << endl;
		sqlite3_free(err);
		return result;
	}

	sqlite3_close(db);
	return 0;
}

double Car::carGetPriceOfCar(int& id)
{
	double price = 0.0;

	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ID = " + to_string(id) + ";";

	result = sqlite3_exec(db, selectSQL.c_str(), carcallbackPrice, &price, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
	}

	sqlite3_close(db);

	return price;
}

bool Car::carCheckIfOwnedCar(User& u, int id)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji " << sqlite3_errmsg(db) << endl; 
		sqlite3_close(db);
		return false;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ID = " + to_string(id) + " AND OwnerID = "+ to_string(u.id) + "; ";
	sqlite3_stmt* stmt;
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return false;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return true;
}

int Car::carGetIdOfOwnerCar(int &id)
{
	int ownerId = 0;
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	string selectSQL = "SELECT * FROM " + tableName + " WHERE ID = " + to_string(id) + ";";

	result = sqlite3_exec(db, selectSQL.c_str(), carcallbackOwnerID, &ownerId, &err);

	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
	}

	sqlite3_close(db);

	return ownerId;
}

int Car::carDeleteForSale(int& id)
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		return result;
	}

	string deleteSQL = "UPDATE " + tableName + " SET ForSale = 0 WHERE ID = " + to_string(id) + "; ";

	result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji: " << err << endl;
		sqlite3_free(err);
		sqlite3_close(db);
		return result;
	}

	sqlite3_close(db);
	return 0;
}

int Car::carCheckIfCorrectToBuy(int& id)
{
	sqlite3* db;
	sqlite3_stmt* stmt;


	string file_name = "CarMarketCars.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK) {
		cerr << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return false;
	}

	string selectSQL = "SELECT * FROM " + this->tableName + " WHERE ID = " + to_string(id) + " ; ";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cerr << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return false;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) 
	{
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return true;
	}
	else
	{
		sqlite3_close(db);
		Sleep(1000);
		return false;
	}
}

