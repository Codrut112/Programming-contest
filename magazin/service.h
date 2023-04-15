#pragma once
#include "repo.h"
#include "validare.h"

using std::string;
class Magazin {
	Repo& rep;
	Validator validator;
public:
	//constructor
	Magazin(Repo& rep, Validator validator) :rep{ rep }, validator{ validator } {}
	//impiedica copierea
	Magazin(const Magazin& ot) = delete;
	
	//adauga un produs 
	void adauga(double pret, string nume, string producator, string tip);
	//modifica un produs dupa nume
	void modifica(double pret_nou, string nume, string producator_nou, string tip_nou);
	//sterge un produs dupa nume
	void sterge(string nume);
	//returneaza un vector cu toate elementele
	const vector<Produs> get_all()const;
	//returneaza numarul de produse
	size_t size()const;
	//returneaza un vector cu toate produsele cu pretul mai mare
	const vector<Produs> filtrare_pret(double pret_minim)const;
	//returneaza un vector cu toate produsele cu numele "nume"
	const vector<Produs> filtrare_nume(string nume)const;
	//returneaza un vector cu toate produsele de la un anumit producator
	const vector<Produs> filtrare_producator(string producator)const;

	
	
	typedef bool(*compara)(Produs* x, Produs* y);
	vector<Produs> sortare(compara cmp);
	

};

void teste_service();
void test_filtrari();

bool comp_nume(Produs* x, Produs* y);
bool comp_pret(Produs* x, Produs* y);
bool comp_nume_tip(Produs* x, Produs* y);