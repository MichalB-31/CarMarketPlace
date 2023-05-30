#pragma once
#include "Table.h"
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;


class User //klasa ktora ma zapisac dane uzytkownika i je wrzucic do tabeli, mysle ze bedzie tu mocne polaczenie z klasa Table
{
private:
	
public:
	int id;
	string name;
	string surname;
	string login;
	string email;

	friend class Table;
	User(Table& t);
	//void collect(Table &t);
};


