#pragma once
#include "tranzactie.h"

typedef void* ElemType;

typedef void (*DestroyFct)(ElemType);
typedef ElemType(*CopyFct)(ElemType);

typedef struct {
	ElemType* elems;
	int length;
	int capacitate;
	DestroyFct dfnc;
} MyList;

MyList* createEmpty(DestroyFct f);

void destroyList(MyList* v);

ElemType get(MyList* v, int poz);

ElemType setElem(MyList* v, int poz, ElemType el);

int size(MyList* v);

void add(MyList* v, ElemType el);

ElemType delete(MyList* v, int poz);

void testCreateVector();

void testIterate();

MyList* copyList(MyList* v, CopyFct copyFct);

void testCopy();