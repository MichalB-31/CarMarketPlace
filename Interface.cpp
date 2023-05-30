#include "Interface.h"

void Interface::welcome()
{
	cout << "Witaj!" << endl;
	Sleep(1000);
	system("cls");
}

int Interface::log_reg()
{
	
	cout << "Chce sie zalogowac (nacisnij 1 + enter)                    Jestem tu pierwszy raz (nacisnij 2 + enter)" << endl;
	try { //kod zeby zlapac jezeli uzytkownik poda cos innego niz 1 lub 2
		int decision{};
		cin >> decision;
		if (decision == 1 || decision == 2)
		{
			system("cls");
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

void Interface::log(Table &t, User &u)
{
	string log, pass;
	
	while (true)
	{
		cout << "Wpisz login: ";
		cin >> log;
		cout << "Wpisz haslo: ";
		cin >> pass;
		if (t.login_check(log, pass) == true)
		{
			break;
		}
		Sleep(3000);
		system("cls");
	}
	u.login = log;
	Sleep(3000);

}

void Interface::reg(Table &t, User &u)
{
	string name, surname, log, email, password;

	cout << "Podaj imie: ";
	cin >> name;
	cout << "Podaj nazwisko: ";
	cin >> surname;
	cout << "Podaj login: ";
	cin >> log;
	cout << "Podaj email: ";
	cin >> email;
	cout << "Podaj haslo: ";
	cin >> password;
	int a = t.add_row(name, surname, log, password, email);
	Sleep(2000);
	system("cls");
	if (a == 1)
	{
		cout << "Zarejestrowano w systemie!" << endl;
	}
	else if (a == 2)
	{
		while (true)
		{
			cout << "Podaj inny login: ";
			cin >> log;
			a = t.add_row(name, surname, log, password, email);
			if (a != 2)
			{
				break;
			}
			Sleep(2000);
			system("cls");
		}
	}
	else if (a == 3)
	{
		while (true)
		{
			cout << "Podaj inny adres email: ";
			cin >> email;
			a = t.add_row(name, surname, log, password, email);
			if (a != 3)
			{
				break;
			}
			Sleep(2000);
			system("cls");
		}
	}
	u.login = log;

	Sleep(3000);
}

void Interface::profile()
{
	system("cls");
	cout << "Imie: " << endl;
	cout << "Nazwisko: " << endl;
	cout << "Login: " << endl;
	cout << "Adres email: " << endl;
	cout << endl;
	cout << "====================" << endl;
	cout << endl;
	cout << "Dodaj pojazd: " << endl;
}
void Interface::menu()
{
	int decision{};
	system("cls");
	cout << "===MENU===" << endl << endl;
	cout << "---MOJ PROFIL---" << " (1 + ENTER) " << endl;
	cout << "---Przegladaj pojazdy---" << " (2 + ENTER) " << endl;
	cout << "---Zakoncz---" << " (3 + ENTER) " << endl;
	try { //kod zeby zlapac jezeli uzytkownik poda cos innego niz 1 lub 2 lub 3
		cin >> decision;
		if (decision == 1)
		{
			profile();
			system("cls");
		}
		else
		{
			throw (decision);
		}
	}
	catch (int dec)
	{
		system("cls");
		cout << "Nieprawidlowa decyzja" << endl;
		Sleep(1000);
		system("cls");
		menu();
	}
}