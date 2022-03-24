#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "utils.h"

void generate(TranzactiiStore* v){
    addTranzactie(v, "intrare", "abc", 1, 12);
    addTranzactie(v, "intrare", "Mancare", 4, 10);
    addTranzactie(v, "intrare", "Taxe", 6, 2);
    addTranzactie(v, "iesire", "Impozit", 3, 45);
    addTranzactie(v, "iesire", "Transfer", 1, 13);
    addTranzactie(v, "iesire", "abc", 1, 13);
    addTranzactie(v, "intrare", "abc", 1, 54);
}

void testAll() {
	testCreateDestroy();
	testValideaza();
	testCreateVector();
	testIterate();
	testAddService();
	testModifyService();
	testDeleteService();
	testFindService();
	testFilterService();
	testCopy();
	testCopyTranzactie();
	testSortareSuma();
	testSortareZiua();
}

void printTranzactii(MyList* v) {
	if (v->length == 0)
		printf("Nu exista tranzactii.\n");
	else
	{
		printf("tranzactiile curente sunt:\n");
		for (int i = 0; i < size(v); i++) {
			Tranzactie* t = get(v, i);
			printf("Ziua: %d | Suma: %f | Tipul: %s | Descriere: %s\n", t->ziua, t->suma, t->tip, t->descriere);
		};
	};
}

void printMenu() {
	printf("1. Adauga tranzactie\n");
	printf("2. Actualizare tranzactie\n");
	printf("3. Sterge tranzactie\n");
	printf("4. Afiseaza toate tranzactiile\n");
	printf("5. Filarare lista\n");
	printf("6. Sortare tranzactii dupa suma\n");
	printf("7. Sortare tranzactii dupa zi\n");
	printf("8. Undo\n");
	printf("0. Iesire\n");
}

void uiAdd(TranzactiiStore* v) {
	char tip[10], descriere[100];
	int ziua;
	float suma;
	char temp;
	printf("Ziua: ");
	scanf_s("%d", &ziua);
	printf("Suma: ");
	scanf_s("%f", &suma);
	scanf_s("%c", &temp, 1);
	printf("Tipul: ");
	fgets(tip, 10, stdin);
	printf("Descriere: ");
	fgets(descriere, 100, stdin);

	trimTrailing(tip);
	trimTrailing(descriere);
	

	int successful = addTranzactie(v, tip, descriere, ziua, suma);
	if (successful)
		printf("Tranzactie adaugata cu succes.\n");
	else
		printf("Tranzactie invalida.\n");

}

void uiModify(TranzactiiStore* v) {
	char tip[10], descriere[100];
	int ziua;
	float suma;
	char temp;
	printf("Ziua:");
	scanf_s("%d", &ziua);
	printf("Suma:");
	scanf_s("%f", &suma);
	scanf_s("%c", &temp, 1);
	printf("Tipul:");
	fgets(tip, 10, stdin);
	printf("Descriere:");
	fgets(descriere, 100, stdin);

	trimTrailing(tip);
	trimTrailing(descriere);

	int successful = modifyTranzactie(v, ziua, suma, tip, descriere);
	if (successful)
		printf("Tranzactia modificata cu succes.\n");
	else
		printf("Nu exista tranzactie cu datele introduse.\n");
}

void uiDelete(TranzactiiStore* v) {
	char tip[10], descriere[100];
	int ziua;
	float suma;
	char temp;
	printf("ziua:");
	scanf_s("%d", &ziua);
	printf("Suma:");
	scanf_s("%f", &suma);
	printf("Tipul:");
	scanf_s("%c", &temp, 1);
	fgets(tip, 10, stdin);
	printf("Descriere:");
	fgets(descriere, 100, stdin);

	trimTrailing(tip);
	trimTrailing(descriere);

	int successful = deleteTranzactie(v, tip, descriere, ziua, suma);
	if (successful)
		printf("Tranzactie stearsa cu succes.\n");
	else
		printf("Nu exista traznactie cu datele date.\n");
}

void uiFilter(TranzactiiStore* v) {
	printf("1. Filtrare dupa tip\n");
	printf("2. filtrare dupa suma\n");
	printf("3. filtrare dupa zi\n");
	int cmd;
	printf("Introduceti numarul comenzii: ");
	scanf_s("%d", &cmd);
	if (cmd == 1)
	{
		char tip[10];
		char temp;
		scanf_s("%c", &temp, 1);
		printf("Tipul tranzactiei este:");
		fgets(tip, 10, stdin);
		trimTrailing(tip);
		if (strcmp(tip, "") == 0)
			printf("date invalide");
		else
		{
          MyList* filteredList = filterTranzactiitip(v, tip);
		  printTranzactii(filteredList);
		  destroyList(filteredList);
		}
		
	}
	if (cmd == 2)
	{
		printf("1. suma mai mica\n");
		printf("2. suma mai mare\n");
		printf("Introduceti numarul comenzii: ");
		int cmds;
		scanf_s("%d", &cmds);
		float suma;
		printf("Itroduceti suma: ");
		scanf_s("%f", &suma);
		if (cmds == 1 && suma !=0)
		{
			MyList* filteredList = filterTranzactiiSumaMaiMica(v, suma);
			printTranzactii(filteredList);
			destroyList(filteredList);
		}
		if (cmds == 2 && suma!=0)
		{
			MyList* filteredList = filterTranzactiiSumaMaiMare(v, suma);
			printTranzactii(filteredList);
			destroyList(filteredList);
		}
		if (suma == 0)
			printf("date invalide");
	}
    if (cmd == 3)
    {
        int zi;
        printf("Itroduceti ziua: ");
        scanf_s("%d", &zi);
        if (zi !=0)
        {
            MyList* filteredList = filterTranzactiiZi(v, zi);
            printTranzactii(filteredList);
            destroyList(filteredList);
        }
        if (zi  < 1 || zi > 31)
            printf("date invalide");
    }

}

void uiSortBySuma(TranzactiiStore* store) {

	MyList* sortedList = sortTranzactiiBySuma(store);
	printTranzactii(sortedList);
	destroyList(sortedList);

}

void uiSortByZiua(TranzactiiStore* store) {

	MyList* sortedList = sortTranzactiiByZiua(store);
	printTranzactii(sortedList);
	destroyList(sortedList);

}

void run() {
	TranzactiiStore List = createTranzactiiStore();
	int running = 1;
    generate(&List);
	while (running) {
		printMenu();
		int cmd;
		printf("Comanda este:");
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			uiAdd(&List);
			break;
		case 2:
			uiModify(&List);
			break;
		case 3:
			uiDelete(&List);
			break;
		case 4:
			printTranzactii(List.allTranzactii);
			break;
		case 5:
			uiFilter(&List);
			break;
		case 6:
			uiSortBySuma(&List);
			//printTranzactii(&List);
			break;
		case 7:
			uiSortByZiua(&List);
			break;
        case 8:
            if (undo(&List) != 0) {
                printf("No more undo!!!\n");
            }
            break;

		case 0:
			running = 0;
			destroyTranzactiiStore(&List);
			break;
		default:
			printf("Comanda invalida!\n");

		}
	}
}
