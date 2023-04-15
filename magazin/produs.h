#pragma once
#include <string>
#include <iostream> 
using  std ::string;
using  std ::string;
//aceasta clasa pastreaza informatiile unui produs
class Produs{
private:
	double pret;
	string nume;
	string producator;
	string tip;
public:

	Produs() = default;
	//constructor
	Produs(double pret, string nume, string producator, string tip);
	
	Produs(const Produs& ot) :nume{ ot.get_nume() }, producator{ ot.get_producator() }, tip{ ot.get_tip() }, pret{ ot.get_price() } {};
	//returneaza pretul unui produs
	double get_price()const;

	//returneaza numele unui produs 
	string get_nume()const;

	//returneaza producatorul produsului
	string get_producator()const;

	//returneaza tipul produsului
	string get_tip()const;

	//returneaza pretul unui produs
	void set_price(double new_price);

	//returneaza numele unui produs 
	void set_nume(string nume_nou);

	//returneaza producatorul produsului
	void set_producator(string new_producator);

	//returneaza tipul produsului
	void set_tip(string new_tip);



};
void test_produs();