#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "User.h"
using namespace std;

class Table
{
private:
	string tableName{};			
	string whichTable;							//ktora tabela, jak 'Users' to Users, jak 'Cars' to Cars
public:
	friend class User;
	Table(string &name, string &whichTab);   //parametry to Nazwa_Tabeli, Typ_Tabeli jak wy¿ej

	friend int callbackUser(void* data, int argc, char** argv, char** azColName); //Funkcje umozliwiajace odczytywanie pobranych danych z tabeli
	friend int callbackProfile(void* data, int argc, char** argv, char** azColName);
	friend int callbackSale(void* data, int argc, char** argv, char** azColName);

	int createTable();			 
	int readFromTable(User &u, string type); //type - ktora tabela       
	int addRow(string &name, string &surname, string &login,string &password, string &email, string &balance); 
	int carAddRow(string& ownerID, string& make, string& model, string& year, string& mileage, string& body, string& price, string& forSale);
	int deleteRow(string &id);	  //usuniecie calego wiersza
	int setSaleAndPrice(int& id, double& price);
	int swapOwner(User& u, int& id);
	int showCarsForSale();
	double getPriceOfCar(int& id);
	bool loginCheck(string& username, const string& password); 
	int getIDfromLogin(string& login, int& id, double& balance);
	bool checkIfOwnedCar(User& u, int id);

};


