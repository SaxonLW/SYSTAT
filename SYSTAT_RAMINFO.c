#include "stringTree.h"
#include "SYSTAT_RAMINFO_FUNC_LIST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * MEMINFO;

static void cat(FILE *fp)
{
    char   buffer[4096];
    size_t nbytes;
    while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), fp)) != 0)
         fwrite(buffer, sizeof(char), nbytes, stdout);
}

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

unsigned int lineCount (FILE * file){
	unsigned int lineCount = 0;
	char ch = 0;

	do{
		ch = fgetc(file);
		if(ch == '\n'){
			lineCount++;
		}
	}while(ch != EOF);

	if (ch != '\n' && lineCount){
		lineCount++;
	}

	return lineCount;
}

void determineValue (char * name, unsigned long long val, struct SYSTAT_SYSTEM * sys){
	int i = 0;

	sNode*  p = getHead();

	void (*funcMask) (struct SYSTAT_SYSTEM *, unsigned long long);

	while(name[i] != ':'){
		fflush(stdout);
		if(p->links[name[i]] == NULL){
			p=p->links[name[i]];
			break;
		}
		else{
			p=p->links[name[i]];
		}
		i++;
	}

	if(p->func == NULL){
		return;
	}

	funcMask = p->func;
	funcMask(sys, val);

	return;
}

void ramInfoUpdate(struct SYSTAT_SYSTEM * sys){
	MEMINFO = fopen("/proc/meminfo", "r");
	printf("\nRAM\n");

	char name [64];
	char excess [16];
	unsigned long long val;
	int args;

	while(args = fscanf(MEMINFO, "%s %llu %s\n", name, &val, excess)){
		if(args == 3){
			determineValue(name, val, sys);
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

void update_MemTotal       (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_MemTotal = val;
	return;
}
void update_MemFree        (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_MemFree = val;
	return;
}
void update_MemAvailable   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_MemAvailable = val;
	return;
}
void update_Buffers        (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Buffers = val;
	return;
}
void update_Cached         (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Cached = val;
	return;
}
void update_SwapCached     (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_SwapCached= val;
	return;
}
void update_Active         (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Active = val;
	return;
}
void update_Inactive       (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Inactive = val;
	return;
}
void update_Active_anon   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Active_anon = val;
	return;
}
void update_Inactive_anon (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Inactive_anon = val;
	return;
}
void update_Active_file   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Active_file = val;
	return;
}
void update_Inactive_file (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Inactive_file= val;
	return;
}
void update_Unevictable    (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Unevictable = val;
	return;
}
void update_Mlocked        (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Mlocked = val;
	return;
}
void update_HighTotal      (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_HighTotal = val;
	return;
}
void update_HighFree       (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_HighFree = val;
	return;
}
void update_LowTotal       (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_LowTotal = val;
	return;
}
void update_LowFree        (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_LowFree = val;
	return;
}
void update_SwapTotal      (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_SwapTotal = val;
	return;
}
void update_SwapFree       (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_SwapFree = val;
	return;
}
void update_Dirty          (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Dirty = val;
	return;
}
void update_Writeback      (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Writeback = val;
	return;
}
void update_AnonPages      (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_AnonPages = val;
	return;
}
void update_Mapped         (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Mapped = val;
	return;
}
void update_Shmem          (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Shmem = val;
	return;
}
void update_Slab           (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Slab = val;
	return;
}
void update_SReclaimable   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_SReclaimable = val;
	return;
}
void update_SUnreclaim     (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_SUnreclaim = val;
	return;
}
void update_KernelStack    (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_KernelStack = val;
	return;
}
void update_PageTables     (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_PageTables = val;
	return;
}
void update_NFS_Unstable   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_NFS_Unstable = val;
	return;
}
void update_Bounce         (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Bounce = val;
	return;
}
void update_WritebackTmp   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_WritebackTmp = val;
	return;
}
void update_CommitLimit    (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_CommitLimit = val;
	return;
}
void update_Committed_AS   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Committed_AS = val;
	return;
}
void update_VmallocTotal   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_VmallocTotal = val;
	return;
}
void update_VmallocUsed    (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_VmallocUsed = val;
	return;
}
void update_VmallocChunk   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_VmallocChunk = val;
	return;
}
void update_AnonHugePages  (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_AnonHugePages = val;
	return;
}
void update_CmaTotal       (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_CmaTotal = val;
	return;
}
void update_CmaFree        (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_CmaFree = val;
	return;
}
void update_HugePages_Total(struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_HugePages_Total = val;
	return;
}
void update_HugePages_Free (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_HugePages_Free = val;
	return;
}
void update_HugePages_Rsvd (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_HugePages_Rsvd= val;
	return;
}
void update_HugePages_Surp (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_HugePages_Surp = val;
	return;
}
void update_Hugepagesize   (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_Hugepagesize = val;
	return;
}
void update_DirectMap4k    (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_DirectMap4k = val;
	return;
}
void update_DirectMap2M    (struct SYSTAT_SYSTEM * sys, unsigned long long val){
	sys->MEM_INFO_DirectMap2M = val;
	return;
}
