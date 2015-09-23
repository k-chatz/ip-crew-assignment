#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "module1.h"

int fulldate(struct fulldate START, struct fulldate END, int *days){
	int m[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, i, y = 0, flag = 0, temp;
	if (days == NULL)
		days = malloc(sizeof(int));
	*days = 0;
	temp = START.DAY;
	i = START.MONTH;
	while (i < END.MONTH + ((END.YEAR - START.YEAR) * 12)){
		if (i > 12){
			i = 1;
			START.YEAR++;
		}

		if (i == 2){
			if (START.YEAR % 4 == 0 && (START.YEAR % 100 != 0 || START.YEAR % 400 == 0))
				m[i - 1] = 29;
			else
				m[i - 1] = 28;
		}

		*days = (*days) + (m[i - 1] - temp);
		temp = 0;
		i++;
	}

	(*days) += (END.DAY - temp);

	if (START.HOUR != 0)
		flag = 1;
	if (START.MINUTE != 0)
		flag = 1;

	START.MINUTE = 1440 - (START.MINUTE + (START.HOUR * 60));
	END.MINUTE = END.MINUTE + (END.HOUR * 60);

	if (i == START.MONTH && ((START.MONTH > END.MONTH) || (START.YEAR > END.YEAR))){
		y = -1;
		*days = 0;
	}
	else{
		if ((((((*days) - 1) * 24) * 60) + (END.MINUTE + START.MINUTE)) >= 0){
			y = (((((*days) - 1) * 24) * 60) + (END.MINUTE + START.MINUTE));
			if (flag)
				(*days)--;
		}
		else{
			y = -1;
			*days = 0;
		}
	}

	return y;
}
