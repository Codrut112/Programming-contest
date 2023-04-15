#pragma once
#include <vector>
#include "produs.h"
#include "vector.h"
using std::vector;
class Repo {
private:
	VectorDinamic<Produs> produse;
public:
	//constructor default
	Repo() = default;
	//impiedica crearea de copii
	Repo(const Repo& ot) = delete;
	//stocheaza un produs
	void store(const Produs& p);
	//sterge produsul cu numele nume
	void sterge(string nume);
	//modifica un produs dupa nume
	void modifica(string nume,const Produs& new_p);
	//returneaza numarul de produse
	size_t size()const;
	//returneaza un vector cu produsele
	const vector<Produs> get_all();
	//cauta produsul in lista
	int cauta(string nume);

	

};

class RepoException {
private:
	string msg;
public:
	RepoException(string m);
	//returneaza eroarea
	string get_message();
	
	
};


void test_repo();