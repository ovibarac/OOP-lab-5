#ifndef TRANZACTIE_H_
#define TRANZACTIE_H_

typedef struct {
	int ziua;
	double suma;
	char* tip;
	char* descriere;
} Tranzactie;

Tranzactie* createTranzactie(int ziua, double suma, char* tipul, char* descriere);

void destroyTranzactie(Tranzactie* t);

int valideazaTranzactie(Tranzactie* t);

Tranzactie* copyTranzactie(Tranzactie* t);

void testCreateDestroy();

void testValideaza();

void testCopyTranzactie();



#endif