#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include "participant.h"
#include "repository.h"
#include "concursService.h"

void testAll() {
	// teste domain
	testCreateDestroy();
	testValidate();
	testCopyParticipant();

	// teste repo
	testCreate();
	testAdd();
	testCopyRepo();
	testUpdate();
	testRemove();
	testListeDeliste();
	//teste service
	testAddService();
	testGetAllService();
	testUpdateService();
	testRemoveService();
	testFiltrareScor();
	testFiltrareLiteraNume();
	testSortNume();
	testSortScor();
}

void printMenu() {
	printf("1. Adauga participant\n2. Actualizeaza participant\n3. Sterge participant\n4. Afiseaza participantii\n5. Afiseaza participantii cu scor mai mic decat cel dat\n6. Afiseaza participantii al caror nume incepe cu litera data\n7. Sortare dupa nume\n8. Sortare dupa scor\n9. Afiseaza participantii cu scor mai mare decat cel dat\n0. Iesire\n\nIntrodu comanda: ");
}

void printParticipanti(Repository* l) {
	
	if (size(l) > 0) {
		for (int i = 0; i < size(l); i++) {
		
			Participant* p = get(l, i);
			printf("Nume: %s\nPrenume: %s\nScor: %lf\n\n", p->nume, p->prenume, p->scor);
		}
	}
	else printf("nu sunt participanti\n");
}

void addParticipantUI(Concurs* c) {
	printf("Nume: ");
	char nume[30];
	scanf_s("%s", nume, 30);

	printf("Prenume: ");
	char prenume[30];
	scanf_s("%s", prenume, 30);

	printf("Scor: ");
	double scor;
	scanf_s("%lf", &scor);

	int error = addParticipant(c, nume, prenume, scor);
	
	if (error)
		printf("Participant invalid!\n\n");
	else
		printf("Participant adaugat cu succes!\n\n");
}

void getAllUI(Concurs* c) {
	
	Repository* lista = getAllParticipanti(c);
	
	printParticipanti(lista);
	destroy(lista);
}

void updateParticipantUI(Concurs* c) {
	printf("Nume vechi: ");
	char nume_vechi[30];
	scanf_s("%s", nume_vechi, 30);

	printf("Prenume vechi: ");
	char prenume_vechi[30];
	scanf_s("%s", prenume_vechi, 30);

	printf("Nume nou: ");
	char nume_nou[30];
	scanf_s("%s", nume_nou, 30);

	printf("Prenume nou: ");
	char prenume_nou[30];
	scanf_s("%s", prenume_nou, 30);

	printf("Scor nou: ");
	double scor_nou;
	scanf_s("%lf", &scor_nou);

	int error = updateParticipant(c, nume_vechi, prenume_vechi, nume_nou, prenume_nou, scor_nou);
	if (error) {
		if (error == 4)
			printf("Participantul nu se afla in lista!\n\n");
		else
			printf("Date invalide!\n\n");
	}

	else
		printf("Participantul a fost modificat cu succes!\n\n");
}

void removeParticipantUI(Concurs* c) {
	printf("Nume: ");
	char nume[30];
	scanf_s("%s", nume, 30);

	printf("Prenume: ");
	char prenume[30];
	scanf_s("%s", prenume, 30);

	int error = removeParticipant(c, nume, prenume);
	if (error)
		printf("Participant inexistent!\n\n");

	else
		printf("Participant sters cu succes!\n\n");
}

void filtrareScorUI(Concurs* c) {
	double scor_maxim = 0;
	printf("Scor maxim: ");
	scanf_s("%lf", &scor_maxim);

	Repository* lista = filtrareScor(c, scor_maxim);
	printParticipanti(lista);
	destroy(lista);
}

void filtrareLiteraNumeUI(Concurs* c) {
	printf("Litera: ");
	char litera='0';
	scanf("%c", &litera);
	scanf("%c", &litera);

	Repository* lista = filtrareLiteraNume(c, litera);
	printParticipanti(lista);
	destroy(lista);
}

void sortNumeUI(Concurs* c) {
	printf("Crescator(tasteaza 0) sau descrescator(tasteaza 1): ");
	int ordine = 0;
	scanf_s("%d", &ordine);

	if (ordine != 1 && ordine != 0)
		ordine = 0;

	Repository* lista = sortNume(c, ordine);
	printParticipanti(lista);
	destroy(lista);
}

void sortScorUI(Concurs* c) {
	printf("Crescator(tasteaza 0) sau descrescator(tasteaza 1): ");
	int ordine = 0;
	scanf_s("%d", &ordine);

	if (ordine != 1 && ordine != 0)
		ordine = 0;

	Repository* lista = sortScor(c, ordine);
	printParticipanti(lista);
	destroy(lista);
}

void filtrareScorUI_mai_mare(Concurs* c) {
	double scor_minim = 0;
	printf("Scor minim: ");
	scanf_s("%lf", &scor_minim);

	Repository* lista = filtrareScor_mai_mare(c, scor_minim);
	printParticipanti(lista);
	destroy(lista);
}

void runUI() {
	Concurs c = createConcurs();
	int ok = 1;

	while (ok) {
		printMenu();
		int cmd = 0;
		scanf_s("%d", &cmd);

		switch (cmd) {
		case 1:
			addParticipantUI(&c);
			break;
		case 2:
			updateParticipantUI(&c);
			break;
		case 3:
			removeParticipantUI(&c);
			break;
		case 4:
			getAllUI(&c);
			break;
		case 5:
			filtrareScorUI(&c);
			break;
		case 6:
			filtrareLiteraNumeUI(&c);
			break;
		case 7:
			sortNumeUI(&c);
			break;
		case 8:
			sortScorUI(&c);
			break;
		case 9:
			filtrareScorUI_mai_mare(&c);
			break;
		case 10:
			if (undo(&c) != 0)printf("no more undo");
			break;
		case 0:
			ok = 0;
			destroyConcurs(&c);
			break;
		default:
			printf("Comanda invalida!\n\n");
		}
	}
}

int main() {
	testAll();
	runUI();
	_CrtDumpMemoryLeaks();
	return 0;
}