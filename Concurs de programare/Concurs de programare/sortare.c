#include "sortare.h"

void sort(Repository* l, Compara cmp) {
	int len = size(l);

	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (cmp(&l->elems[i], &l->elems[j]) > 0) {
				Participant aux = l->elems[i];
				l->elems[i] = l->elems[j];
				l->elems[j] = aux;
			}
		}
	}
}