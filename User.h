#pragma once
#include "Table.h"
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;


class User //klasa ktora ma zapisac dane uzytkownika i je wrzucic do tabeli, mysle ze bedzie tu mocne polaczenie z klasa Table
{
private:
	int id;
	string name;
	string surname;
	string nickname;
	string email;
	string password;
public:
	friend class Table;
	void collect(Table &t);
};


