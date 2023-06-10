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
	system("cls");
	cout << "Chce sie zalogowac (1 + ENTER)                Jestem tu pierwszy raz (2 + ENTER)          Zamknij program (3 + ENTER)"<< endl;
	try { //kod zeby zlapac jezeli uzytkownik poda cos innego niz 1 lub 2
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
	catch(int decision)
	{
		cout << "Nieprawidlowa decyzja" << endl;
		Sleep(1000);
		system("cls");
		log_reg();
		return 0;
	}
}

int Interface::preLog(string& log)
{
	cout << "Jezeli chcesz przerwac wpisz w pierwszym wierszu [0 + ENTER]" << endl;
	cout << "Wpisz login: ";
	cin >> log;
	if (log == "0")
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Interface::log(Table &t, User &u, string &login)
{
	string pass;
	
	while (true)
	{
		cout << "Wpisz haslo: ";
		cin >> pass;
		if (t.loginCheck(login, pass) == true)
		{
			break;
		}
		Sleep(3000);
		system("cls");
	}
	u.login = login;
	Sleep(3000);
	return 1;

}

int Interface::preReg(string& name)
{
	cout << "Jezeli chcesz przerwac wpisz w pierwszym wierszu [0 + ENTER]" << endl;
	cout << "Podaj imie: ";
	cin >> name;
	if (name == "0")
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Interface::reg(Table &t, User &u, string &name)
{
	string surname, log, email, password;
	string balance = "0";
	cout << "Podaj nazwisko: ";
	cin >> surname;
	cout << "Podaj login: ";
	cin >> log;
	cout << "Podaj email: ";
	cin >> email;
	cout << "Podaj haslo: ";
	cin >> password;
	int a = t.addRow(name, surname, log, password, email, balance);
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
			a = t.addRow(name, surname, log, password, email, balance);
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
			a = t.addRow(name, surname, log, password, email, balance);
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
	return 1;
}

int Interface::addCar(Table& t, Table& c, User& u)
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
	string forSale = "0";
	string price = "0";
	string id = to_string(u.id);
	c.carAddRow(id, make, model, year, mileage, body, price, forSale);
	Sleep(3000);
	return 0;
}

int Interface::addCarForSale(Table& t, Table& c, User& u)
{
	int carID;
	double price;
	system("cls");
	cout << "Wyjscie [0 + ENTER]" << endl;
	cout << "Wyberz ktory pojazd chcesz chcesz wystawic na sprzedaz [NUMER + ENTER]" << endl;
	c.readFromTable(u, "co");
	cin >> carID;
	if (carID == 0)
	{
		return 0;
	}
	cout << "Podaj cene samochodu: ";
	cin >> price;
	c.setSaleAndPrice(carID, price);
	cout << "Pojazd wystawiony na sprzedaz!" << endl;
	Sleep(3000);
	system("cls");
	return 0;
}

int Interface::showCars(Table& t, Table& c, User& u)
{
	int decision;
	char finalDecision;
	double price;
	cout << "Jezeli chcesz dokonac zakupu, wpisz: NUMER ID + ENTER. Wyjscie: 0 + ENTER" << endl << endl;
	cout << "===========" << endl;
	c.readFromTable(u, "cs");
	cout << endl;
	cin >> decision;
	if (!decision)
	{
		return 0;
	}
	else
	{
		price = c.getPriceOfCar(decision);
		if (u.balance >= price)
		{
			cout << "Czy chcesz potwierdzic zakup? [t/n]";
			cin >> finalDecision;
			if (finalDecision == 'T' || finalDecision == 't')
			{
				bool check = c.checkIfOwnedCar(u, decision);
				if (check)
				{
					cout << "Dokonano zakupu!";
					c.swapOwner(u, decision);
					u.balance = -price;
					Sleep(3000);
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			cout << "Za malo srodkow na koncie!" << endl;
		}
	}
	Sleep(3000);
	return 0;
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
	t.readFromTable(u,"u");
	cout << "Twoje pojazdy:\n";
	c.readFromTable(u, "cp");
	cout << endl;
	cout << "====================" << endl;
	cout << endl;
	cout << "Wplac srodki [1 + ENTER]" << endl;
	cout << "Wyplac srodki [2 + ENTER]\n" << endl;
	cout << "====================" << endl;
	cout << endl;
	cout << "Dodaj pojazd [3 + ENTER]" << endl;
	cout << "Usun pojazd [4 + ENTER]\n " << endl;
	cout << "====================\n" << endl;
	cout << "Wystaw pojazd na sprzedaz pojazd [5 + ENTER]" << endl;
	cout << "Usun ogloszenie sprzedazy [6 + ENTER]\n " << endl;
	cout << "====================\n" << endl;
	cout << "Powrot do menu [7 + ENTER]" << endl;

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
		addCar(t,c,u);
	}
	else if (decision == 4)
	{
		
	}
	else if (decision == 5)
	{
		addCarForSale(t, c, u);
	}
	else if (decision == 6)
	{

	}
	else if (decision == 7)
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
				showCars(t, c, u);
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
		catch(int decision)
		{
			system("cls");
			cout << "Nieprawidlowa decyzja" << endl;
			Sleep(1000);
			system("cls");
			menu(t, c, u);
		}
	}
	return 0;
}