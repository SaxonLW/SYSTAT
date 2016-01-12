
#include "SYSTAT.h"
#include "SYSTAT_CPUINFO.h"
#include "SYSTAT_RAMINFO.h"
#include <pthread.h>
#include <stdio.h>

#define threadCount 2

struct threadData{
	struct SYSTAT_SYSTEM * sys;
	void (*func) (struct SYSTAT_SYSTEM * sys);
};

int SYSTAT_INI (struct SYSTAT_SYSTEM * sys);
int SYSTAT_UPDATE(struct SYSTAT_SYSTEM * sys);
pthread_t SYSTAT_LOOP_ASYNC(struct SYSTAT_SYSTEM * sys);
void SYSTAT_LOOP_START(struct SYSTAT_SYSTEM *sys);
void SYSTAT_LOOP_FILE(struct SYSTAT_SYSTEM *sys);

int SYSTAT_INI (struct SYSTAT_SYSTEM * sys){

	ramInfoIntialise();

	return 0;
}

int SYSTAT_UPDATE(struct SYSTAT_SYSTEM * sys){
	struct SYSTAT_SYSTEM * val = sys;

	int i;

	pthread_t thread [threadCount];

	pthread_create(&thread[0],NULL, (void * (*)(void *)) ramInfoUpdate, &val);
	pthread_create(&thread[1],NULL, (void * (*)(void *)) cpuInfoUpdate, &val);

	for (i = 0; i < threadCount; i++){
		pthread_join(thread[i], NULL);
	}

	return 0;
}
