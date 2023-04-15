#include "ui.h"
#include "repo.h"
#include "validare.h" 
#include "service.h"
#include <assert.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


/*
  Functie folosit in teste
  primeste vector prin valoare -> copy constructor
  returneaza prin valoare -> copy constructor sau move constructor
*/
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	double totalPrice = 0;
	for (auto el : v) {
		totalPrice += el.get_price();
	}
	Produs p{ 22,"nume","producator","tip"};
	v.push_back(p);
	return v;
}

template <typename MyVector>
void addProduse(MyVector& v, int cate) {
	for (int i = 0; i < cate; i++) {
		Produs p{ i + 10.0,std::to_string(i) + "_nume",std::to_string(i) + "_producator",std::to_string(i) + "_tip" };
		v.push_back(p);
	}
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addProduse(v, 100);
	assert(v.size() == 100);
	assert(v.get(50).get_tip() == "50_tip");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2.get(50).get_tip() == "50_tip");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3.get(50).get_tip() == "50_tip");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4.get(50).get_tip() == "50_tip");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(), MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	addProduse(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}

template <typename MyVector>
void testAll() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}

void test_all() {

	test_produs();
	test_repo();
	test_validator();
	teste_service();
	test_filtrari();
    testAll<VectorDinamic<Produs>>();

}
int main() {
	test_all();
	//Repo repo;
	//Validator validator;
	//Magazin mag{ repo,validator };
	//UI UI{ mag };
	//UI.run();
	_CrtDumpMemoryLeaks();

}