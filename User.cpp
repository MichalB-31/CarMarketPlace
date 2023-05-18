#include "User.h"


void User::collect(Table &t)
{
	cout << "Podaj imie:";
	cin >> this->name;
	cout << "Podaj nazwisko: ";
	cin >> this->surname;
	cout << "Podaj pseudonim: ";
	cin >> this->nickname;
	cout << "Podaj email: ";
	cin >> this->email;
	cout << "Podaj haslo: ";
	cin >> this->password;
	t.add_row(this->name, this->surname, this->nickname, this->email);
}
