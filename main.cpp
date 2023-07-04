#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "Table.h"
#include "Car.h"
#include "User.h"
#include "Interface.h"
using namespace std;

int main()
{
	string nazwa1 = "Cars";
	string nazwa2 = "Users";
	Car c1(nazwa1);
	Table t1(nazwa2);

	t1.createTable();
	c1.carCreateTable();

	Interface i1;
	User u1;

	string login;
	string name;
	int getId = 0;
	double getBalance = 0;

	int d{};
	int m{};
	i1.welcome();
	while (true)
	{
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
			else if (d == 2)
			{
				i1.reg(t1, u1);
			}
			else
			{
				return 0;
			}
		}
		t1.getIDandBalanceFromLogin(u1.login, u1.id, u1.balance);
		m = i1.menu(t1, c1, u1);
		if (m == 0)
		{
			return 0;
		}
	}

	return 0;

}

//wylogowanie
