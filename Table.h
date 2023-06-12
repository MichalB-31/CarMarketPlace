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

	//Funkcja do odczytania dancyh z tabeli:
	friend int callbackUser(void* data, int argc, char** argv, char** azColName); 

	int createTable();			 //stworzenie tabeli
	int readFromTable(User &u, string type); //odczytanie danych z tabeli na profilu
	int addRow(string &name, string &surname, string &login,string &password, string &email, string &balance); //dodanie uzytkownika
	int deleteRow(int &id);	  //usuniecie yztkownika
	bool loginCheck(string& username, const string& password); //sprawdzenie czy podane login i haslo do siebie pasuja 
	int getIDfromLogin(string& login, int& id, double& balance); //dopisania ID oraz srodkow na kocie na podstawie loginu do atrybutow obiektu User tak zeby bylo latwo potem odczytywac
};


