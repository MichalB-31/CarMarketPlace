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
	Table t1("users", "Users");
	Table c1("cars02", "Cars");
	t1.create_table();
	c1.create_table();
	
	Interface i1;
	User u1;
	u1.login = "mb307";
	u1.id = 1;
	t1.get_id_from_login(u1.login, u1.id);
	i1.profile(t1,c1, u1);
	//c1.read_from_table_TEST();
	return 0;
	

	/*
	Table t1("users", "Users");
	Table c1("cars02", "Cars");
	t1.create_table();
	c1.create_table();
	Interface i1;
	i1.welcome();
	int d = i1.log_reg();
	User u1;
	if (d == 1)			//1 - logowanie, 2 - rejestracja, 3 - wyjscie
	{
		i1.log(t1, u1);
	}
	else if(d == 2)
	{
		i1.reg(t1,u1);
		i1.log(t1,u1);
	}
	else if(d == 3)
	{
		return 0;
	}
	t1.get_id_from_login(u1.login, u1.id);
	i1.menu(t1,c1,u1);


	//Table t2("cars", "Cars");
	//t2.create_table();
	//t1.car_add_row("Ford", "Focus", "2010", "178000", "Hatchback");
	

	*/

	

		
}

//Legenda jesli mozna to tak nazwac:

//Dane uzytkownika ktorego wpisalem do testow
//login: mb307, haslo: test

//Table - klasa do obslugi zapytan SQL
//Interface - typowo wyglad, staram sie zeby te funkcjonalnego wykonywala klasa User - niesty troche w siebie wchodza. Chodzi o to ze klasa Interface mam miec tylko funkcje wygladu.
//User - przekazywanie wszystkiego co uzytkownikiem, pobieranie do bazy danych i przechowywanie atrybutow


