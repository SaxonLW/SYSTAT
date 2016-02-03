#include "stringTree.h"
#include "SYSTAT_RAMINFO_FUNC_LIST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void ramInfoIntialise(){

	int i;

	stringPack keys [48];

	newStringPack(&keys[0],"MemTotal",update_MemTotal,8        );
	newStringPack(&keys[1],"MemFree",update_MemFree,7         );
	newStringPack(&keys[2],"MemAvailable",update_MemAvailable,12   );
	newStringPack(&keys[3],"Buffers",update_Buffers,7         );
	newStringPack(&keys[4],"Cached",update_Cached,6          );
	newStringPack(&keys[5],"SwapCached",update_SwapCached,10     );
	newStringPack(&keys[6],"Active",update_Active,6          );
	newStringPack(&keys[7],"Inactive",update_Inactive,8        );
	newStringPack(&keys[8],"Active(anon)",update_Active_anon,12   );
	newStringPack(&keys[9],"Inactive(anon)",update_Inactive_anon,14 );
	newStringPack(&keys[10],"Active(file)",update_Active_file,12   );
	newStringPack(&keys[11],"Inactive(file)",update_Inactive_file,14 );
	newStringPack(&keys[12],"Unevictable",update_Unevictable,11    );
	newStringPack(&keys[13],"Mlocked",update_Mlocked,7         );
	newStringPack(&keys[14],"HighTotal",update_HighTotal,9       );
	newStringPack(&keys[15],"HighFree",update_HighFree,8        );
	newStringPack(&keys[16],"LowTotal",update_LowTotal,8        );
	newStringPack(&keys[17],"LowFree",update_LowFree,7         );
	newStringPack(&keys[18],"SwapTotal",update_SwapTotal,9       );
	newStringPack(&keys[19],"SwapFree",update_SwapFree,8        );
	newStringPack(&keys[20],"Dirty",update_Dirty,5           );
	newStringPack(&keys[21],"Writeback",update_Writeback,9       );
	newStringPack(&keys[22],"AnonPages",update_AnonPages,9       );
	newStringPack(&keys[23],"Mapped",update_Mapped,6          );
	newStringPack(&keys[24],"Shmem",update_Shmem,5           );
	newStringPack(&keys[25],"Slab",update_Slab,4            );
	newStringPack(&keys[26],"SReclaimable",update_SReclaimable,12   );
	newStringPack(&keys[27],"SUnreclaim",update_SUnreclaim,10     );
	newStringPack(&keys[28],"KernelStack",update_KernelStack,11    );
	newStringPack(&keys[29],"PageTables",update_PageTables,10     );
	newStringPack(&keys[30],"NFS_Unstable",update_NFS_Unstable,12   );
	newStringPack(&keys[31],"Bounce",update_Bounce,6          );
	newStringPack(&keys[32],"WritebackTmp",update_WritebackTmp,12   );
	newStringPack(&keys[33],"CommitLimit",update_CommitLimit,11    );
	newStringPack(&keys[34],"Committed_AS",update_Committed_AS,12   );
	newStringPack(&keys[35],"VmallocTotal",update_VmallocTotal,12   );
	newStringPack(&keys[36],"VmallocUsed",update_VmallocUsed,11    );
	newStringPack(&keys[37],"VmallocChunk",update_VmallocChunk,12   );
	newStringPack(&keys[38],"AnonHugePages",update_AnonHugePages,13  );
	newStringPack(&keys[39],"CmaTotal",update_CmaTotal,8        );
	newStringPack(&keys[40],"CmaFree",update_CmaFree,7         );
	newStringPack(&keys[41],"HugePages_Total",update_HugePages_Total,15);
	newStringPack(&keys[42],"HugePages_Free",update_HugePages_Free,14 );
	newStringPack(&keys[43],"HugePages_Rsvd",update_HugePages_Rsvd,14 );
	newStringPack(&keys[44],"HugePages_Surp",update_HugePages_Surp,14 );
	newStringPack(&keys[45],"Hugepagesize",update_Hugepagesize,12   );
	newStringPack(&keys[46],"DirectMap4k",update_DirectMap4k,11    );
	newStringPack(&keys[47],"DirectMap2M",update_DirectMap2M,11    );


	for (i = 0; i < 48; i++){
		addString(keys[i]);
	}

	//traverseTree(getHead(),0);

}

void determineValueRAM (char * name, unsigned long long val, struct SYSTAT_MEMINFO * sys){
	int i = 0;

	sNode*  p = getHead();

	void (*funcMask) (struct SYSTAT_MEMINFO *, unsigned long long);


	/*
	 * About this traversal
	 * p is assigned NULL in the loop to prevent the wrong function being called
	 * This can happen when two words are similar except for their last letter,
	 * and the null is not assigned the wrong function can occur
	 * Future proofing
	 */
	while(name[i] != ':'){

		if(p->links[name[i]] == NULL){
			p=p->links[name[i]];
			break;
		}
		else{
			p=p->links[name[i]];
		}
		i++;
	}

	if(p->func == NULL || p == NULL){
		return;
	}

	funcMask = p->func;
	funcMask(sys, val);

	return;
}

void ramInfoUpdate(struct SYSTAT_MEMINFO * sys){

	FILE * MEMINFO;

	MEMINFO = fopen("/proc/meminfo", "r");

	char name [64];
	char excess [16];
	unsigned long long val;
	int args;

	while(args = fscanf(MEMINFO, "%s %llu %s\n", name, &val, excess)){
		if(args == 3){
			determineValueRAM(name, val, sys);
		}
		if(args == -1){
			break;
		}
		else{
			continue;
		}
	}

	fclose(MEMINFO);

	return;

}

void ramInfoUpdateThread(struct SYSTAT_MEMINFO * sys){
	ramInfoUpdate(sys);
	pthread_exit(NULL);
}

void update_MemTotal       (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->MemTotal = val;
	return;
}
void update_MemFree        (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->MemFree = val;
	return;
}
void update_MemAvailable   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->MemAvailable = val;
	return;
}
void update_Buffers        (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Buffers = val;
	return;
}
void update_Cached         (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Cached = val;
	return;
}
void update_SwapCached     (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->SwapCached= val;
	return;
}
void update_Active         (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Active = val;
	return;
}
void update_Inactive       (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Inactive = val;
	return;
}
void update_Active_anon   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Active_anon = val;
	return;
}
void update_Inactive_anon (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Inactive_anon = val;
	return;
}
void update_Active_file   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Active_file = val;
	return;
}
void update_Inactive_file (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Inactive_file= val;
	return;
}
void update_Unevictable    (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Unevictable = val;
	return;
}
void update_Mlocked        (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Mlocked = val;
	return;
}
void update_HighTotal      (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->HighTotal = val;
	return;
}
void update_HighFree       (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->HighFree = val;
	return;
}
void update_LowTotal       (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->LowTotal = val;
	return;
}
void update_LowFree        (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->LowFree = val;
	return;
}
void update_SwapTotal      (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->SwapTotal = val;
	return;
}
void update_SwapFree       (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->SwapFree = val;
	return;
}
void update_Dirty          (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Dirty = val;
	return;
}
void update_Writeback      (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Writeback = val;
	return;
}
void update_AnonPages      (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->AnonPages = val;
	return;
}
void update_Mapped         (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Mapped = val;
	return;
}
void update_Shmem          (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Shmem = val;
	return;
}
void update_Slab           (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Slab = val;
	return;
}
void update_SReclaimable   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->SReclaimable = val;
	return;
}
void update_SUnreclaim     (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->SUnreclaim = val;
	return;
}
void update_KernelStack    (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->KernelStack = val;
	return;
}
void update_PageTables     (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->PageTables = val;
	return;
}
void update_NFS_Unstable   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->NFS_Unstable = val;
	return;
}
void update_Bounce         (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Bounce = val;
	return;
}
void update_WritebackTmp   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->WritebackTmp = val;
	return;
}
void update_CommitLimit    (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->CommitLimit = val;
	return;
}
void update_Committed_AS   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Committed_AS = val;
	return;
}
void update_VmallocTotal   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->VmallocTotal = val;
	return;
}
void update_VmallocUsed    (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->VmallocUsed = val;
	return;
}
void update_VmallocChunk   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->VmallocChunk = val;
	return;
}
void update_AnonHugePages  (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->AnonHugePages = val;
	return;
}
void update_CmaTotal       (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->CmaTotal = val;
	return;
}
void update_CmaFree        (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->CmaFree = val;
	return;
}
void update_HugePages_Total(struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->HugePages_Total = val;
	return;
}
void update_HugePages_Free (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->HugePages_Free = val;
	return;
}
void update_HugePages_Rsvd (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->HugePages_Rsvd= val;
	return;
}
void update_HugePages_Surp (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->HugePages_Surp = val;
	return;
}
void update_Hugepagesize   (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->Hugepagesize = val;
	return;
}
void update_DirectMap4k    (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->DirectMap4k = val;
	return;
}
void update_DirectMap2M    (struct SYSTAT_MEMINFO * sys, unsigned long long val){
	sys->DirectMap2M = val;
	return;
}
