#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "module1.h"

struct cf *insert(struct cf **CF, int sn, struct fulldate START, struct fulldate END, int flights, int flytime){
	if (CF == NULL) return NULL;
	while ((*CF) != NULL) CF = &((*CF)->NEXT);
	(*CF) = malloc(sizeof(struct cf));
	(*CF)->SN = sn;
	(*CF)->FLIGHTS = flights;
	(*CF)->START = START;
	(*CF)->END = END;
	(*CF)->TIME = fulldate(START, END, NULL);
	(*CF)->FLYTIME = flytime;
	(*CF)->WORKDAYS = 0;
	(*CF)->CAPTAIN = 0;
	(*CF)->NEXT = NULL;
}

struct cf *set(struct flight *F, struct fulldate TO, int cfl, int *scf, int *fscf, double *IFT, int n){
	int i = 0, flights = 0, t = 0, flag = 1, flytime = 0;
	struct fulldate FLY, START, END;
	struct cf *CF = NULL;

	for (i = 0; i < cfl; i++){
		flights++;

		FLY.DAY = F[i].START.DAY;
		FLY.MONTH = F[i].START.MONTH;
		FLY.YEAR = F[i].START.YEAR;
		FLY.HOUR = F[i].START.HOUR;
		FLY.MINUTE = F[i].START.MINUTE;

		END.DAY = F[i].END.DAY;
		END.MONTH = F[i].END.MONTH;
		END.YEAR = F[i].END.YEAR;
		END.HOUR = F[i].END.HOUR;
		END.MINUTE = F[i].END.MINUTE;

		if (t != F[i].CF){
			flytime = 0;
			flights = 1;
			t = F[i].CF;
			START.DAY = F[i].START.DAY;
			START.MONTH = F[i].START.MONTH;
			START.YEAR = F[i].START.YEAR;
			START.HOUR = F[i].START.HOUR;
			START.MINUTE = F[i].START.MINUTE;
		}

		flytime += fulldate(FLY, END, NULL);
		if (F[i].CF != F[i + 1].CF){
			if (fulldate(START, TO, NULL) >= 0){
				(*scf)++;
				(*fscf) += flights;
				(*IFT) += flytime;

				insert(&CF, F[i].CF, START, END, flights, flytime);

				flytime = 0;
				flights = 0;
			}
		}
	}
	free(F);
	return CF;
}
