#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "User.h"
using namespace std;

//klasa obslugujaca baze danych uzytkowniow
class Table
{
private:
	string tableName{};						
public:
	friend class User;
	Table(string &name);   

	int createTable();			 //stworzenie tabeli
	int readFromTable(User &u, string type); //odczytanie danych z tabeli na profilu
	int addRow(string &name, string &surname, string &login,string &password, string &email, string &balance); //dodanie uzytkownika
	int deleteRow(int &id);	//usuniecieuyztkownika
	bool loginCheck(string& username, const string& password); //sprawdzenie czy podane login i haslo do siebie pasuja 
	int getIDandBalanceFromLogin(string& login, int& id, double& balance); //dopisania ID oraz srodkow na koncie na podstawie loginu do atrybutow obiektu User tak zeby bylo latwo potem odczytywac

	int updateBalance(User& u, double sale = 0, int id = 0, string type = "deposit"); //funkcja zmieniajaca stan salda, domyslne parametry sa uzywane przy zwyklej wplacie, zostaja zmienione automatycznie
																					  //przy sprzedazy samochodu
};


