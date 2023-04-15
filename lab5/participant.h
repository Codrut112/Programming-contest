#pragma once

typedef struct {
	char* nume, * prenume;
	double scor;
} Participant;

/// <summary>
/// Creeaza un nou participant
/// </summary>
/// <param name="nume"> char* </param>
/// <param name="prenume"> char* </param>
/// <param name="scor"> double </param>
/// <returns> Participant </returns>
Participant* createParticipant(char* nume, char* prenume, double scor);

/// <summary>
/// Dealoca memoria ocupata de participant
/// </summary>
/// <param name="p"> Participant* </param>
void destroyParticipant(Participant* p);

/// <summary>
/// Valideaza participantul
/// </summary>
/// <param name="p"> Participant </param>
/// <returns> 0, daca participantul e valid 
///           1, daca numele e invalid
///           2, daca prenumele e invalid
///           3, daca scor < 0 sau scor > 10 </returns>
int validateParticipant(Participant p);

/// <summary>
/// Returneaza copia participantului p
/// </summary>
/// <param name="p"> Participant* </param>
/// <returns> Participant </returns>
Participant* copyParticipant(Participant* p);

/// <summary>
/// Modifica numele participantului
/// </summary>
/// <param name="p"> Participant* </param>
/// <param name="nume_nou"> char* </param>
void setNume(Participant* p, char* nume_nou);

/// <summary>
/// Modifica prenumele participantului
/// </summary>
/// <param name="p"> Participant* </param>
/// <param name="prenume_nou"> char* </param>
void setPrenume(Participant* p, char* prenume_nou);

/// <summary>
/// Modifica scorul participantului
/// </summary>
/// <param name="p"> Participant* </param>
/// <param name="scor_nou"> double </param>
void setScor(Participant* p, double scor_nou);


/// <returneaza numele participantului>
/// 
/// </summary>
/// <param name="p"></Participant>
/// <returns></char*>
char* get_nume(Participant* p);

/// <returneaza prenumele participantului>
/// 
/// </summary>
/// <param name="p"></Participant>
/// <returns></char*>
char* get_prenume(Participant* p);

/// <returneaza scorul participantului>
/// 
/// </summary>
/// <param name="p"></Participant>
/// <returns></char*>
double get_score(Participant* p);
/// <summary>
/// Functie de test pentru creare si distrugere participant
/// </summary>
void testCreateDestroy();
void testValidate();
void testCopyParticipant();
