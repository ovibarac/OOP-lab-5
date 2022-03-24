#pragma once
#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

MyList* createEmpty(DestroyFct f) {
	MyList* v = malloc(sizeof(MyList));
	v->capacitate = 2;
	v->length = 0;
	v->elems = malloc(sizeof(ElemType) * v->capacitate);
	v->dfnc = f;
	return v;
}

void destroyList(MyList* v) {
	for (int i = 0; i < v->length; i++) {
		v->dfnc(v->elems[i]);
	}
	v->length = 0;
	free(v->elems);
	free(v);
}

ElemType get(MyList* v, int poz) {
	return v->elems[poz];
}

ElemType setElem(MyList* v, int poz, ElemType el) {
	ElemType replacedElement = v->elems[poz];
	v->elems[poz] = el;
	return replacedElement;
}

int size(MyList* v) {
	return v->length;
}

void add(MyList* v, ElemType el) {
	if (v->length >= v->capacitate) {
		int newCapacitate = v->capacitate * 2;
		ElemType* aux_elems = malloc(sizeof(ElemType) * newCapacitate);
		for (int i = 0; i < v->length; i++) {
			aux_elems[i] = v->elems[i];
		}
		free(v->elems);
		v->elems = aux_elems;
		v->capacitate = newCapacitate;
	}

	v->elems[v->length] = el;
	v->length++;
}

ElemType delete(MyList* v, int poz) {
	ElemType el = v->elems[poz];
	for (int i = poz; i < v->length - 1; i++) {
		v->elems[i] = v->elems[i + 1];
	}
	v->length--;
	return el;
}

/*
Remove last element from the list
!!!! do not destroy removed element
return the removed element
*/
ElemType removeLast(MyList* l) {
    ElemType rez = l->elems[l->length - 1];
    l->length -= 1;
    return rez;
}

MyList* copyList(MyList* v, CopyFct copyFct) {
	MyList* v_copy = createEmpty(v->dfnc);
	for (int i = 0; i < v->length; i++) {
		ElemType el = get(v, i);
		add(v_copy, copyFct(el));
	}
	return v_copy;
}

void testCreateVector() {
	MyList* v = createEmpty(destroyTranzactie);
	assert(size(v) == 0);
	destroyList(v);
}

void testIterate() {
	MyList* v = createEmpty(destroyTranzactie);
	Tranzactie* t1 = createTranzactie(17, 7575, "iesire", "hfeufh");
	Tranzactie* t2 = createTranzactie(18, 755, "intrare", "hfcfrh");
	Tranzactie* t3 = createTranzactie(19, 898, "iesire", "hfeufh");

	add(v, t1);
	add(v, t2);
	add(v, t3);

	assert(size(v) == 3);
	Tranzactie* t = get(v, 0);

	assert(strcmp(t->tip, "iesire") == 0);
	assert(strcmp(t->descriere, "hfeufh") == 0);
	assert(t->ziua == 17);
	assert(t->suma == 7575);

	destroyList(v);

}

void testCopy() {
	MyList* v1 = createEmpty(destroyTranzactie);
	add(v1, createTranzactie(17, 7575, "iesire", "hfeufh"));
	add(v1, createTranzactie(18, 755, "intrare", "hfcfrh"));

	assert(size(v1) == 2);
	MyList* v2 = copyList(v1, copyTranzactie);
	assert(size(v2) == 2);
	Tranzactie* t = get(v2, 0);
	assert(strcmp(t->descriere, "hfeufh") == 0);
	destroyList(v1);
	destroyList(v2);
}