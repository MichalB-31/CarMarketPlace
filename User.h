#pragma once
#include "Table.h"
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;


class User //klasa ktora ma zapisac dane uzytkownika i je wrzucic do tabeli, mysle ze bedzie tu mocne polaczenie z klasa Table
{
private:
	int id = 1; //Myslalem zeby ogarniczyc atrybuty do id, login, password - reszta z bazy danych po prostu
	//string name;
	//string surname;
	string login;
	//string email;
	string password;
public:
	friend class Table;
	User(Table& t);
	//void collect(Table &t);
};


