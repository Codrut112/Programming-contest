#pragma once
#include "service.h"
class UI {
private:
	Magazin& mag;
	//adauga un produs
	void adaugaUI();
	//tipareste toate produsele
	void tiparesteUI();
	//modifica un produs
	void modificaUI();
	//sterge un produs
	void stergeUI();
	//filtrari
	void filtrareUI();
	void sortareUI();
public:
	//constructor
	UI(Magazin& mag) :mag{ mag } {};
	//impiedica crearea de copii
	UI(const UI& ot) = delete;
	void run();
};