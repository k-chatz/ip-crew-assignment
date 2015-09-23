#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "module1.h"

int days(struct fulldate S1, struct fulldate E1, struct fulldate E2);

struct cf *dense(struct cf *CF, struct fulldate *FINISH, int *t){
	struct cf *SELECTED = NULL;
	int flag = 0, min = -1;
	while (CF != NULL){
		if (CF->CAPTAIN == 0){
			if ((*t = fulldate(*FINISH, CF->START, NULL)) >= 660){
				if (*t < min || min == -1){
					flag++;
					min = *t;
					SELECTED = CF;
				}
			}
		}
		CF = CF->NEXT;
	}
	if (flag){
		*FINISH = SELECTED->END;
		return SELECTED;
	}
	else{
		return NULL;
	}
}

struct cf *award(struct cf *CF, int n, int *P, double *IFT, double *V){
	struct cf *TOP = CF, *CONTINUE = NULL;
	struct captain *CAPTAIN = NULL;
	struct fulldate FINISH, S1, E1, E2;
	int t = 0, i = 0, j = 0;

	CAPTAIN = malloc(n * sizeof(struct captain));

	for (i = 0; i < n; i++){
		struct cf *CFi = TOP;
		int flag = 1;

		CAPTAIN[i].ID = i + 1;
		CAPTAIN[i].FLYTIME = 0;

		FINISH.DAY = 1;
		FINISH.MONTH = 1;
		FINISH.YEAR = 2001;
		FINISH.HOUR = 0;
		FINISH.MINUTE = 0;

		CF = TOP;

		while ((CONTINUE = CF) != NULL){

			if ((CF = dense(CFi, &FINISH, &t)) != NULL){
				S1.DAY = CF->START.DAY;
				S1.MONTH = CF->START.MONTH;
				S1.YEAR = CF->START.YEAR;
				S1.HOUR = 0;
				S1.MINUTE = 0;

				E1.DAY = CF->END.DAY;
				E1.MONTH = CF->END.MONTH;
				E1.YEAR = CF->END.YEAR;
				E1.HOUR = 0;
				E1.MINUTE = 0;

				if (flag){
					E2 = S1;
					CAPTAIN[i].WORKDAYS = 1;
					flag = 0;
				}

				CAPTAIN[i].WORKDAYS += days(S1, E1, E2);

				if (CAPTAIN[i].WORKDAYS > 7){
					int D = 0;
					fulldate(E2, S1, &D);
					if (D > 2){
						CAPTAIN[i].WORKDAYS = days(S1, E1, E2);
					}
				}

				CF->WORKDAYS = CAPTAIN[i].WORKDAYS;
				if (CAPTAIN[i].WORKDAYS <= 5){
					CF->CAPTAIN = i + 1;
					CAPTAIN[i].FLYTIME += CF->FLYTIME;
					printf("%4.4d ", CF->SN);
					E2.DAY = CF->END.DAY;
					E2.MONTH = CF->END.MONTH;
					E2.YEAR = CF->END.YEAR;
					E2.HOUR = 0;
					E2.MINUTE = 0;
					(*P)++;
				}
			}
			CF = CONTINUE->NEXT;
		}
		putchar('\n');

		*V += (((double)(CAPTAIN[i].FLYTIME - *IFT)) * ((double)(CAPTAIN[i].FLYTIME - *IFT)));
	}
	free(CAPTAIN);
	return TOP;
}

int days(struct fulldate S1, struct fulldate E1, struct fulldate E2){
	int days = 0;
	if (fulldate(E2, S1, NULL) == 0){
		if (fulldate(S1, E1, &days) == 0)
			return 0;
		else
			return  days;
	}
	else{
		if (fulldate(S1, E1, &days) == 0)
			return 1;
		else
			return ++days;
	}
}
