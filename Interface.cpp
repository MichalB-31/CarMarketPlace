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

void Interface::log(Table &t)
{
	string login, password;
	cout << "Wpisz login: ";
	cin >> login;
	cout << "Wpisz haslo: ";
	cin >> password;
	t.login_check(login, password);
	Sleep(3000);

}

void Interface::reg()
{
	string name, surname, login, email, password;
	cout << "Podaj imie: ";
	cin >> name;
	cout << "Podaj nazwisko: ";
	cin >> surname;
	cout << "Podaj pseudonim: ";
	cin >> login;
	cout << "Podaj email: ";
	cin >> email;
	cout << "Podaj haslo: ";
	cin >> password;
	//t.add_row(1, this->name, this->surname, this->login, this->login, this->email); Wylaczone na czas testow
	Sleep(3000);
	cout << "Zarejestrowano w systemie!" << endl;
}

void Interface::menu()
{
	system("cls");
	cout << "===MENU===" << endl << endl;
	cout << "---MOJ PROFIL---" << endl;
	cout << "---Przegladaj pojazdy---" << endl;
	Sleep(3000);
}