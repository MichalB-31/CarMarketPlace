#include "Interface.h"
#include <iomanip>

void Interface::welcome()
{

	cout << "             _________________________________ " << endl;
	cout<<	"             |                                \\ " <<endl;
	cout << "             |                                 \\ " << endl;
	cout << "             |                                  \\ " << endl;
	cout << "             |               WITAJ!              \\ " << endl;
	cout << "     ________|                                    \\_____________ "<<endl;
	cout << "    |                                                           | " << endl;
	cout << "    |      ________                                ________     | " << endl;
	cout << "    |     |        |                              |        |    | " << endl;
	cout << "    |_____|        |______________________________|        |____| " << endl;
	cout << "          |        |                              |        | " << endl;
	cout << "          |________|                              |________| " << endl;
			  
				  
				  
				  
				  
				  
	Sleep(3000);
	system("cls");
}

int Interface::log_reg()
{
	int decision{};
	system("cls");
	while (true)
	{
		cout << "     _____________       _____________        _____________     " << endl;
		cout << "    |  Logowanie  |     | Rejestracja |      |   Wyjscie   |    " << endl;
		cout << "    |  1 + ENTER  |     |  2 + ENTER  |      |  3 + ENTER  |    " << endl;
		cout << "    |_____________|     |_____________|      |_____________|    " << endl;
			
			//Jestem tu pierwszy raz(2 + ENTER)          Zamknij program(3 + ENTER)" << endl;
		cin >> decision;
		if (decision == 1 || decision == 2 || decision == 3)
		{
			system("cls");
			return decision;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << " >>> Nieprawidlowa decyzja <<< " << endl;
			Sleep(1000);
			system("cls");
		}
	}
}

int Interface::log(Table &t, User &u)
{
	string pass;
	string login;
	
	while (true)
	{
		cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
		cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
		cout << "[Wpisz login: ";
		cin >> login;
		if (login == "0")
		{
			return 0;
		}
		cout << "[Wpisz haslo: ";
		cin >> pass;
		if (t.loginCheck(login, pass) == true)
		{
			Sleep(1000);
			break;
		}
		system("cls");
	}
	u.login = login;
	return 4;

}

int Interface::reg(Table &t, User &u)
{
	string name,surname, log, email, password;
	string balance = "0";
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
	cout << "[Podaj imie: ";
	cin >> name;
	if (name == "0")
	{
		return 0;
	}
	cout << "[Podaj nazwisko: ";
	cin >> surname;
	cout << "[Podaj login: ";
	cin >> log;
	cout << "[Podaj email: ";
	cin >> email;
	cout << "[Podaj haslo: ";
	cin >> password;
	int a = t.addRow(name, surname, log, password, email, balance);
	system("cls");
	if (a == 1)
	{
		cout << ">>> Zarejestrowano w systemie! <<<" << endl;
		Sleep(2000);
		return 4;

	}
	if (a == 2)
	{
		while (true)
		{
			cout << "<> Podaj inny login: ";
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
	if (a == 3)
	{
		while (true)
		{
			cout << "<> Podaj inny adres email: ";
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
	cout << ">>> Zarejestrowano w systemie! <<<" << endl;
	Sleep(1000);
	return 4;
}

int Interface::addCar(Car& c, User& u)
{
	char decision{}, firstdecision{};
	string make{}, model{}, year{}, mileage{}, body{};
	system("cls");
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl;
	cout << "[Na koncu zostaniesz zapytany o potwierdzenie wprowadzonych danych]" << endl << endl;
	cout << "[Czy chcesz rozpoczac dodawanie pojazdu? [t/n] ";
	cin >> firstdecision;
	if (firstdecision == 'n' || firstdecision == 'N')
	{
		return 0;
	}
	cout << "[Podaj marke: ";
	cin >> make;
	cout << "[Podaj model: ";
	cin >> model;
	cout << "[Podaj rocznik: ";
	cin >> year;
	cout << "[Podaj przebieg: ";
	cin >> mileage;
	cout << "[Podaj rodzaj nadwozia: ";
	cin >> body;
	cout << "[Czy potwerdzasz wprowadzone dane? [t/n] ";
	cin >> decision;
	if (decision == 'n' || decision == 'N')
	{
		return 0;
	}
	string forSale = "0";
	string price = "0";
	string id = to_string(u.id);
	c.carAddRow(id, make, model, year, mileage, body, price, forSale);
	return 0;
}

int Interface::deleteCar( Car& c, User& u)
{
	int decision{};
	system("cls");
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Wybierz pojazd, ktory chcesz usunac wpisujac jego ID + ENTER" << endl << endl;
	cout << "[Twoje pojazdy:\n";
	c.carReadFromTable(u, "co");
	cin >> decision;
	if (decision == 0)
	{
		return 0;
	}
	else
	{
		bool check = c.carCheckIfOwnedCar(u, decision);
		if (!check)
		{
			c.carDeleteRow(decision);
		}
		else
		{
			cout << "!!! Nieprawidlowa wartosc !!!" << endl;
			Sleep(1000);
		}

		return 0;
	}

}

int Interface::addCarForSale(Car& c, User& u)
{
	int carID;
	double price;
	system("cls");
	cout << "[ Wyjscie wpisz 0 + ENTER]" << endl;
	cout << " [Wyberz ktory pojazd chcesz chcesz wystawic na sprzedaz wpisujac jego ID + ENTER]" << endl << endl;
	c.carReadFromTable(u, "co");
	cin >> carID;
	if (carID == 0)
	{
		return 0;
	}
	cout << "\n[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
	cout << "[Podaj cene samochodu: ";
	cin >> price;
	c.carSetSaleAndPrice(carID, price);
	cout << ">>> Pojazd wystawiony na sprzedaz <<<" << endl;
	Sleep(2000);
	system("cls");
	return 0;
}

int Interface::deleteCarForSale(Car& c, User& u)
{
	int decision{};
	system("cls");
	cout << "[ Wyjscie wpisz 0 + ENTER]" << endl;
	cout << "[Wybierz ogloszenie, ktore chcesz usunac wpisujac jego ID + ENTER]" << endl << endl;
	cout << "[Twoje pojazdy:\n";
	c.carReadFromTable(u, "cd");
	cin >> decision;
	if (decision == 0)
	{
		return 0;
	}
	else
	{
		bool check = c.carCheckIfOwnedCar(u, decision);
		if (!check)
		{
			c.carDeleteRow(decision);
		}
		else
		{
			cout << "!!! Nieprawidlowa wartosc !!!" << endl;
			Sleep(1000);
		}

		return 0;
	}
}

int Interface::showCars(Table& t, Car& c, User& u)
{
	int decision;
	int id = 0;
	char finalDecision;
	double price;
	bool check{};
	cout << "[ Wyjscie wpisz 0 + ENTER]" << endl;
	cout << "[Jezeli chcesz dokonac zakupu, wpisz numer ID + ENTER] "<< endl << endl;
	c.carReadFromTable(u, "cs");
	cout << endl;
	cin >> decision;

	if (!decision)
	{
		return 0;
	}
	else
	{
		check = c.carCheckIfCorrectToBuy(decision);
		if (!check)
		{
			cout << "!!! Niepoprawna wartosc !!!" << endl;
			cin.clear();
			cin.ignore();
			Sleep(1000);
			return 0;
		}
		price = c.carGetPriceOfCar(decision);
		if (u.balance >= price)
		{
			cout << "[Czy chcesz potwierdzic zakup? [t/n]";
			cin >> finalDecision;
			if (finalDecision == 'T' || finalDecision == 't')
			{
				bool check = c.carCheckIfOwnedCar(u, decision);
				if (check)
				{
					cout << ">>> Dokonano zakupu <<<";
					id = c.carGetIdOfOwnerCar(decision);
					cout << id;
					t.updateBalance(u, price, id, "sale");
					c.carSwapOwner(u, decision);
					u.balance = u.balance - price;
					t.updateBalance(u);
				}
				else
				{
					cout << "!!! To twoj pojazd, nie mozesz go kupic !!!" << endl;
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			cout << "!!! Za malo srodkow na koncie !!!" << endl;
		}
	}
	Sleep(1000);
	return 0;
}

int Interface::deposit(Table& t, User& u)
{
	double dep = 0.0;
	system("cls");
	cout << "[Wpisz zadana kwote do wplaty: ";
	cin >> dep;
	if (dep > 0)
	{
		u.balance = u.balance + dep;
		t.updateBalance(u);
		cout << ">>> Dokonano wplaty. Aktualny stan srodkow: " << fixed << setprecision(2) << u.balance <<"zl <<<"<< endl;
		Sleep(2000);
		
	}
	else
	{
		cout << "!!! Nieprawidlowa wartosc !!!" << endl;
		Sleep(2000);
	}
	return 0;
}

int Interface::withdraw(Table& t,User& u)
{
	double with;
	
	system("cls");
	cout << "[Wpisz kwote jaka chcesz wyplacic: ";
	cin >> with;
	if (u.balance >= with)
	{
		u.balance -= with;
		t.updateBalance(u);
		cout << ">>> Dokonano wyplaty. Aktualny stan srodkow: " << fixed << setprecision(2) << u.balance << "zl <<<" << endl;
		Sleep(2000);
	}
	else
	{
		cout << "!!! Nieprawidlowa wartosc !!!" << endl;
		Sleep(3000);
	}
	return 0;
}

int Interface::logout()
{
	system("cls");
	cout << ">>> Wylogowano <<<" << endl;
	Sleep(2000);
	return 0;
}

int Interface::goodbye()
{
	system("cls");
	cout << " -------------------------------- " << endl;
	cout << "| Do zobaczenia nastepnym razem! |" << endl;
	cout << " -------------------------------- " << endl;
	Sleep(2000);
	return 0;
}

int Interface::profile(Table &t, Car&c, User& u)
{
	int decision{};
	system("cls");
	t.readFromTable(u,"u");
	cout << "[Twoje pojazdy:\n";
	c.carReadFromTable(u, "cp");
	cout << endl;

	cout << "--------------------------" << endl;
	cout << "> 1 + ENTER: Dodaj pojazd " << endl;
	cout << "> 2 + ENTER: Usun pojazd\n " << endl;
	cout <<	"--------------------------" << endl;
	cout << "--------------------------" << endl;
	cout << "> 3 + ENTER Wplac srodki " << endl;
	cout << "> 4 + ENTER Wyplac srodki \n" << endl;
	cout << "--------------------------" << endl;
	cout << "--------------------------" << endl;
	cout << "> 5 + ENTER Wystaw pojazd na sprzedaz pojazd " << endl;
	cout << "> 6 + ENTER Usun ogloszenie sprzedazy\n " << endl;
	cout << "--------------------------" << endl;
	cout << "--------------------------" << endl;
	cout << "> 7 + ENTER Powrot do menu" << endl;
	cout << "--------------------------" << endl;
	

	cin >> decision;
	if (decision == 1)
	{
		addCar(c, u);
	}
	else if (decision == 2)
	{
		deleteCar(c, u);
	}
	else if (decision == 3)
	{
	 	deposit(t, u);
	}
	else if (decision == 4)
	{
		withdraw(t, u);
	}
	else if (decision == 5)
	{
		addCarForSale(c, u);
	}
	else if (decision == 6)
	{
		deleteCarForSale(c, u);
	}
	else if (decision == 7)
	{
		return 0;
	}
	else
	{
		cin.clear();
		cin.ignore();
		system("cls");
		cout << "!!! Nieprawidlowa decyzja !!! " << endl;
		Sleep(1000);
	}
	profile(t, c, u);
}

int Interface::menu(Table &t, Car&c, User& u)
{
	int decision{};
	while (true)
	{
		system("cls");
		cout << " ----------------------------------  " << endl;
		cout << "|               MENU               | " << endl;
		cout << "|                                  | " << endl;
		cout << "|> 1 + ENTER: Twoj Profil          | " << endl;
		cout << "|> 2 + ENTER: Ogloszenia sprzedazy | " << endl;
		cout << "|> 3 + ENTER  Wylogowanie          | " << endl;
		cout << "|> 4 + ENTER  Zamknij aplikacje    | " << endl;
		cout << "|                                  | " << endl;
		cout << " ----------------------------------  " << endl;
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
			goodbye();
			logout();
			return 1;
		}
		else if (decision == 4)
		{
			goodbye();
			return 0;
		}
		else			
		{
			cin.clear();
			cin.ignore();
			system("cls");
			cout << "!!! Nieprawidlowa decyzja !!!" << endl;
			Sleep(1000);
		}
	}
	return 0;
}