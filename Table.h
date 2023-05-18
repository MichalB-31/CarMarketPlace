#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
using namespace std;

class Table
{
private:
	string name = "users"; //to trzeba zamienic na typ char prawdopodbnie bo ma problem potem odczytac, nie wiem czy spacji nie wstawia 
public:
	int create_table(); //Funkcja tworzaca nowa tabele w bazie danych, argument to nazwa tabeli 
	int read_from_table(); //Odczytanie danych z tabeli - tylko trzeba tutaj podzielic bo raczej nie chcemy wszystkich informacji na raz
											 //tylko np. same "Marka model"
	int add_row(); //dodanie rzedu czyli calej informacji np. o uzytkowniku, o samochodzie
	int delete_row(string id); //usuniecie calego wiersza

	friend int callback(void* data, int argc, char** argv, char** azColName); //Funkcja umozliwiajaca odczytywanie pobranych danych z tabeli
};

//18.05.2023 00:51 edit

