#include <stdio.h>
#include <stdlib.h>
#include "SYSTAT.h"
#include <time.h>
#include <ncurses.h>
#include <pthread.h>

clock_t start;
clock_t updateT;

void update(struct SYSTAT_SYSTEM * sys){



	while (1){
		updateT = clock();
		SYSTAT_UPDATE(sys);
		updateT = clock() - updateT;
	}
}


void outputMEMINFO(struct SYSTAT_MEMINFO sys){
	printw("MemTotal:\t%llu\n",sys.MemTotal);
	printw("MemFree:\t%llu\n",sys.MemFree);
	printw("MemAvailable:\t%llu\n",sys.MemAvailable);
	printw("Buffers:\t%llu\n",sys.Buffers);
	printw("Cached:\t%llu\n",sys.Cached);
	printw("SwapCached:\t%llu\n",sys.SwapCached);
	printw("Active:\t%llu\n",sys.Active);
	printw("Inactive:\t%llu\n",sys.Inactive);
	printw("Active_anon:\t%llu\n",sys.Active_anon);
	printw("Inactive_anon:\t%llu\n",sys.Inactive_anon);
	printw("Active_file:\t%llu\n",sys.Active_file);
	printw("Inactive_file:\t%llu\n",sys.Inactive_file);
	printw("Unevictable:\t%llu\n",sys.Unevictable);
	printw("Mlocked:\t%llu\n",sys.Mlocked);
	printw("HighTotal:\t%llu\n",sys.HighTotal);
	printw("HighFree:\t%llu\n",sys.HighFree);
	printw("LowTotal:\t%llu\n",sys.LowTotal);
	printw("LowFree:\t%llu\n",sys.LowFree);
	printw("SwapTotal:\t%llu\n",sys.SwapTotal);
	printw("SwapFree:\t%llu\n",sys.SwapFree);
	printw("Dirty:\t%llu\n",sys.Dirty);
	printw("Writeback:\t%llu\n",sys.Writeback);
	printw("AnonPages:\t%llu\n",sys.AnonPages);
	printw("Mapped:\t%llu\n",sys.Mapped);
	printw("Shmem:\t%llu\n",sys.Shmem);
	printw("Slab:\t%llu\n",sys.Slab);
	printw("SReclaimable:\t%llu\n",sys.SReclaimable);
	printw("SUnreclaim:\t%llu\n",sys.SUnreclaim);
	printw("KernelStack:\t%llu\n",sys.KernelStack);
	printw("PageTables:\t%llu\n",sys.PageTables);
	printw("NFS_Unstable:\t%llu\n",sys.NFS_Unstable);
	printw("Bounce:\t%llu\n",sys.Bounce);
	printw("WritebackTmp:\t%llu\n",sys.WritebackTmp);
	printw("CommitLimit:\t%llu\n",sys.CommitLimit);
	printw("Committed_AS:\t%llu\n",sys.Committed_AS);
	printw("VmallocTotal:\t%llu\n",sys.VmallocTotal);
	printw("VmallocUsed:\t%llu\n",sys.VmallocUsed);
	printw("VmallocChunk:\t%llu\n",sys.VmallocChunk);
	printw("AnonHugePages:\t%llu\n",sys.AnonHugePages);
	printw("CmaTotal:\t%llu\n",sys.CmaTotal);
	printw("CmaFree:\t%llu\n",sys.CmaFree);
	printw("HugePages_Total:\t%llu\n",sys.HugePages_Total);
	printw("HugePages_Free:\t%llu\n",sys.HugePages_Free);
	printw("HugePages_Rsvd:\t%llu\n",sys.HugePages_Rsvd);
	printw("HugePages_Surp:\t%llu\n",sys.HugePages_Surp);
	printw("Hugepagesize:\t%llu\n",sys.Hugepagesize);
	printw("DirectMap4k:\t%llu\n",sys.DirectMap4k);
	printw("DirectMap2M:\t%llu\n",sys.DirectMap2M);
}

int main (void){

	struct SYSTAT_SYSTEM * sys = SYSTAT_INI();

	int state = 0;

	pthread_t t;

	//pthread_create(&t,NULL,update, sys);

	initscr();

	while(1){

		updateT = clock();
		SYSTAT_UPDATE(sys);
		updateT = clock() - updateT;


		start = clock();
		move(0,0);
		outputMEMINFO(sys->MEMINFO);
		start =clock() - start;

		printw("%li\t%li\n",start,updateT);
		refresh();
	}
	endwin();

	//time = clock() - time;

	//printf("%li\n", time);
}
