#include "unit.h"

void bacaunit(LIST *stdunit){
	int i;
	Unit Utemp;
	STARTKATA(true);
	while(!EOP){
		if(!IsSama(CKata, EndUnit){
			switch(i){
				case 1 : Utemp.type = CKata;
						 break;
				case 2 : Utemp.maxhealth = KatatoBilangan(CKata);
						 Utemp.currhealth = Utemp.maxhealth;
						 break;
				case 3 : Utemp.atkdmg = KatatoBilangan(CKata);
						 break;
				case 4 : Utemp.maxmove = KatatoBilangan(CKata);
						 Utemp.currmove = Utemp.maxmove;
						 break;
				case 5 : Utemp.atktype = CKata;
						 break;
				case 6 : Utemp.cost = KatatoBilangan(CKata);
						 break;
				case 7 : Utemp.heal = KatatoBilangan(CKata);
						 break;
			}
			i++;
		}
		else{
			Utemp.canatk = true;
			if(i<8)
				Utemp.heal = 0;
			i=1;
			Add(stdunit, Utemp);
		}
		ADVKATA(true);
	}
}

void PrintUnitRekrut(Unit U){
	PrintKata(U.type);
	printf(" | Health %d | ATK %d | DEF %d | %dG", U.maxhealth, U.atkdmg, U.cost);
}


void PrintMove(Unit U){
	PrintKata(U.type);
	TulisPOINT(U.pos);
	printf(" | Movement Point : %d | Can Attack : ", U.currmove);
	if(U.canatk)
		printf("YES");
	else
		printf("NO");
}

void PrintUnit(Unit U){
	PrintKata(U.type);
	printf(" ");
	TulisPOINT(U.pos);
	printf(" | Health %d", U.currhealth);
}
