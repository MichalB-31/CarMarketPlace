#include "Interface.h"

void Interface::welcome()
{
	cout << "Witaj!" << endl;
	Sleep(1000);
	system("cls");
}

int Interface::log_reg()
{
	
	cout << "Chce sie zalogowac (1 + ENTER)                Jestem tu pierwszy raz (2 + ENTER)          Zamknij program (3 + ENTER)"<< endl;
	try { //kod zeby zlapac jezeli uzytkownik poda cos innego niz 1 lub 2
		int decision{};
		cin >> decision;
		if (decision == 1 || decision == 2 || decision == 3)
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

int Interface::add_car(Table& t, Table& c, User& u)
{
	char decision;
	string make{}, model{}, year{}, mileage{}, body{};
	system("cls");
	cout << "Podaj marke: ";
	cin >> make;
	cout << "Podaj model: ";
	cin >> model;
	cout << "Podaj rocznik: ";
	cin >> year;
	cout << "Podaj przebieg: ";
	cin >> mileage;
	cout << "Podaj rodzaj nadwozia: ";
	cin >> body;
	cout << "Czy potwerdzasz wprowadzone dane? [t/n]";
	cin >> decision;
	if (decision == 'n' || decision == 'N')
	{
		return 0;
	}
	c.car_add_row(to_string(u.id), make, model, year, mileage, body, "0", "0");
	Sleep(3000);
	return 0;
}

int Interface::car_for_sale(Table& t, Table& c, User& u)
{
	int carID;
	double price;
	system("cls");
	cout << "Wyjscie [0 + ENTER]" << endl;
	cout << "Wyberz ktory pojazd chcesz chcesz wystawic na sprzedaz [NUMER + ENTER]" << endl;
	c.read_from_table(u, "co");
	cin >> carID;
	if (carID == 0)
	{
		return 0;
	}
	cout << "Podaj cene samochodu: ";
	cin >> price;
	c.modify_row(carID, price);
	cout << "Pojazd wystawiony na sprzedaz!" << endl;
	Sleep(3000);
	system("cls");
	return 0;
}

int Interface::show_cars(Table& t, Table& c, User& u)
{
	int decision;
	char finalDecision;
	double price;
	cout << "Jezeli chcesz dokonac zakupu, wpisz: NUMER ID + ENTER. Wyjscie: 0 + ENTER" << endl << endl;
	cout << "===========" << endl;
	c.read_from_table(u, "cs");
	cout << endl;
	cin >> decision;
	if (!decision)
	{
		return 0;
	}
	else
	{
		price = c.getPriceFromTableRow(decision);
		if (u.balance >= price)
		{
			cout << "Czy chcesz potwierdzic zakup? [t/n]";
			cin >> finalDecision;
			if (finalDecision == 'T' || finalDecision == 't')
			{
				cout << "Dokonano zakupu!";
				c.modify_owner(u, decision);
				u.balance = -price;
				Sleep(3000);
			}
		}
		else
		{
			cout << "Za malo srodkow na koncie!" << endl;
		}
	}
	Sleep(3000);
}

int Interface::deposit(User& u)
{
	double dep{};
	while (true)
	{
		system("cls");
		cout << "Wpisz zadana kwote do wplaty: ";
		cin >> dep;
		if (dep > 0)
		{
			u.balance += dep;
			cout << "Dokonano wplaty. Aktualny stan srodkow: " << u.balance <<"zl"<< endl;
			Sleep(3000);
			break;
		}
		else
		{
			cout << "Nieprawidlowa wartosc!" << endl;
			Sleep(3000);
		}
	}
	return 0;
}

int Interface::withdraw(User& u)
{
	double with;
	while (true)
	{
		system("cls");
		cout << "Wpisz kwote jaka chcesz wyplacic: ";
		cin >> with;
		if (u.balance > with)
		{
			u.balance -= with;
			cout << "Dokonano wyplaty. Aktualny stan srodkow: " << u.balance << "zl" << endl;
			Sleep(3000);
			break;
		}
		else
		{
			cout << "Nieprawidlowa wartosc!" << endl;
			Sleep(3000);
		}
	}
	return 0;
}

int Interface::profile(Table &t, Table &c, User& u)
{
	int decision{};
	system("cls");
	t.read_from_table(u,"u");
	cout << "\nTwoje pojazdy:\n";
	c.read_from_table(u, "cp");
	cout << endl;
	cout << "====================" << endl;
	cout << endl;
	cout << "Wplac srodki [1 + ENTER]" << endl;
	cout << "Wyplac srodki [2 + ENTER]\n" << endl;
	cout << "====================" << endl;
	cout << endl;
	cout << "Dodaj pojazd [3 + ENTER]\n " << endl;
	cout << "====================\n" << endl;
	cout << "Wystaw dodany pojazd na sprzedaz pojazd [4 + ENTER]\n " << endl;
	cout << "====================\n" << endl;
	cout << "Powrot do menu [5 + ENTER]" << endl;

	cin >> decision;
	if (decision == 1)
	{
		deposit(u);
	}
	else if (decision == 2)
	{
		withdraw(u);
	}
	else if (decision == 3)
	{
		add_car(t,c,u);
	}
	else if (decision == 4)
	{
		car_for_sale(t, c, u);
	}
	else if (decision == 5)
	{
		return 0;
	}
	profile(t, c, u);
}

int Interface::menu(Table &t,Table &c, User& u)
{
	int decision{};
	while (true)
	{
		system("cls");
		cout << "===MENU===" << endl << endl;
		cout << "---MOJ PROFIL---" << " (1 + ENTER) " << endl;
		cout << "---Przegladaj pojazdy---" << " (2 + ENTER) " << endl;
		cout << "---Zakoncz---" << " (3 + ENTER) " << endl;
		try {
			cin >> decision;
			if (decision == 1)
			{
				profile(t, c, u);
				system("cls");
			}
			else if (decision == 2)
			{
				system("cls");
				show_cars(t, c, u);
			}
			else if (decision == 3)
			{
				break;
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
			menu(t, c, u);
		}
	}
}