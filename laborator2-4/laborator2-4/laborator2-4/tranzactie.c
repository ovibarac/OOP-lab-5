#include "tranzactie.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Tranzactie* createTranzactie(int ziua, double suma, char* tipul, char* descriere) {
	Tranzactie* t = malloc(sizeof(Tranzactie));
	t->ziua = ziua;
	t->suma = suma;
	int nrC = (int)strlen(tipul) + 1;
	t->tip = malloc(nrC * sizeof(char));
	strcpy_s(t->tip, nrC, tipul);
	nrC = (int)strlen(descriere) + 1;
	t->descriere = malloc(nrC * sizeof(char));
	strcpy_s(t->descriere, nrC, descriere);
	return t;
}

void destroyTranzactie(Tranzactie* t) {
	free(t->descriere);
	free(t->tip);
	t->suma = 0;
	t->ziua = 0;
}

Tranzactie* copyTranzactie(Tranzactie* t) {
	return createTranzactie(t->ziua, t->suma, t->tip, t->descriere);
}

int valideazaTranzactie(Tranzactie* t) {
	if (strlen(t->tip) == 0)
		return 0;
	if (strcmp(t->tip, "iesire") != 0 && strcmp(t->tip, "intrare") != 0)
		return 0;
	if (strlen(t->descriere) == 0)
		return 0;
	if (t->suma<=0)
		return 0;
	if (t->ziua < 1 || t->ziua>31)
		return 0;
	return 1;
}

void testCreateDestroy() {
	Tranzactie* t = createTranzactie(5, 45.7, "iesire", "datorie");

	assert(strcmp(t->tip, "iesire") == 0);
	assert(strcmp(t->descriere, "datorie") == 0);
	assert(t->ziua == 5);
	assert(t->suma == (double)45.7);

	destroyTranzactie(t);
}

void testValideaza() {
	Tranzactie* t1 = createTranzactie(34, 76, "iesire", "hchuc");
	assert(valideazaTranzactie(t1) == 0);
	Tranzactie* t2 = createTranzactie(0, 76, "iesire", "hchuc");
	assert(valideazaTranzactie(t2) == 0);
	Tranzactie* t3 = createTranzactie(5, -76, "iesire", "hchuc");
	assert(valideazaTranzactie(t3) == 0);
	Tranzactie* t4 = createTranzactie(5, 76, "jxdej", "hchuc");
	assert(valideazaTranzactie(t4) == 0);
	Tranzactie* t5 = createTranzactie(7 , 76, "iesire", "");
	assert(valideazaTranzactie(t5) == 0);
	Tranzactie* t7 = createTranzactie(7, 76, "", "jncdjjch");
	assert(valideazaTranzactie(t7) == 0);
	Tranzactie* t6 = createTranzactie(14, 76.2, "iesire", "dwedewedbecb");
	assert(valideazaTranzactie(t6) == 1);
	destroyTranzactie(t1);
	destroyTranzactie(t2);
	destroyTranzactie(t3);
	destroyTranzactie(t4);
	destroyTranzactie(t5);
	destroyTranzactie(t6);
	destroyTranzactie(t7);
}

void testCopyTranzactie()
{
	Tranzactie* t = createTranzactie(5, 45.7, "iesire", "datorie");
	Tranzactie* tc = copyTranzactie(t);
	assert(tc->ziua == 5);
	assert(tc->suma == 45.7);
	destroyTranzactie(t);
	destroyTranzactie(tc);
}