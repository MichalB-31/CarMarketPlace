#include "Interface.h"

void Interface::welcome()
{
	cout << "Witaj!" << endl;
	Sleep(1000);
	system("cls");
}

int Interface::log_reg()
{
	int decision{};
	cout << "Chce sie zalogowac (nacisnij 1 + enter)                    Jestem tu pierwszy raz (nacisnij 2 + enter)" << endl;
	try { //kod zeby zlapac jezeli uzytkownik poda cos innego niz 1 lub 2
		cin >> decision;
		if (decision == 1 || decision == 2)
		{
			return decision;
		}
		else
		{
			throw (decision);
		}
	}
	catch(int dec)
	{
		cout << "Nieprawidlowa decyzja" << endl;
		Sleep(1000);
		system("cls");
		log_reg();
	}
}

void Interface::log()
{
	cout << "Wpisz login: ";
}

void Interface::reg()
{
	;
}