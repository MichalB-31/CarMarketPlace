#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class Interface
{
public:
	void welcome(); //strona powitania
	int log_reg(); //strona logowania oraz rejestracji, zwraca 1 lub 2 i w zaleznosci od tego bedzie dalej logowanie lub rejestracja
	void log();
	void reg();
};

