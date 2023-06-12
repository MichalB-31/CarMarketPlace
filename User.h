#pragma once
#include "Table.h"
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;


class User //klasa uzytkownika ktora posiada login, dzieki ktoremu mozliwe jest uzyskanie ID oraz balance i przypisanie ich do atrybutow tutaj
{
public:
	int id;
	string login;
	double balance = 0;
	friend class Table;
};


