
#include "SYSTAT.h"
#include "SYSTAT_CPUINFO.h"
#include "SYSTAT_RAMINFO.h"
#include "SYSTAT_PROCESSES.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define threadCount 2

struct threadData{
	struct SYSTAT_SYSTEM * sys;
	void (*func) (struct SYSTAT_SYSTEM * sys);
};

struct SYSTAT_SYSTEM * SYSTAT_INI ();
void SYSTAT_UPDATE(struct SYSTAT_SYSTEM * sys);
pthread_t SYSTAT_LOOP_ASYNC(struct SYSTAT_SYSTEM * sys);
void SYSTAT_LOOP_START(struct SYSTAT_SYSTEM *sys);
void SYSTAT_LOOP_FILE(struct SYSTAT_SYSTEM *sys);

struct SYSTAT_SYSTEM * new_SYSTAT_SYSTEM(){
	struct SYSTAT_SYSTEM * p;
	p = calloc (1, sizeof(struct SYSTAT_SYSTEM));
	p->CPUINFO.PROCESSORS = NULL;
}

struct SYSTAT_SYSTEM * SYSTAT_INI (){
	struct SYSTAT_SYSTEM * p = new_SYSTAT_SYSTEM();
	ramInfoIntialise();
	cpuInfoInitialise();

	return p;
}

void SYSTAT_UPDATE(struct SYSTAT_SYSTEM * sys){


	cpuInfoUpdate(&sys->CPUINFO);
	ramInfoUpdate(&sys->MEMINFO);
	processesUpdate(sys);
	return;

}
