#pragma once
#include "repository.h"

/// <summary>
/// Functie care compara cei 2 participanti
/// Returneaza 0, daca cei 2 sunt egali
///            -1, daca p1 < p2
///            1, altfel
/// </summary>
typedef int(*Compara)(Participant* p1, Participant* p2);

/// <summary>
/// Sorteaza lista l, dupa criteriul cmp
/// </summary>
/// <param name="l"> Repository* </param>
/// <param name="cmp"> Compara (functie) </param>
void sort(Repository* l, Compara cmp);

