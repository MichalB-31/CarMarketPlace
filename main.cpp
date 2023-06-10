#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "Table.h"
#include "User.h"
#include "Interface.h"
using namespace std;

//LOOK DOWN BELOW

int main()
{
	string userTableName = "Users";
	string carTableName = "Cars";
	Table t1(userTableName, userTableName);
	Table c1(carTableName, carTableName);
	t1.createTable();
	c1.createTable();
	Interface i1;
	User u1;

	string login;
	string name;
	int d{};
	int l{};
	int r{};
	i1.welcome();
	while (true)
	{
		d = i1.log_reg();
		if (d == 1)
		{
			l = i1.preLog(login);
			if (l == 1)
			{
				i1.log(t1, u1, login);
				break;
			}
			else
			{
				continue;
			}
		}
		else if (d == 2)
		{
			r = i1.preReg(name);
			if (r == 1)
			{
				i1.reg(t1, u1, name);
				break;
			}
		}
		else
		{
			return 0;
		}
	}
	t1.getIDfromLogin(u1.login, u1.id, u1.balance);
	i1.menu(t1,c1,u1);


	return 0;
}
//Przerobienie funkcji get_price
//Dopisanie srodkow na koncie do bazy danych 
//Usuniecie ogloszenia
//Usuniecie calkowite samochodu z serwisu
//Upiekszenie kodu


//Legenda jesli mozna to tak nazwac:

//Dane uzytkownika ktorego wpisalem do testow
//login: mb307, haslo: test
//login db79 haslo: test

//Table - klasa do obslugi zapytan SQL
//Interface - typowo wyglad, staram sie zeby te funkcjonalnego wykonywala klasa User - niesty troche w siebie wchodza. Chodzi o to ze klasa Interface mam miec tylko funkcje wygladu.
//User - przekazywanie wszystkiego co uzytkownikiem, pobieranie do bazy danych i przechowywanie atrybutow


