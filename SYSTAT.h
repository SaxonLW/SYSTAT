#include <pthread.h>

struct SYSTAT_SYSTEM{
	unsigned long long MEM_INFO_MemTotal;
	unsigned long long MEM_INFO_MemFree;
	unsigned long long MEM_INFO_MemAvailable;
	unsigned long long MEM_INFO_Buffers;
	unsigned long long MEM_INFO_Cached;
	unsigned long long MEM_INFO_SwapCached;
	unsigned long long MEM_INFO_Active;
	unsigned long long MEM_INFO_Inactive;
	unsigned long long MEM_INFO_Active_anon;
	unsigned long long MEM_INFO_Inactive_anon;
	unsigned long long MEM_INFO_Active_file;
	unsigned long long MEM_INFO_Inactive_file;
	unsigned long long MEM_INFO_Unevictable;
	unsigned long long MEM_INFO_Mlocked;
	unsigned long long MEM_INFO_HighTotal;
	unsigned long long MEM_INFO_HighFree;
	unsigned long long MEM_INFO_LowTotal;
	unsigned long long MEM_INFO_LowFree;
	unsigned long long MEM_INFO_SwapTotal;
	unsigned long long MEM_INFO_SwapFree;
	unsigned long long MEM_INFO_Dirty;
	unsigned long long MEM_INFO_Writeback;
	unsigned long long MEM_INFO_AnonPages;
	unsigned long long MEM_INFO_Mapped;
	unsigned long long MEM_INFO_Shmem;
	unsigned long long MEM_INFO_Slab;
	unsigned long long MEM_INFO_SReclaimable;
	unsigned long long MEM_INFO_SUnreclaim;
	unsigned long long MEM_INFO_KernelStack;
	unsigned long long MEM_INFO_PageTables;
	unsigned long long MEM_INFO_NFS_Unstable;
	unsigned long long MEM_INFO_Bounce;
	unsigned long long MEM_INFO_WritebackTmp;
	unsigned long long MEM_INFO_CommitLimit;
	unsigned long long MEM_INFO_Committed_AS;
	unsigned long long MEM_INFO_VmallocTotal;
	unsigned long long MEM_INFO_VmallocUsed;
	unsigned long long MEM_INFO_VmallocChunk;
	unsigned long long MEM_INFO_AnonHugePages;
	unsigned long long MEM_INFO_CmaTotal;
	unsigned long long MEM_INFO_CmaFree;
	unsigned long long MEM_INFO_HugePages_Total;
	unsigned long long MEM_INFO_HugePages_Free;
	unsigned long long MEM_INFO_HugePages_Rsvd;
	unsigned long long MEM_INFO_HugePages_Surp;
	unsigned long long MEM_INFO_Hugepagesize;
	unsigned long long MEM_INFO_DirectMap4k;
	unsigned long long MEM_INFO_DirectMap2M;

};

extern pthread_t SYSTAT_LOOP(struct SYSTAT_SYSTEM * sys);

extern int SYSTAT_INI (struct SYSTAT_SYSTEM * sys);

extern int SYSTAT_UPDATE(struct SYSTAT_SYSTEM * sys);
