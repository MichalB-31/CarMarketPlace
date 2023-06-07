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
	Table(string name, string whichTab);   //parametry to Nazwa_Tabeli, Typ_Tabeli jak wy¿ej
	friend class User;
	int create_table();			  //Funkcja tworzaca nowa tabele w bazie danych, argument to nazwa tabeli 
	int read_from_table(User &u, string type);        //Odczytanie danych z tabeli - tylko trzeba tutaj podzielic bo raczej nie chcemy wszystkich informacji na raz
											 //tylko np. same "Marka model"

	int read_from_table_TEST(); //odczytuje wszystkie dane do tesow
	int add_row(string name, string surname, string login,string password, string email); //dodanie rzedu czyli calej informacji np. o uzytkowniku, o samochodzie
	int delete_row(string id);	  //usuniecie calego wiersza
	//int update_row - napewno sie przyda
	friend int callbackUser(void* data, int argc, char** argv, char** azColName); //Funkcja umozliwiajaca odczytywanie pobranych danych z tabeli
	friend int callbackProfile(void* data, int argc, char** argv, char** azColName);
	friend int callbackSale(void* data, int argc, char** argv, char** azColName);
	bool login_check(const string& username, const string& password); //Funkcja sprawdzaja czy uzytkownik podal prawidlowe dane i moze sie zalogowac
	int get_id_from_login(const string& login, int& id);

	int car_add_row(string ownerID, string make, string model, string year, string mileage, string body, string price, string forSale);

	int modify_row(int id, double price);

	int show_cars_for_sale();

	int modify_owner(User& u,int id);

};


