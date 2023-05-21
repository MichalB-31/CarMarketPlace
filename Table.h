#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "User.h"
using namespace std;

class Table
{
private:
	string table_name = "usersv1"; //to trzeba zamienic na typ char prawdopodbnie bo ma problem potem odczytac, nie wiem czy spacji nie wstawia 
public:
	int create_table(); //Funkcja tworzaca nowa tabele w bazie danych, argument to nazwa tabeli 
	int read_from_table(); //Odczytanie danych z tabeli - tylko trzeba tutaj podzielic bo raczej nie chcemy wszystkich informacji na raz
											 //tylko np. same "Marka model"
	int add_row(int id, string name, string surname, string login, string email); //dodanie rzedu czyli calej informacji np. o uzytkowniku, o samochodzie
	int delete_row(string id); //usuniecie calego wiersza
	//int update_row - napewno sie przyda
	int login_check(string login, string password);
	friend int callback(void* data, int argc, char** argv, char** azColName); //Funkcja umozliwiajaca odczytywanie pobranych danych z tabeli
	friend class User;
};


