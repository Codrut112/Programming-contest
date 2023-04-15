#include "service.h"
#include "assert.h"
#include <iostream>
void Magazin::adauga(double pret, string nume, string producator, string tip)
{   
	Produs p{pret, nume, producator, tip };
	validator.valideaza(p);
	rep.store(p);
}

void Magazin::modifica(double pret_nou, string nume, string producator_nou, string tip_nou)
{
	Produs p = Produs(pret_nou, nume, producator_nou, tip_nou);
	validator.valideaza(p);
	rep.modifica(nume, p);
}

void Magazin::sterge(string nume)
{
	rep.sterge(nume);
	
}

const vector<Produs> Magazin::get_all() const
{
	return rep.get_all();
}

 size_t Magazin::size() const
{
	return rep.size();
}

 

 const vector<Produs> Magazin::filtrare_pret(double pret_minim) const
 {
	 vector<Produs> produse = rep.get_all();
	 vector<Produs> produse_filtrate;
	 for (auto& produs : produse) {
		
		 if (produs.get_price() > pret_minim)produse_filtrate.push_back(produs);
		 
	 }
	 return produse_filtrate;
 }

 const vector<Produs> Magazin::filtrare_nume(string nume) const
 {
	 vector<Produs> produse = rep.get_all();
	 vector<Produs> produse_filtrate;
	 for (auto& produs : produse) {

		 if (produs.get_nume()==nume)produse_filtrate.push_back(produs);

	 }
	 return produse_filtrate;
 }


 const vector<Produs> Magazin::filtrare_producator(string producator) const
 {
	 vector<Produs> produse = rep.get_all();
	 vector<Produs> produse_filtrate;
	 for (auto& produs : produse) {
		
		 if (produs.get_producator() == producator)produse_filtrate.push_back(produs);

	 }
	 return produse_filtrate;
 }

 

 vector<Produs> Magazin::sortare(compara cmp)
 {  

	 
	 vector<Produs> produse = rep.get_all();
	 for(int i=0;i<produse.size();i++)
		 for(int j=i+1;j<produse.size();j++)
			 if (cmp(&produse[i], &produse[j]))
			 
				 std::swap(produse[i], produse[j]);

	 return produse;
 }

 bool comp_nume(Produs* x, Produs* y)
 {
	 return x->get_nume() > y->get_nume();
 }

 bool comp_pret(Produs* x, Produs* y)
 {
	 return x->get_price() > y->get_price();
 }

 bool comp_nume_tip(Produs* x, Produs* y)
 {
	 if (x->get_nume() == y->get_nume())
		 return x->get_tip() > y->get_tip();
	 return comp_nume(x,y);
 }





void teste_service() {
	
	Repo rep;
	Validator valid;
	 Magazin mag{ rep , valid };

	mag.adauga(1.22, "banana", "africa", "bune");
	mag.adauga(2.22, "covrig", "petru", "sare");

	mag.adauga(51.22, "laptop", "lenovo", "gaming");
	

	mag.modifica(5, "banana", "india", "rele");
	vector<Produs> vect = mag.get_all();
	assert(vect[0].get_nume() == "banana");
	assert(vect[0].get_producator() == "india");
	assert(vect[0].get_tip() == "rele");
	mag.sterge("banana");
	assert(mag.size() == 2);

}
void test_filtrari() {

	Repo rep;
	Validator valid;
	Magazin mag{ rep , valid };
	mag.adauga(1.22, "macos", "apple", "linux");
	mag.adauga(2.22, "macos", "apple", "ubuntu");

	mag.adauga(51.22, "laptop", "lenovo", "gaming");

	assert(mag.filtrare_nume("macos").size() == 2);
	assert(mag.filtrare_producator("apple").size() == 2);
	assert(mag.filtrare_pret(25).size() == 1);
	vector<Produs> lista=mag.sortare(comp_nume_tip);
	assert(lista[0].get_tip() == "gaming");
	assert(lista[1].get_tip() == "linux");
	assert(lista[2].get_tip() == "ubuntu");
	lista = mag.sortare(comp_pret);
	assert(lista[0].get_price() == 1.22);
	assert(lista[1].get_price() == 2.22);
	assert(lista[2].get_price() == 51.22);

}



