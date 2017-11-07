#ifndef _UNIT_H
#define _UNIT_H

#include "point.h"
#include "mesinkata.h"
#include "listsirkuler.h"

const Kata range("Range", 5);
const Kata melle("Melle", 5);
const Kata endunit("End", 3);

typedef struct{
	Kata type;
	Kata atktype;
	boolean canatk;
	int maxhealth;
	int currhealth;
	int atkdmg;
	int maxmove;
	int currmove;
	int heal;
	int cost;
	Point pos;
} Unit;

void bacaunit(LIST *stdunit);

void PrintUnitRekrut(Unit U);

void PrintMove(Unit U);

void PrintUnit(Unit U);

#endif
