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
	//2 Funkcje ponizej pozwalaja na wyswietlenie danych pobranych z bazy danych w odpowiedni sposob: (w sumie to nie musza byc jako "friend")
	friend int carcallbackProfile(void* data, int argc, char** argv, char** azColName); //Wyswietlenie samochodow na profilu
	friend int carcallbackSale(void* data, int argc, char** argv, char** azColName); //Wyswietlenie pojazdow ktore sa na sprzedaz
	friend int carcallbackSetSale(void* data, int argc, char** argv, char** azColName); //Ustawienie parametru na 1 gdy pojazd jest wystawiony na sprzedaz oraz jego ceny
	friend int carcallbackPrice(void* data, int columnCount, char** columnValues, char** columnNames); //Funkcja pobierajaca cene samochodu podczas zakupu
	
	Car(string& name); 

	//Kazda funkcja ma car jako przedrostek bo musialem je kopiowac przy zmianie klasy i visual studio troche wariowalo, chyba mozna to juz zmienic
	int carcreateTable(); //stworzenie bazy danych z tabela
	int carreadFromTable(User& u, string type); //odczytanie danych z tabeli, typ to sposb w jaki sposb zostana wypisane 
	int carcarAddRow(string& ownerID, string& make, string& model, string& year, string& mileage, string& body, string& price, string& forSale); //dodanie samochodu do tabeli
	int cardeleteRow(int& id); //usuniecie pojazdu z tabeli
	int carsetSaleAndPrice(int& id, double& price); //ustawienie ceny i parametru sprzedazy na 1 w tabeli
	int carswapOwner(User& u, int& id); //zmiana wlasciciela po zakupie
	int carshowCarsForSale(); //pokazanie pojazdo ktore sa wystawione na sprzedaz
	double cargetPriceOfCar(int& id); //funckja pobierajaca cene samochodu gdy chcemy go zakupic
	bool carcheckIfOwnedCar(User& u, int id); //sprawdzenie czy nie kupujemy wlasnego pojazdu
};
