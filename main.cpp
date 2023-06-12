#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
//#include "Table.h"
#include "Car.h"
#include "User.h"
#include "Interface.h"
using namespace std;

//LOOK DOWN BELOW

int main()
{
	string nazwa1 = "Cars";
	string nazwa2 = "Users";
	Car c1(nazwa1);
	Table t1(nazwa2);
	
	t1.createTable();
	c1.carcreateTable();
	
	Interface i1;
	User u1;

	string login;
	string name;
	int d{};
	i1.welcome();
	while (true)
	{
		d = i1.log_reg(); //ekran wyboru: 1 - logowanie, 2 - rejestracja, 3 - wyjscie
		if (d == 1)
		{
			d = i1.log(t1, u1); 
			if (d == 4) //jesli funckja zwroci 4 to znaczy ze jest okej, jak nie to znaczy ze login lub haslo sa nieprawidlowe
			{
				break;
			}
		}
		else if(d == 2)
		{
			i1.reg(t1, u1);
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
//Usuniecie ogloszenia
//Usuniecie calkowite samochodu z serwisu
//Upiekszenie kodu


//Dane jakich uzywalem wczesiej
//login: mb, haslo: test 



