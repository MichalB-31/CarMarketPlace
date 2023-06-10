#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Table.h"
using namespace std;

class Interface
{
public:
	friend class Table;
	void welcome(); //strona powitania
	int log_reg(); //strona logowania oraz rejestracji, zwraca 1 lub 2 i w zaleznosci od tego bedzie dalej logowanie lub rejestracja
	int preLog(string& log);
	int log(Table &t, User& u, string &log); //strona obslugujaca logowanie i przekazujaca parametry do sprawdzenia
	int preReg(string& name);
	int reg(Table &t, User& u, string &name); //strona do rejestracji i przekazujaca parametry do sprawdzenia, nastepenie wywolanie funkcji do logowania
	int menu(Table &t, Table& c, User& u); //strona po zalogowaniu
	int profile(Table& t,Table &c, User& u);
	int addCar(Table& t,Table& c, User& u);
	int addCarForSale(Table& t, Table& c, User& u);
	int showCars(Table& t, Table& c, User& u);

	int deposit(User& u);
	int withdraw(User& u);

	friend class User;
};

