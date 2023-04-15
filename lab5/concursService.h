#pragma once
#include "repository.h"

typedef struct {
	Repository* participanti;
	Repository* undoList;
} Concurs;

/// <summary>
/// Creaza un concurs, unde sunt stocati participanti
/// </summary>
/// <returns> Concurs </returns>
Concurs createConcurs();

/// <summary>
/// Dealoca spatiul ocupat de consurs
/// </summary>
/// <param name="c"> Concurs* </param>
void destroyConcurs(Concurs* c);

/// <summary>
/// Adauga un participant in concurs
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="nume"> char* </param>
/// <param name="prenume"> char* </param>
/// <param name="scor"> double </param>
/// <returns></returns>
int addParticipant(Concurs* c, char* nume, char* prenume, double scor);

/// <summary>
/// Actualizeaza numele, prenumele si scorul participantului al carui nume este nume_vechi si prenume prenume_vechi
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="nume_vechi"> char* </param>
/// <param name="prenume_vechi"> char* </param>
/// <param name="nume_nou"> char* </param>
/// <param name="prenume_nou"> char* </param>
/// <param name="scor_nou"> double </param>
/// <returns> 1, daca numele este invalid
///           2, daca prenumele este invalid
///           3, daca scorul este invalid
///           4, daca participantul nu se afla in lista
///           0, daca operatia s-a realizat cu succes </returns>
int updateParticipant(Concurs* c, char* nume_vechi, char* prenume_vechi, char* nume_nou, char* prenume_nou, double scor_nou);

/// <summary>
/// Sterge participantul cu numele si prenumele dat
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="nume"> char* </param>
/// <param name="prenume"> char* </param>
/// <returns> 1, daca participantul nu exista in lista 
///           0, daca operatia s-a realizat cu succes </returns>
int removeParticipant(Concurs* c, char* nume, char* prenume);

/// <summary>
/// Returneaza lista de participanti din concurs
/// </summary>
/// <param name="c"> Concurs* </param>
/// <returns> Repository </returns>
Repository* getAllParticipanti(Concurs* c);

/// <summary>
/// Returneaza pozitia pe care se regaseste participantul cu numele dat
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="nume"> char* </param>
/// <param name="prenume"> char* </param>
/// <returns> -1, daca numele nu se regaseste in lista
///           poz, altfel </returns>
int pozInLista(Concurs* c, char* nume, char* prenume);

/// <summary>
/// Returneaza lista cu participanti care au scorul mai mic decat scorul dat
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="scor_minim"> double </param>
/// <returns> Repository </returns>
Repository* filtrareScor(Concurs* c, double scor_maxim);

/// <summary>
/// Returneaza lista cu participanti ale caror nume incep cu litera data
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="litera"> char </param>
/// <returns> Repository </returns>
Repository* filtrareLiteraNume(Concurs* c, char litera);

/// <summary>
/// Compara numele celor 2 participanti
/// </summary>
/// <param name="p1"> Participant* </param>
/// <param name="p2"> Participant* </param>
/// <returns> 0, daca numele sunt egale 
///           -1, daca primul nume < al doilea nume 
///           1, altfel </returns>
int cmpNumeCresc(Participant* p1, Participant* p2);

/// <summary>
/// Compara numele celor 2 participanti
/// </summary>
/// <param name="p1"> Participant* </param>
/// <param name="p2"> Participant* </param>
/// <returns> 0, daca numele sunt egale
///           -1, daca numele al doilea > primul nume
///           1, altfel </returns>
int cmpNumeDescresc(Participant* p1, Participant* p2);

/// <summary>
/// Returneaza lista sortata crescator/descrescator dupa nume
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="descrescator"> int 
///                             = 0, sortare crescatoare
///                             = 1, sortare descresctoare</param>
/// <returns> Repository </returns>
Repository* sortNume(Concurs* c, int descrescator);

/// <summary>
/// Compara scorurile date
/// </summary>
/// <param name="s1"> Participant* </param>
/// <param name="s2"> Participant* </param>
/// <returns> 0, daca cele 2 scoruri sunt egale 
///           -1, daca s1 < s2 
///           1, altfel </returns>
int cmpScorCresc(Participant* p1, Participant* p2);

/// <summary>
/// Compara scorurile date
/// </summary>
/// <param name="s1"> Participant* </param>
/// <param name="s2"> Participant* </param>
/// <returns> 0, daca cele 2 scoruri sunt egale 
///           -1, daca s1 > s2
///           1, altfel </returns>
int cmpScorDescresc(Participant* p1, Participant* p2);

/// <summary>
/// Sorteaza participantii din lista dupa scorul obtinut
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="descrescator"> int
///                             = 0, sortare crescatoare
///                             = 1, sortare descrescatoare </param>
Repository* sortScor(Concurs* c, int descrescator);


/// <summary>
/// Returneaza lista cu participanti care au scorul mai mare decat scorul dat
/// </summary>
/// <param name="c"> Concurs* </param>
/// <param name="scor_minim"> double </param>
/// <returns> Repository </returns>
Repository* filtrareScor_mai_mare(Concurs* c, double scor_minim);


int undo(Concurs* c);



void testAddService();
void testGetAllService();
void testUpdateService();
void testRemoveService();
void testFiltrareScor();
void testFiltrareLiteraNume();
void testSortNume();
void testSortScor();