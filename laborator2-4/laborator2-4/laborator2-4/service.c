#pragma once
#include "service.h"
#include "customSort.h"
#include <assert.h>
#include <string.h>

TranzactiiStore createTranzactiiStore()
{
	TranzactiiStore store;
	store.allTranzactii = createEmpty(destroyTranzactie);
	store.undoList = createEmpty(destroyList);
	return store;
}

void destroyTranzactiiStore(TranzactiiStore* store) {
	destroyList(store->allTranzactii);
	destroyList(store->undoList);
}

int undo(TranzactiiStore* store){
    if(size(store->undoList)==0){
        return 1;
    }
    MyList* l = removeLast(store->undoList);
    destroyList(store->allTranzactii);
    store->allTranzactii = l;
    return 0;
}

int addTranzactie(TranzactiiStore* store, char* tip, char* descriere, int zi, double suma) {
	Tranzactie* t = createTranzactie(zi, suma, tip, descriere);
    MyList* toUndo = copyList(store->allTranzactii, copyTranzactie);
	int successful = valideazaTranzactie(t);
	if (!successful)
	{
		destroyTranzactie(t);
		return 0;
	}
	add(store->allTranzactii, t);
	add(store->undoList, toUndo);
	return 1;
}

int findTranzactie(TranzactiiStore* store, char* tip, int zi, double suma) {
	int poz_to_delete = -1;
	for (int i = 0; i < store->allTranzactii->length; i++) {
		Tranzactie* t = get(store->allTranzactii, i);
		if (t->suma == suma && t->ziua== zi && strcmp(t->tip, tip) == 0) {
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}
int deleteTranzactie(TranzactiiStore* store, char* tip, char* descriere, int ziua, double suma) {
	int poz_to_delete = findTranzactie(store, tip, ziua, suma);
	if (poz_to_delete != -1) {
        MyList* toUndo = copyList(store->allTranzactii, copyTranzactie);
        Tranzactie* t = delete(store->allTranzactii, poz_to_delete);
		destroyTranzactie(t);
        add(store->undoList, toUndo);
		return 1;
	}
	else
		return 0;
}
int modifyTranzactie(TranzactiiStore* store, int ziua, double suma, char* tip, char* descriere) {
	int poz_to_delete = findTranzactie(store, tip, ziua, suma);

	if (poz_to_delete != -1) {
		Tranzactie* T_Noua = createTranzactie(ziua, suma, tip, descriere);
        MyList* toUndo = copyList(store->allTranzactii, copyTranzactie);
		Tranzactie* t = setElem(store->allTranzactii, poz_to_delete, T_Noua);
		destroyTranzactie(t);
        add(store->undoList, toUndo);
		return 1;
	}
	else
		return 0;
}

MyList* filterTranzactiitip(TranzactiiStore* store, char* tip) {
	if (strcmp(tip, "") != 0)
	{
        MyList* filteredList = createEmpty(destroyTranzactie);
	    for (int i = 0; i < store->allTranzactii->length; i++) {
		    Tranzactie* t = get(store->allTranzactii, i);
		    if (strcmp(tip, t->tip) == 0)
			    add(filteredList, createTranzactie(t->ziua, t->suma, t->tip, t->descriere));
	    }
	    return filteredList;
	}
	else {
		return copyList(store->allTranzactii, copyTranzactie);
	}
	

}

MyList* filterTranzactiiSumaMaiMare(TranzactiiStore* store, float suma) {
	if (suma > 0)
	{
		MyList* filteredList = createEmpty(destroyTranzactie);
		for (int i = 0; i < store->allTranzactii->length; i++) {
			Tranzactie* t = get(store->allTranzactii, i);
			if (suma <= t->suma)
				add(filteredList, createTranzactie(t->ziua, t->suma, t->tip, t->descriere));
		}
		return filteredList;
	}
	else {
		return copyList(store->allTranzactii, copyTranzactie);
	}

}

MyList* filterTranzactiiSumaMaiMica(TranzactiiStore* store, float suma) {
	if (suma > 0)
	{
		MyList* filteredList = createEmpty(destroyTranzactie);

		for (int i = 0; i < store->allTranzactii->length; i++) {
			Tranzactie* t = get(store->allTranzactii, i);
			if (suma >= t->suma)
				add(filteredList, createTranzactie(t->ziua, t->suma, t->tip, t->descriere));
		}
		return filteredList;
	}
	else {
		return copyList(store->allTranzactii, copyTranzactie);
	}
}

int cmpSuma(Tranzactie* t1, Tranzactie* t2) {
	if (t1->suma == t2->suma)
		return 0;
	if (t1->suma > t2->suma)
		return 1;
	else
		return -1;
}

MyList* sortTranzactiiBySuma(TranzactiiStore* store) {
	MyList* songList = copyList(store->allTranzactii, copyTranzactie);
	sort(songList, cmpSuma);
	return songList;
}

int cmpZiua(Tranzactie* t1, Tranzactie* t2) {
	if (t1->ziua == t2->ziua)
		return 0;
	if (t1->ziua > t2->ziua)
		return 1;
	else
		return -1;
}

MyList* sortTranzactiiByZiua(TranzactiiStore* store) {
	MyList* songList = copyList(store->allTranzactii, copyTranzactie);
	sort(songList, cmpZiua);
	return songList;
}


void testAddService() {
	TranzactiiStore store = createTranzactiiStore();

	int successful1 = addTranzactie(&store, "intrare", "ceva", 5, 67.6);
	assert(successful1 == 1);

	int successful2 = addTranzactie(&store, "ndnse", "", 5, 78);
	assert(successful2 == 0);

	int successful3 = addTranzactie(&store, "intrare", "plata", -6, 888);
	assert(successful3 == 0);

	MyList* allSongs = filterTranzactiitip(&store, "");
	assert(size(allSongs) == 1);
	destroyList(allSongs);

	destroyTranzactiiStore(&store);

}

void testFindService() {
	TranzactiiStore v = createTranzactiiStore();


	int successful1 = addTranzactie(&v, "intrare", "ceva", 5, 67.6);
	assert(successful1 == 1);

	int successful2 = addTranzactie(&v, "iesire", "plata", 5, 78);
	assert(successful2 == 1);

	int successful3 = addTranzactie(&v, "intrare", "plata", 6, 888);
	assert(successful3 == 1);

	assert(size(v.allTranzactii) == 3);
	int poz = findTranzactie(&v, "iesire", 5, 78);

	assert(poz == 1);

	destroyTranzactiiStore(&v);
}

void testModifyService() {
	TranzactiiStore v = createTranzactiiStore();

	int successful1 = addTranzactie(&v, "intrare", "ceva", 5, 67.6);
	assert(successful1 == 1);

	int successful2 = addTranzactie(&v, "iesire", "plata", 5, 78);
	assert(successful2 == 1);

	int successful3 = addTranzactie(&v, "intrare", "plata", 6, 888);
	assert(successful3 == 1);

	assert(size(v.allTranzactii) == 3);
	int modify_success = modifyTranzactie(&v, 5, 78, "iesire", "datorie");
	assert(modify_success == 1);
	int modify_success2 = modifyTranzactie(&v, 7, 898, "intrare", "orice");
	assert(modify_success2 == 0);
	destroyTranzactiiStore(&v);
}

void testDeleteService() {
	TranzactiiStore v = createTranzactiiStore();
	int successful1 = addTranzactie(&v, "intrare", "ceva", 5, 67.6);
	assert(successful1 == 1);

	int successful2 = addTranzactie(&v, "iesire", "plata", 5, 78);
	assert(successful2 == 1);

	int successful3 = addTranzactie(&v, "intrare", "plata", 6, 888);
	assert(successful3 == 1);

	assert(size(v.allTranzactii) == 3);
	int succesful_del = deleteTranzactie(&v, "iesire", "plata", 5, 78);
	assert(succesful_del == 1);
	int succesfully_del = deleteTranzactie(&v, "intrare", "dchd", 9, 663);
	assert(succesfully_del == 0);
	destroyTranzactiiStore(&v);
}

void testFilterService() {
	TranzactiiStore v = createTranzactiiStore();

	int successful1 = addTranzactie(&v, "intrare", "ceva", 5, 67.6);
	assert(successful1 == 1);

	int successful2 = addTranzactie(&v, "iesire", "plata", 5, 78);
	assert(successful2 == 1);

	int successful3 = addTranzactie(&v, "intrare", "plata", 6, 888);
	assert(successful3 == 1);
	assert(size(v.allTranzactii) == 3);

	MyList* filteredList = filterTranzactiitip(&v, "intrare");
	assert(size(filteredList) == 2);
	destroyList(filteredList);


	filteredList = filterTranzactiiSumaMaiMare(&v, 70);
	assert(size(filteredList) == 2);
	destroyList(filteredList);


	filteredList = filterTranzactiiSumaMaiMare(&v, 1000);
	assert(size(filteredList) == 0);
	destroyList(filteredList);

	filteredList = filterTranzactiiSumaMaiMica(&v, 70);
	assert(size(filteredList) == 1);
	destroyList(filteredList);

	filteredList = filterTranzactiiSumaMaiMica(&v, 50);
	assert(size(filteredList) == 0);
	destroyList(filteredList);


	destroyTranzactiiStore(&v);

}

void testSortareSuma()
{
	TranzactiiStore v = createTranzactiiStore();
    int successful2 = addTranzactie(&v, "iesire", "plata", 5, 78);
	assert(successful2 == 1);
	
	int successful1 = addTranzactie(&v, "intrare", "ceva", 5, 67);
	assert(successful1 == 1);

	int successful3 = addTranzactie(&v, "intrare", "plata", 6, 888);
	assert(successful3 == 1);


	MyList* sortedList = sortTranzactiiBySuma(&v);
	Tranzactie* t0 = get(sortedList, 0);
	Tranzactie* t1 = get(sortedList, 1);
	Tranzactie* t2 = get(sortedList, 2);

	assert(t0->suma == 67);
	assert(t1->suma == 78);
	assert(t2->suma == 888);

	destroyList(sortedList);
	destroyTranzactiiStore(&v);
}

void testSortareZiua()
{
	TranzactiiStore v = createTranzactiiStore();
	int successful2 = addTranzactie(&v, "iesire", "plata", 5, 78);
	assert(successful2 == 1);

	int successful1 = addTranzactie(&v, "intrare", "ceva", 4, 67.6);
	assert(successful1 == 1);

	int successful3 = addTranzactie(&v, "intrare", "plata", 6, 888);
	assert(successful3 == 1);


	MyList* sortedList = sortTranzactiiByZiua(&v);
	Tranzactie* t0 = get(sortedList, 0);
	Tranzactie* t1 = get(sortedList, 1);
	Tranzactie* t2 = get(sortedList, 2);

	assert(t0->ziua == 4);
	assert(t1->ziua == 5);
	assert(t2->ziua == 6);

	destroyList(sortedList);
	destroyTranzactiiStore(&v);
}
