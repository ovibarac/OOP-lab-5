#ifndef  CUSTOMSORT_H_
#define CUSTOMSORT_H_

#include "lista.h"

/*
* Tipul de functie pentru compararea a doua elemente
* returneaza 0 daca sunt egale, 1 daca el1>el2, -1 altfel
*/
typedef int (*CompareFct)(void* el1, void* el2);
void sort(MyList* v, CompareFct cmpF);

#endif // ! CUSTOMSORT_H_