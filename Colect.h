#pragma once
#include <iostream>
#include <string>
using namespace std;


class User_data
{
private:
	int id;
	string name;
	string surname;
	string nickname;
	string email;
	string password;
public:
	void insert();
};

void User_data::insert()
{
	cout << "Podaj swoje imie: ";
	cin >> this->name;
	cout << "Podaj swoje nazwisko: ";
	cin >> this->surname;
	cout << "Podaj swoja nazwe uzytkownika: ";
	cin >> this->nickname;
	cout << "Podaj swoj email: ";
	cin >> this->email;
	cout << "Podaj haslo: ";
	cin >> password;

}

