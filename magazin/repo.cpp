#include "repo.h"
#include <assert.h>
#include <iostream>

void Repo::store(const Produs& p)
{
	

	for (const auto& produs:produse ) {

		if (p.get_nume() == produs.get_nume() and p.get_producator() == produs.get_producator() and p.get_tip() == produs.get_tip())
			throw RepoException("produs existent");
		
	}

	
	produse.push_back(p);

}

void Repo::sterge(string nume)
{
	produse.get(produse.size() - 1);
	int poz = cauta(nume);
	produse.set(produse.get(produse.size() - 1), poz);
	produse.pop_back();
}

void Repo::modifica(string nume, const Produs& new_p)
{
	int poz = cauta(nume);
	produse.set(new_p, poz);
}

size_t Repo::size()const
{
	return produse.size();

}

const vector<Produs> Repo::get_all()
{
	vector<Produs>lista_produse;
	for (auto& produs : produse) {
		lista_produse.push_back(produs);

	}
	return lista_produse;
}

int Repo::cauta(string nume ) 
{
	int i=0;
	for (auto & produs:produse) {
	
		if (nume ==produs.get_nume())
			return i;
		i++;
	}
	throw RepoException("produs inexistent");}


void test_repo()
{
	
	Repo lista;
	lista.store(Produs(1, "Apa", "dorna", "minerala"));
	lista.store(Produs(2.5, "Apa", "dorna", "plata"));
	try {
		lista.store(Produs(2.5, "Apa", "dorna", "plata"));
		assert(false);
	}
	catch (RepoException e) { assert(true); }
	
	
	assert(lista.size() == 2);
	assert(lista.cauta("Apa") == 0);
	lista.modifica("Apa", Produs(1, "bere", "cicucas", "rece"));
	vector<Produs> lista_noua = lista.get_all();
	assert(lista_noua.front().get_nume() == "bere");
	assert(lista.cauta("bere") == 0);
	
	try {
		assert(lista.cauta("") == -1); 
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "produs inexistent");
		assert(true);
	}

	lista.sterge("Apa");
	assert(lista.size() == 1);
	

}

RepoException::RepoException(string m)
{
	msg = m;
}

string RepoException::get_message()
{
	return msg;
}
