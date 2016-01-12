#include <stdio.h>
#include "SYSTAT.h"
#include <time.h>


int main (void){

	clock_t time = clock();

	struct SYSTAT_SYSTEM sys;
	SYSTAT_INI(&sys);
	SYSTAT_UPDATE(&sys);

	printf("\ndebug\n");
	fflush(stdout);

	time = clock() - time;

	printf("\n%li\n", time);
}
