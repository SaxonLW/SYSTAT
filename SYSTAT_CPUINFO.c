#include "stringTree.h"
#include "SYSTAT.h"
#include <stdio.h>

FILE * CPUINFO;

void cpuInfoUpdate(struct SYSTAT_SYSTEM * sys){
	CPUINFO = fopen("/proc/cpuinfo", "r");
	printf("\nCPU\n");

	fclose(CPUINFO);
	return;
}
