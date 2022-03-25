#pragma once
#include "lista.h"

typedef struct {
	MyList* allTranzactii;
	MyList* undoList;
}TranzactiiStore;

TranzactiiStore createTranzactiiStore();

void destroyTranzactiiStore(TranzactiiStore* store);

int addTranzactie(TranzactiiStore* store, char* tip, char* descriere, int zi, double suma);

int undo(TranzactiiStore* store);

int findTranzactie(TranzactiiStore* store, char* tip, int zi, double suma);

int deleteTranzactie(TranzactiiStore* store, char* tip, char* descriere, int ziua, double suma);

int modifyTranzactie(TranzactiiStore* store, int ziua, double suma, char* tip, char* descriere);

void testAddService();

void testFindService();

void testModifyService();

void testDeleteService();

MyList* filterTranzactiitip(TranzactiiStore* store, char* tip);

MyList* filterTranzactiiZi(TranzactiiStore* store, int zi);

MyList* filterTranzactiiSumaMaiMare(TranzactiiStore* v, float suma);

MyList* filterTranzactiiSumaMaiMica(TranzactiiStore* v, float suma);

void testFilterService();

int cmpSuma(Tranzactie* t1, Tranzactie* t2);

int cmpZiua(Tranzactie* t1, Tranzactie* t2);

MyList* sortTranzactiiBySuma(TranzactiiStore* store);

MyList* sortTranzactiiByZiua(TranzactiiStore* store);

void testSortareSuma();

void testSortareZiua();

