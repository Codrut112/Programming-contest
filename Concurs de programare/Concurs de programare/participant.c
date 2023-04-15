#include "participant.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

Participant createParticipant(char* nume, char* prenume, double scor) {
	Participant rez;
	
	size_t len = strlen(nume) + 1;
	rez.nume = malloc(sizeof(char) * len);
	
	if(rez.nume)
		strcpy_s(rez.nume, len, nume);

	len = strlen(prenume) + 1;
	rez.prenume = malloc(sizeof(char) * len);

	if(rez.prenume)
		strcpy_s(rez.prenume, len, prenume);

	rez.scor = scor;
	return rez;
}

void destroyParticipant(Participant* p) {
	free(p->nume);
	free(p->prenume);
	p->nume = NULL;
	p->prenume = NULL;
	p->scor = -1;
}

void setNume(Participant* p, char* nume_nou) {
	free(p->nume);
	p->nume = malloc(sizeof(char) * (strlen(nume_nou) + 1));
	
	if(p->nume)
		strcpy_s(p->nume, strlen(nume_nou) + 1, nume_nou);
}

void setPrenume(Participant* p, char* prenume_nou) {
	free(p->prenume);
	p->prenume = malloc(sizeof(char) * (strlen(prenume_nou) + 1));
	
	if(p->prenume)
		strcpy_s(p->prenume, strlen(prenume_nou) + 1, prenume_nou);
}

void setScor(Participant* p, double scor_nou) {
	p->scor = scor_nou;
}

int validateParticipant(Participant p) {
	if (strlen(p.nume) == 0)
		return 1;

	if (strlen(p.prenume) == 0)
		return 2;

	if (p.scor < 0 || p.scor > 10)
		return 3;

	return 0;
}

Participant copyParticipant(Participant* p) {
	Participant rez = createParticipant(p->nume, p->prenume, p->scor);
	return rez;
}

void testCreateDestroy() {
	Participant p = createParticipant("Codrea", "Ionut", 7.89);
	assert(strcmp(p.nume, "Codrea") == 0);
	assert(strcmp(p.prenume, "Ionut") == 0);
	assert(p.scor == 7.89);

	destroyParticipant(&p);
	assert(p.nume == NULL);
	assert(p.prenume == NULL);
	assert(p.scor == -1);
}

void testValidate() {
	Participant p = createParticipant("", "", -9.88);
	assert(validateParticipant(p) == 1);

	setNume(&p, "Popa");
	assert(validateParticipant(p) == 2);

	setPrenume(&p, "Marian");
	assert(validateParticipant(p) == 3);

	setScor(&p, 9.77);
	assert(validateParticipant(p) == 0);

	destroyParticipant(&p);
}

void testCopyParticipant() {
	Participant p = createParticipant("Manea", "George", 9.88);
	Participant p_copie = copyParticipant(&p);
	assert(strcmp(p_copie.nume, "Manea") == 0);
	assert(strcmp(p_copie.prenume, "George") == 0);
	assert(p_copie.scor == 9.88);
	destroyParticipant(&p);
	destroyParticipant(&p_copie);
}