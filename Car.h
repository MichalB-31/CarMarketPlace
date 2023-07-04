#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "User.h"
using namespace std;

class Car //Klasa obslugujaca zapytania do SQL dla bazy danych samochodow
{
private:
	string tableName{};					
public:
	friend class User;
	Car(string& name); 


	int carCreateTable(); //stworzenie bazy danych z tabela
	int carReadFromTable(User& u, string type); //odczytanie danych z tabeli, typ to sposb w jaki sposb zostana wypisane 
	int carAddRow(string& ownerID, string& make, string& model, string& year, string& mileage, string& body, string& price, string& forSale); //dodanie samochodu do tabeli
	int carDeleteRow(int& id); //usuniecie pojazdu z tabeli
	int carSetSaleAndPrice(int& id, double& price); //ustawienie ceny i parametru sprzedazy na 1 w tabeli
	int carSwapOwner(User& u, int& id); //zmiana wlasciciela po zakupie
	int carShowCarsForSale(); //pokazanie pojazdo ktore sa wystawione na sprzedaz
	double carGetPriceOfCar(int& id); //funckja pobierajaca cene samochodu gdy chcemy go zakupic
	bool carCheckIfOwnedCar(User& u, int id); //sprawdzenie czy nie kupujemy wlasnego pojazdu
	int carGetIdOfOwnerCar(int& id);  //Funkcja potrzebny zeby uzytkownik sprzedajcy auto otrzymal za nie pieniadze
	int carDeleteForSale(int& id); //Usuniecie ogloszenia
	int carCheckIfCorrectToBuy(int& id);
};
