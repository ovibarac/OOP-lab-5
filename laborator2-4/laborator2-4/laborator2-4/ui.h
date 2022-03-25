#pragma once
#include "service.h"

void testAll();

void printTranzactii(MyList* v);

void printMenu();

void uiAdd(TranzactiiStore* v);

void uiModify(TranzactiiStore* v);

void uiDelete(TranzactiiStore* v);

void uiFilter(TranzactiiStore* v);

void uiSortBySuma(TranzactiiStore* store);

void uiSortByZiua(TranzactiiStore* store);

void uiSoldZi(TranzactiiStore* store);

void run();

