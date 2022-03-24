#pragma once
#include "customSort.h"


void sort(MyList* v, CompareFct cmpF) {
	int i, j;
	for (i = 0; i < size(v); i++) {
		for (j = i + 1; j < size(v); j++) {
			void* p1 = get(v, i);
			void* p2 = get(v, j);
			if (cmpF(p1, p2) > 0) {
				setElem(v, i, p2);
				setElem(v, j, p1);
			}
		}
	}
}