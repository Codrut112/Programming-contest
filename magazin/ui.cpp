#include "ui.h"
#include<iostream>
#include "sortare.h"
using std::cout;
using std::cin;
void UI::adaugaUI() {
	double pret;
	string nume, producator, tip;
	cout << "nume:";
	cin >> nume;
	cout << "producator:";
	cin >> producator;
	cout << "tip:";
	cin >> tip;
	cout << "pret:";
	cin >> pret;
	mag.adauga(pret, nume, producator, tip);
	cout << "produs adaugat\n";
}
void UI::tiparesteUI() {
	vector<Produs> produse = mag.get_all();
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}
} 

void UI::modificaUI() {
	double pret;
	string nume, producator, tip;
	cout << "nume:";
	cin >> nume;
	cout << "producator:";
	cin >> producator;
	cout << "tip:";
	cin >> tip;
	cout << "pret:";
	cin >> pret;
	mag.modifica(pret,nume,producator,tip);
	cout << "produs modificat\n";

}
void UI::stergeUI() {
	string nume;
	cout << "nume:";
	cin >> nume;
	mag.sterge(nume);
	cout << "produs sters\n";
}
void UI::filtrareUI()
{
	vector<Produs> produse;
	int caz;
	cout << "dupa ce vrei sa filtrezi ?\npret:1\nnume:2\nproducator:3\n";
	cin >> caz;
	switch (caz)
	{
	case 1:
	{cout << "pretul:";
	double pret;
	cin >> pret;
	produse = mag.filtrare_pret(pret);
	break; }
	case 2:
	{cout << "nume:";
	string nume;
	cin >> nume;
	produse = mag.filtrare_nume(nume);
	break; }
	case 3:
	{cout << "producator:";
	string producator;
	cin >> producator;
	produse = mag.filtrare_producator(producator);
	break; }
	default:break;
}
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}

}


void UI::sortareUI()
{
	vector<Produs> produse;
	cout << "dupa ce vrei sa sortezi? \n1:nume\n2:pret\n3:nume+tip\n";
	int caz;
	cin >> caz;
	switch (caz) {
	case 1:
		produse = mag.sortare(comp_nume);
		break;
	case 2:
		produse = mag.sortare(comp_pret);
		break;
	case 3:
		produse = mag.sortare(comp_nume_tip);
		break;
	default:break;

	}
	for (const auto& produs : produse) {
		cout << produs.get_nume() << " " << produs.get_producator() << " " << produs.get_tip() << " " << produs.get_price() << '\n';

	}

}

void UI::run()
{
	int cmd ;
	while (true) {
		cout << "Meniu\n";
		cout << "1 adauga\n2 tipareste\n3 modifica\n4 sterge\n5 filtrare\n6 sortare\n0 exit\n";
		cin >> cmd;
		try {
			switch (cmd)
			{
			case 0:return;
			case 1:
				adaugaUI();
				break;
			case 2:
				tiparesteUI();
				break;
			case 3:
				modificaUI();
				break;
			case 4:
				stergeUI();
				break;
			case 5:
				filtrareUI();
				break;
			case 6:
				sortareUI();
				break;
			default:cout << "comanda invalida\n";
			}
		}
		catch (RepoException& ex) {
			cout << ex.get_message()<<'\n';
		}
		catch (ValidError& ex) {
			cout << ex.get_message() << '\n';

		}
	}
}

	

