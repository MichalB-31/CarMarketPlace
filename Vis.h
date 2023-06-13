#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;
class Vis
{
public:
	void welcome();
};

void Vis::welcome()
{
	cout << "Witaj!" << endl;
	Sleep(4000);
	system("cls");
}

