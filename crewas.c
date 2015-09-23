#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "module1.h"
#include "module2.h"

int main(int argc, char *argv[]){
	int n = 0, i = 0, m = 0, hours = 0, minutes = 0, ccf = 0, cfl = 0, scf = 0, fscf = 0, days = 0, P = 0, vi = 0;
	char *p = NULL, *file = NULL;
	double IFT = 0, V = 0;
	struct fulldate START, END;
	struct cf *CF;
	START.YEAR = 2001;
	START.MONTH = 1;
	START.DAY = 1;
	START.HOUR = 0;
	START.MINUTE = 0;

	END.YEAR = 2020;
	END.MONTH = 12;
	END.DAY = 31;
	END.HOUR = 23;
	END.MINUTE = 59;

	for (i = 1; i < argc - 1; i++){
		if (strcmp(argv[i], "-p") == 0){
			file = argv[i + 1];
		}
		else if (strcmp(argv[i], "-n") == 0){
			n = atoi(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-s") == 0){
			p = argv[i + 1];
			START.YEAR = (atoi(p) >= 2001) ? atoi(p) : 2001;
			START.MONTH = (atoi(p + 5) >= 0 && atoi(p + 5) <= 12) ? atoi(p + 5) : 1;
			START.DAY = (atoi(p + 8) >= 0 && atoi(p + 8) <= 31) ? atoi(p + 8) : 1;
			START.HOUR = (atoi(p + 11) >= 0 && atoi(p + 11) <= 24) ? atoi(p + 11) : 0;
			START.MINUTE = (atoi(p + 14) >= 0 && atoi(p + 14) <= 59) ? atoi(p + 14) : 0;
		}
		else if (strcmp(argv[i], "-e") == 0){
			p = argv[i + 1];
			END.YEAR = (atoi(p) >= 0) ? atoi(p) : 1;
			END.MONTH = (atoi(p + 5) >= 0 && atoi(p + 5) <= 12) ? atoi(p + 5) : 1;
			END.DAY = (atoi(p + 8) >= 0 && atoi(p + 8) <= 31) ? atoi(p + 8) : 1;
			END.HOUR = (atoi(p + 11) >= 0 && atoi(p + 11) <= 24) ? atoi(p + 11) : 0;
			END.MINUTE = (atoi(p + 14) >= 0 && atoi(p + 14) <= 59) ? atoi(p + 14) : 0;
		}
		else if (strcmp(argv[i], "-r") == 0){

		}
		else if (strcmp(argv[i], "-i") == 0){
			vi = 1;
		}
		else if (strcmp(argv[i], "-v") == 0){

		}
	}

	struct flight *F;
	if ((F = read_file(file, &ccf, &cfl)) == NULL){
		if (file == NULL){
			printf("Error: No file at input!\n");
			return -1;
		}
		else{
			printf("Error: File '%s' does not exists!\n", file);
			return -1;
		}
	}
	else{
		CF = set(F, END, cfl, &scf, &fscf, &IFT, n);
		if (n > 0)
			IFT /= n;
		CF = award(CF, n, &P, &IFT, &V);
		if (vi)
			printf("V = %0.3f\n", V);
	}
	return 0;
}
