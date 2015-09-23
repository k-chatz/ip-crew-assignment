#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "module1.h"

struct flight *read_file(char *file, int *cfs, int *cfl){
	FILE *stream;
	int  i = 0, r = 0, col = 0, line = 1, tmp = 0, flag = 0, f = 0;
	char current = ' ', *p;

	if ((p = malloc(11 * sizeof(char))) == NULL){
		puts("An error occurred when allocating memory!");
		return NULL;
	}

	if ((stream = fopen(file, "r")) == NULL){
		printf("An error occurred when opening file '%s'\n", file);
		return NULL;
	}

	while (!feof(stream)){
		current = fgetc(stream);
		if (current == '\n')
			(*cfl)++;
	}
	fclose(stream);

	struct flight *F;

	if ((F = malloc((*cfl) * sizeof(struct flight))) == NULL) return NULL;

	if ((stream = fopen(file, "r")) == NULL) return NULL;

	current = ' ';
	while (!feof(stream)){
		col++;
		current = fgetc(stream);
		if (col > 0 && col < 5){
			p[r] = current;
			r++;
		}
		else if (col > 5 && col < 9){
			p[r] = current;
			r++;
		}
		else if (col > 9 && col < 13){
			p[r] = current;
			r++;
		}
		else if (col > 13 && col < 17){
			p[r] = current;
			r++;
		}
		else if (col > 17 && col < 28){
			p[r] = current;
			r++;
		}
		else if (col > 28 && col < 34){
			p[r] = current;
			r++;
		}
		else if (col > 34 && col < 45){
			p[r] = current;
			r++;
		}
		else if (col > 45 && col < 51){
			p[r] = current;
			r++;
		}
		else{
			p[r] = '\0';
			if (col == 5){
				F[line - 1].CF = atoi(p);
				if (tmp != F[line - 1].CF) (*cfs)++;
				tmp = F[line - 1].CF;
			}
			else if (col == 9){
				F[line - 1].FLIGHT = atoi(p);
			}
			else if (col == 13){
				strcpy(F[line - 1].AIRDEP, p);
			}
			else if (col == 17){
				strcpy(F[line - 1].AIRARR, p);
			}
			else if (col == 28){
				F[line - 1].START.YEAR = atoi(p);
				F[line - 1].START.MONTH = atoi(p + 5);
				F[line - 1].START.DAY = atoi(p + 8);
			}
			else if (col == 34){
				F[line - 1].START.HOUR = atoi(p);
				F[line - 1].START.MINUTE = atoi(p + 3);
			}
			else if (col == 45){
				F[line - 1].END.YEAR = atoi(p);
				F[line - 1].END.MONTH = atoi(p + 5);
				F[line - 1].END.DAY = atoi(p + 8);
			}
			else if (col == 51){
				F[line - 1].END.HOUR = atoi(p);
				F[line - 1].END.MINUTE = atoi(p + 3);
			}
			r = 0;
		}

		if (current == '\n'){
			line++;
			col = 0;
		}
	}
	fclose(stream);

	return F;
}
