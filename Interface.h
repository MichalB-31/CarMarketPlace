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
	void log(Table &t, User& u); //strona obslugujaca logowanie i przekazujaca parametry do sprawdzenia
	void reg(Table &t, User& u); //strona do rejestracji i przekazujaca parametry do sprawdzenia, nastepenie wywolanie funkcji do logowania
	int menu(Table &t, Table& c, User& u); //strona po zalogowaniu
	int profile(Table& t,Table &c, User& u);
	int add_car(Table& t,Table& c, User& u);
	int car_for_sale(Table& t, Table& c, User& u);
	int show_cars(Table& t, Table& c, User& u);

	int deposit(User& u);
	

	friend class User;
};

