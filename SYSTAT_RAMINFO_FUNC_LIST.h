#include "SYSTAT.h"

void update_MemTotal       (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_MemFree        (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_MemAvailable   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Buffers        (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Cached         (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_SwapCached     (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Active         (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Inactive       (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Active_anon   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Inactive_anon (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Active_file   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Inactive_file (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Unevictable    (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Mlocked        (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_HighTotal      (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_HighFree       (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_LowTotal       (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_LowFree        (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_SwapTotal      (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_SwapFree       (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Dirty          (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Writeback      (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_AnonPages      (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Mapped         (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Shmem          (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Slab           (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_SReclaimable   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_SUnreclaim     (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_KernelStack    (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_PageTables     (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_NFS_Unstable   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Bounce         (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_WritebackTmp   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_CommitLimit    (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Committed_AS   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_VmallocTotal   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_VmallocUsed    (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_VmallocChunk   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_AnonHugePages  (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_CmaTotal       (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_CmaFree        (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_HugePages_Total(struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_HugePages_Free (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_HugePages_Rsvd (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_HugePages_Surp (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_Hugepagesize   (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_DirectMap4k    (struct SYSTAT_MEMINFO * sys, unsigned long long val);
void update_DirectMap2M    (struct SYSTAT_MEMINFO * sys, unsigned long long val);
