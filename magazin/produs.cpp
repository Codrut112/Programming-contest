#include "produs.h"
#include <assert.h>

Produs::Produs(double pret, string nume, string producator, string tip)
{
	this->pret = pret;
	this->nume = nume;
	this->producator = producator;
	this->tip = tip;
}

double Produs::get_price()const { return pret; }
string Produs::get_nume()const { return nume; }


string Produs::get_producator() const{ return producator; }


string Produs::get_tip()const { return tip; }

void Produs::set_price(double new_price)
{
	pret = new_price;
}

void Produs::set_nume(string nume_nou)
{
	this->nume = nume_nou;
}

void Produs::set_producator(string new_producator)
{
	this->producator = new_producator;
}

void Produs::set_tip(string new_tip)
{
	this->tip = new_tip;
}

void test_produs()
{
	
	Produs p = Produs{ 1,"apa","dorna","plata" };
	assert(p.get_nume() == "apa");
	assert(p.get_price() == 1);
	assert(p.get_tip() == "plata");
	assert(p.get_producator() == "dorna");
	p.set_nume("nume");
	p.set_price(3);
	p.set_producator("ei");
	p.set_tip("bun");
	assert(p.get_nume() == "nume");
	assert(p.get_price() == 3);
	assert(p.get_tip() == "bun");
	assert(p.get_producator() == "ei");

}
