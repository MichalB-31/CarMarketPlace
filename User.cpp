#include "User.h"


User::User(Table &t)
{
	cout << "Podaj imie:";
	cin >> this->name;
	cout << "Podaj nazwisko: ";
	cin >> this->surname;
	cout << "Podaj pseudonim: ";
	cin >> this->login;
	cout << "Podaj email: ";
	cin >> this->email;
	cout << "Podaj haslo: ";
	cin >> this->password;
	t.add_row(1, this->name, this->surname, this->login, this->email);
}
