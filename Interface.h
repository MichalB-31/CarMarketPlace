#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Table.h"
#include "Car.h"
using namespace std;

//kalsa obslugujaca interfejs
class Interface
{
public:
	void welcome(); //strona powitania
	int log_reg(); //strona logowania oraz rejestracji, zwraca 1 lub 2 lub 3 i w zaleznosci od tego bedzie dalej logowanie lub rejestracja
	int log(Table &t, User& u); //strona obslugujaca logowanie i przekazujaca parametry do sprawdzenia
	int reg(Table &t, User& u); //strona do rejestracji i przekazujaca parametry do sprawdzenia, nastepenie wywolanie funkcji do logowania
	int menu(Table &t, Car& c, User& u); //strona po zalogowaniu
	int profile(Table& t, Car& c, User& u); //strona profilu
	int addCar(Car& c, User& u); //strona dodawania pojazdu
	int deleteCar(Car& c, User& u); //strona usuwania pojazdu
	int addCarForSale(Car& c, User& u); //strona wystawiania ogloszenia
	int showCars(Table& t, Car& c, User& u); //strona pokazuja samochody wystawione na sprzedaz i umozliwiajaca ich zakup
	int deleteCarForSale(Car& c, User& u);
	int deposit(Table& t, User& u); //wpalata pieniedzy
	int withdraw(Table& t, User& u); //wyplata pieniedzy
	int goodbye(); //Funckja zegnajaca uzytkowniika
	int logout(); //Funkcja wylogowywujaca uzytkownika
};

