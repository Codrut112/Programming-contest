#include "concursService.h"
#include "sortare.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "participant.h"
Concurs createConcurs() {
	Concurs rez;
	rez.participanti = createEmpty(destroyParticipant);
	rez.undoList = createEmpty(destroy);
	return rez;
}

void destroyConcurs(Concurs* c) {
	destroy(c->participanti);
	destroy(c->undoList);
}

int addParticipant(Concurs* c, char* nume, char* prenume, double scor) {
	Participant* p = createParticipant(nume, prenume, scor);
	int errorCode = validateParticipant(*p);

	if (errorCode) {
		destroyParticipant(p);
		return errorCode;
	}
	Repository* to_undo = copyRepo(c->participanti, copyParticipant);
	add(c->participanti, p);
	add(c->undoList, to_undo);
	
	return 0;
}

Repository* getAllParticipanti(Concurs* c) {
	return copyRepo(c->participanti,copyParticipant);
}

int pozInLista(Concurs* c, char* nume, char* prenume) {
	Repository* lista = createEmpty(destroyParticipant);
	
	for (int i = 0; i < c->participanti->len; i++) {
		
		if (strcmp(get_nume(c->participanti->elems[i]), nume) == 0 && strcmp(get_prenume(c->participanti->elems[i]), prenume) == 0) {
			destroy(lista);
			return i;
		}
	}

	destroy(lista);
	return -1;
}

int updateParticipant(Concurs* c, char* nume, char* prenume, char* nume_nou, char* prenume_nou, double scor_nou) {
	Participant* p = createParticipant(nume_nou, prenume_nou, scor_nou);
	int errorCode = validateParticipant(*p);
	
	if (errorCode) {
		destroyParticipant(p);
		return errorCode;
	}
	
	int poz = pozInLista(c, nume, prenume);
	
	if (poz == -1) {
		destroyParticipant(p);
		return 4;
	}

	Repository* to_undo = copyRepo(c->participanti, copyParticipant);
	update(c->participanti, poz, p);
	add(c->undoList, to_undo);
	destroyParticipant(p);

	return 0;
}

int removeParticipant(Concurs* c, char* nume, char* prenume) {
	int poz = pozInLista(c, nume, prenume);
	if (poz == -1)
		return 1;
	Repository* to_undo = copyRepo(c->participanti, copyParticipant);
	removeElement(c->participanti, poz);
	add(c->undoList, to_undo);
	return 0;
}

Repository* filtrareScor(Concurs* c, double scor_maxim) {
	Repository* l = getAllParticipanti(c);
	for (int i = 0; i < size(l); i++) {
		if (get_score(l->elems[i]) >= scor_maxim) {
			removeElement(l, i);
			i--;
		}
	}

	return l;
}

Repository* filtrareLiteraNume(Concurs* c, char litera) {
	Repository* l = getAllParticipanti(c);
	for (int i = 0; i < size(l); i++) {
		char* nume = get_nume(l->elems[i]);
		if (tolower(nume[0]) != tolower(litera)) {
			removeElement(l, i);
			i--;
		}
	}

	return l;
}

int cmpNumeCresc(Participant* p1, Participant* p2) {
	return strcmp(p1->nume, p2->nume);
}

int cmpNumeDescresc(Participant* p1, Participant* p2) {
	return strcmp(p2->nume, p1->nume);
}

Repository* sortNume(Concurs* c, int descrescator) {
	Repository* l = getAllParticipanti(c);

	if (!descrescator) {
		sort(l, cmpNumeCresc);
	}

	else {
		sort(l, cmpNumeDescresc);
	}

	return l;
}

int cmpScorCresc(Participant* p1, Participant* p2) {
	double dif = p1->scor - p2->scor;
	if (dif < 0)
		return -1;
	else if (dif == 0)
		return 0;
	else
		return 1;
}

int cmpScorDescresc(Participant* p1, Participant* p2) {
	double dif = p1->scor - p2->scor;
	if (dif > 0)
		return -1;
	else if (dif == 0)
		return 0;
	else
		return 1;
}

Repository* sortScor(Concurs* c, int descrescator) {
	Repository* l = getAllParticipanti(c);

	if (!descrescator)
		sort(l, cmpScorCresc);

	else
		sort(l, cmpScorDescresc);

	return l;
}

Repository* filtrareScor_mai_mare(Concurs* c, double scor_minim)
{
	Repository* l = getAllParticipanti(c);
	for (int i = 0; i < size(l); i++) {
		if (get_score(l->elems[i]) <= scor_minim) {
			removeElement(l, i);
			i--;
		}
	}

	return l;
}


int undo(Concurs* c) {
	if (size(c->undoList) == 0)
		return 1;
	Repository* l = remove_last(c->undoList);
	destroy(c->participanti);;
	c->participanti = l;
	return 0;
}




void testAddService() {
	Concurs c = createConcurs();
	assert(addParticipant(&c, "", "", 43) == 1);
	assert(addParticipant(&c, "Manea", "", 3) == 2);
	assert(addParticipant(&c, "Manea", "Paul", 32.2) == 3);
	
	assert(addParticipant(&c, "Manea", "Paul", 9.12) == 0);

	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);
	assert(size(c.participanti) == 3);
	destroyConcurs(&c);
}

void testGetAllService() {
	Concurs c = createConcurs();
	addParticipant(&c, "Blaga", "Dorian", 5.88);
	undo(&c);
	assert(size(c.participanti) == 0);
	addParticipant(&c, "Plart", "Bebe", 7.56);

	Repository* l = getAllParticipanti(&c);
	assert(size(l) == 1);
	destroy(l);
	destroyConcurs(&c);
}

void testUpdateService() {
	Concurs c = createConcurs();
	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);
	
	assert(updateParticipant(&c, "Popa", "", "Marina", "Marian", 5.55) == 4);
	assert(updateParticipant(&c, "Blaga", "Dorian", "", "Bobo", 9.8) == 1);
	assert(updateParticipant(&c, "Plart", "Bebe", "Noul", "Nume", 78.0) == 3);
	assert(updateParticipant(&c, "Plart", "Bebe", "Noul", "Nume", 8.0) == 0);
	Participant* p = get(c.participanti, 1);
	assert(strcmp(p->nume, "Noul") == 0);
	assert(strcmp(p->prenume, "Nume") == 0);
	assert(p->scor == 8);
	undo(&c);
    assert(get_score(c.participanti->elems[1]) == 7.56);
    destroyConcurs(&c);
}

void testRemoveService() {
	Concurs c = createConcurs();

	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);

	assert(removeParticipant(&c, "Tristan", "") == 1);
	assert(removeParticipant(&c, "Blaga", "Dorian") == 0);
	assert(size(c.participanti) == 1);
	removeParticipant(&c, "Plart", "Bebe");
	assert(size(c.participanti) == 0);
	assert(removeParticipant(&c, "Plart", "Bebe") == 1);
	undo(&c);
	assert(size(c.participanti) == 1);
	destroyConcurs(&c);
}

void testFiltrareScor() {
	Concurs c = createConcurs();
	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);
	addParticipant(&c, "Banana", "Bebe", 1);
	addParticipant(&c, "Plart", "Boni", 9.87);
	addParticipant(&c, "Papa", "Joseph", 7.57);
	addParticipant(&c, "Stan", "Louie", 3.66);

	Repository *l = filtrareScor(&c, 7.57);

	assert(size(l) == 4);
	destroy(l);

	l = filtrareScor_mai_mare(&c, 7.57);
	assert(size(l) == 1);
	destroy(l);

	l = filtrareScor(&c, 2);
	assert(size(l) == 1);

	Participant* p = get(l, 0);
	assert(strcmp(p->nume, "Banana") == 0);

	destroy(l);
	destroyConcurs(&c);

}

void testFiltrareLiteraNume() {
	Concurs c = createConcurs();
	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);
	addParticipant(&c, "Banana", "Bebe", 1);
	addParticipant(&c, "Plart", "Boni", 9.87);
	addParticipant(&c, "Papa", "Joseph", 7.57);
	addParticipant(&c, "Stan", "Louie", 3.66);

	Repository *l = filtrareLiteraNume(&c, 'p');
	assert(size(l) == 3);
	destroy(l);

	l = filtrareLiteraNume(&c, 'S');
	assert(size(l) == 1);

	Participant* p = get(l, 0);
	assert(strcmp(p->nume, "Stan") == 0);

	destroy(l);
	destroyConcurs(&c);
}

void testSortNume() {
	Concurs c = createConcurs();
	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);
	addParticipant(&c, "Banana", "Bebe", 1);
	addParticipant(&c, "Plart", "Boni", 9.87);
	addParticipant(&c, "Papa", "Joseph", 7.57);
	addParticipant(&c, "Stan", "Louie", 3.66);

	Repository* l = sortNume(&c, 0);
	assert(size(l) == 6);
	Participant* p = get(l, 0);

	assert(strcmp(p->nume, "Banana") == 0);
	p = get(l, 1);
	assert(strcmp(p->nume, "Blaga") == 0);
	p = get(l, 4);
	assert(strcmp(p->nume, "Plart") == 0);
	destroy(l);

	l = sortNume(&c, 1);
	assert(size(l) == 6);
	p = get(l, 0);
	assert(strcmp(p->nume, "Stan") == 0);
	p = get(l, 5);
	assert(strcmp(p->nume, "Banana") == 0);

	destroy(l);
	destroyConcurs(&c);
}

void testSortScor() {
	Concurs c = createConcurs();
	assert(undo(&c) == 1);
	addParticipant(&c, "Blaga", "Dorian", 5.88);
	addParticipant(&c, "Plart", "Bebe", 7.56);
	addParticipant(&c, "Banana", "Bebe", 1);
	addParticipant(&c, "Plart", "Boni", 9.87);
	addParticipant(&c, "Papa", "Joseph", 7.57);
	addParticipant(&c, "Stan", "Louie", 1);

	Repository* l = sortScor(&c, 0);
	assert(size(l) == 6);
	Participant* p = get(l, 0);
	assert(p->scor == 1);
	p = get(l, 1);
	assert(p->scor == 1);
	p = get(l, 4);
	assert(p->scor == 7.57);
	destroy(l);

	l = sortScor(&c, 1);
	assert(size(l) == 6);
	p = get(l, 0);
	assert(p->scor == 9.87);
	p = get(l, 5);
	assert(p->scor == 1);

	destroy(l);
	destroyConcurs(&c);
}