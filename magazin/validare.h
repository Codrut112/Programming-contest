#pragma once
#include "produs.h"
using std::ostream;
//aceasta clasa se ocupa cu validarea produselor introduse de utilizator
class ValidError {
private:
	//eroarea
	string msg;
public:
	ValidError(string m);
	//returneaza eroarea
	string get_message();
	

};
class Validator {

public:
	//functie de validare
	void valideaza(Produs& p)const;
	

		};





void test_validator();
