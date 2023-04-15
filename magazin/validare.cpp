#include "validare.h"
#include <assert.h>
ValidError::ValidError(string msg)
{
	this->msg = msg;
}

string ValidError::get_message()
{
	
		return msg;
	
}

void Validator::valideaza(Produs& p)const
{
	string error;
	if (p.get_price() <= 0) error += "pret invalid";
	if (p.get_nume() == "")error += "nume invalid";
	if (p.get_producator() == "")error += "producator invalid";
	if (p.get_tip() == "")error += "tip invalid";
	if (!error.empty()) throw ValidError(error);
}



void test_validator()
{
	Produs p = Produs(1, "apa", "dorna", "plata");
	Validator v;
	v.valideaza(p);
	p = Produs(1, "", "dorna", "plata");
	try {
		v.valideaza(p);
		assert(false);

	}
	catch (ValidError& v) { 
		assert(v.get_message() == "nume invalid");
		assert(true); }
}
