#include "repository.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
Repository* createEmpty(DestroyFunction destr) {
	Repository* rez=malloc(sizeof(Repository));
	rez->len = 0;
	rez->cap = 2;
	rez->elems = malloc(sizeof(ElemType) * rez->cap);
	rez->dfnc = destr;
	return rez;
}

void destroy(Repository* l) {
	for (int i = 0; i < l->len; i++)
		//destrf(l->elems[i]);
		l->dfnc(l->elems[i]);

	free(l->elems);

	free(l);
}

void ensureCapacity(Repository* l) {
	
	if (l->len < l->cap)
		return;
	
	int newCapacity = l->cap * 2;
	ElemType* nElems = malloc(sizeof(ElemType) * newCapacity);

	if (nElems) {
		for (int i = 0; i < l->len; i++)
			nElems[i] = l->elems[i];

		free(l->elems);
		l->elems = nElems;
		l->cap = newCapacity;
	}
}

void add(Repository* l, ElemType el) {
	ensureCapacity(l);
	l->elems[l->len] = el;
	l->len++;
}

int size(Repository* l) {
	return l->len;
}

ElemType get(Repository* l, int poz) {
	return l->elems[poz];
}

Repository* copyRepo(Repository* l,CopyFct cf) {
	Repository* rez = createEmpty(l->dfnc);
	for (int i = 0; i < size(l); i++) {
		ElemType p = get(l, i);
		add(rez, cf(p));
	}
	return rez;
}

void update(Repository* l, int poz, Participant* p) {
	setNume(l->elems[poz], p->nume);
	setPrenume(l->elems[poz], p->prenume);
	setScor(l->elems[poz], p->scor);
}

void removeElement(Repository* l, int poz) {
	update(l, poz, l->elems[l->len - 1]);
	destroyParticipant(l->elems[l->len - 1]);
	l->len--;
}
ElemType remove_last(Repository* l)
{
	ElemType rez = l->elems[l->len - 1];
	l->len--;
	return rez;
}

void testCreate() {
	Repository* l = createEmpty(destroyParticipant);
	assert(size(l) == 0);
	destroy(l);
}

void testAdd() {
	Repository* l = createEmpty(destroyParticipant);
	add(l, createParticipant("Codrea", "Ionut", 9.78));
	add(l, createParticipant("Pop", "Milena", 7.66));
	assert(size(l) == 2);

	Participant* p = get(l, 0);
	assert(strcmp(p->nume, "Codrea") == 0);

	p = get(l, 1);
	assert(strcmp(p->prenume, "Milena") == 0);

	destroy(l);

}

void testCopyRepo() {
	Repository* l = createEmpty(destroyParticipant);
	add(l, createParticipant("Codrea", "Ionut", 9.78));
	add(l, createParticipant("Pop", "Milena", 7.66));

	Repository* l_copie = copyRepo(l,copyParticipant);
	assert(size(l_copie) == 2);

	Participant* p = get(l_copie, 0);
	assert(strcmp(p->nume, "Codrea") == 0);

	destroy(l);
	destroy(l_copie);
}

void testUpdate() {
	Repository* l = createEmpty(destroyParticipant);
	add(l, createParticipant("Codrea", "Ionut", 9.78));
	add(l, createParticipant("Pop", "Milena", 7.66));

	Participant* p = createParticipant("Bobo", "Coco", 5.66);
	update(l, 1, p);

	destroyParticipant(p);
	p = get(l, 1);
	assert(strcmp(p->nume, "Bobo") == 0);
	assert(strcmp(p->prenume, "Coco") == 0);
	assert(p->scor == 5.66);

	destroy(l);
}

void testRemove() {
	Repository* l = createEmpty(destroyParticipant);
	add(l, createParticipant("Codrea", "Ionut", 9.78));
	add(l, createParticipant("Pop", "Milena", 7.66));
	add(l, createParticipant("Popa", "Adrian", 6.66));

	removeElement(l, 1);
	Participant* p = get(l, 1);
	Participant* p_copy = copyParticipant(p);
	assert(strcmp(p->nume,p_copy->nume)==0);
	assert(strcmp(p->prenume, p_copy->prenume) == 0);
	assert(p->scor == p_copy->scor);
	assert(strcmp(p->nume, "Popa") == 0);
	assert(size(l) == 2);

	removeElement(l, 0);
	assert(size(l) == 1);
	
	
	removeElement(l, 0);
	assert(size(l) == 0);
	
	destroy(l);
	
	destroyParticipant(p_copy);
}

void testListeDeliste()
{
	Repository* my_participanti = createEmpty(destroyParticipant);
	add(my_participanti, createParticipant("dan", "dan", 3.3));
	add(my_participanti, createParticipant("dani", "dani", 9.3));

	Repository* my_participanti2 = createEmpty(destroyParticipant);
	Repository* undoL = createEmpty(destroy);

	add(undoL, my_participanti);
	assert(size(undoL) == 1);
	add(undoL, my_participanti2);
	assert(size(undoL) == 2);
	destroy(undoL);
}
