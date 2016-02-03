#include <pthread.h>
#define SYSTAT_BUFFER 128
#define SYSTAT_FLAG_BUFFER 16
#define SYSTAT_INT unsigned long long
#define SYSTAT_FLOAT long double

struct SYSTAT_attr              {
	char current [SYSTAT_BUFFER];
};

struct SYSTAT_ns{

};

struct SYSTAT_statm{

};

struct SYSTAT_uid_map{

};

struct SYSTAT_autogroup{
	SYSTAT_INT autogroup;
	char personality [SYSTAT_BUFFER];
	SYSTAT_INT val;
};

struct SYSTAT_limits{

};

struct SYSTAT_projid_map{

};

struct SYSTAT_controlGroup{
	SYSTAT_INT heirachyID;
	char subsystems [SYSTAT_FLAG_BUFFER][SYSTAT_FLAG_BUFFER];
	char controlGroup [SYSTAT_BUFFER];
};

struct SYSTAT_cgroup{
	struct SYSTAT_controlGroup * controlGroups;
	SYSTAT_INT controlGroupCount;
};

struct SYSTAT_gid_map{

};

struct SYSTAT_maps{

};

struct SYSTAT_mountinfo{

};

struct SYSTAT_mounts{

};

struct SYSTAT_mountstats{

};

struct SYSTAT_net{

};

struct SYSTAT_root{

};

struct SYSTAT_sched{

};

struct SYSTAT_schedstat{

};

struct SYSTAT_smaps{

};

struct SYSTAT_stack{

};

struct SYSTAT_stat{

};

struct SYSTAT_status{

};

struct SYSTAT_syscall{

};

struct SYSTAT_task{

};

struct SYSTAT_timers{

};

struct SYSTAT_PROCESS{

	struct SYSTAT_attr attr;
	struct SYSTAT_autogroup autogroup;
	struct SYSTAT_cgroup cgroup;
	char cmdline [SYSTAT_BUFFER];
	char comm [SYSTAT_BUFFER];
	SYSTAT_INT coredump_filter;
	char cpuset [SYSTAT_BUFFER];
	struct SYSTAT_gid_map gid_map;
	struct SYSTAT_limits limits;
	SYSTAT_INT loginuid;
	SYSTAT_INT map_files [SYSTAT_BUFFER][2];
	SYSTAT_INT map_files_count;
	struct SYSTAT_maps maps;
	struct SYSTAT_mountinfo mountinfo;
	struct SYSTAT_mounts mounts;
	struct SYSTAT_mountstats mountstats;
	struct SYSTAT_net net;
	struct SYSTAT_ns ns;
	SYSTAT_INT oom_adj;
	SYSTAT_INT personality;
	struct SYSTAT_projid_map projid_map;
	struct SYSTAT_root root;
	struct SYSTAT_sched sched;
	struct SYSTAT_schedstat schedstat;
	SYSTAT_INT sessionid;
	char setgroups [SYSTAT_BUFFER];
	struct SYSTAT_smaps smaps;
	struct SYSTAT_stack stack;
	struct SYSTAT_stat stat;
	struct SYSTAT_statm statm;
	struct SYSTAT_status status;
	struct SYSTAT_syscall syscall;
	struct SYSTAT_task task;
	struct SYSTAT_timers timers;
	struct SYSTAT_uid_map uid_map;
	char wchan [SYSTAT_BUFFER];


};

struct SYSTAT_PROCESSINFO{
	struct SYSTAT_PROCESS * PROCESSES;
	SYSTAT_INT PROCESS_COUNT;
};

struct SYSTAT_PROCESSOR{
	SYSTAT_INT processor       ;
	char vendor_id [SYSTAT_BUFFER]       ;
	SYSTAT_INT cpu_family      ;
	SYSTAT_INT model           ;
	char model_name [SYSTAT_BUFFER]     ;
	SYSTAT_INT stepping        ;
	SYSTAT_INT microcode       ;
	SYSTAT_FLOAT cpu_MHz         ;
	SYSTAT_INT cache_size      ;
	SYSTAT_INT physical_id     ;
	SYSTAT_INT siblings        ;
	SYSTAT_INT core_id         ;
	SYSTAT_INT cpu_cores       ;
	SYSTAT_INT apicid          ;
	SYSTAT_INT initial_apicid  ;
	SYSTAT_INT fdiv_bug        ;
	SYSTAT_INT f00f_bug        ;
	SYSTAT_INT coma_bug        ;
	SYSTAT_INT fpu             ;
	SYSTAT_INT fpu_exception   ;
	SYSTAT_INT cpuid_level     ;
	SYSTAT_INT wp;
	char flags [SYSTAT_BUFFER] [SYSTAT_FLAG_BUFFER]           ;
	SYSTAT_INT flagCount;
	char bugs [SYSTAT_BUFFER]           ;
	SYSTAT_FLOAT bogomips        ;
	SYSTAT_INT clflush_size    ;
	SYSTAT_INT cache_alignment ;
	SYSTAT_INT address_size_physical   ;
	SYSTAT_INT address_size_virtual   ;
	char power_management [SYSTAT_BUFFER];
};

struct SYSTAT_CPUINFO{
	struct SYSTAT_PROCESSOR * PROCESSORS;
	SYSTAT_INT PROCESSOR_COUNT;
};

struct SYSTAT_MEMINFO{
	SYSTAT_INT MemTotal;
	SYSTAT_INT MemFree;
	SYSTAT_INT MemAvailable;
	SYSTAT_INT Buffers;
	SYSTAT_INT Cached;
	SYSTAT_INT SwapCached;
	SYSTAT_INT Active;
	SYSTAT_INT Inactive;
	SYSTAT_INT Active_anon;
	SYSTAT_INT Inactive_anon;
	SYSTAT_INT Active_file;
	SYSTAT_INT Inactive_file;
	SYSTAT_INT Unevictable;
	SYSTAT_INT Mlocked;
	SYSTAT_INT HighTotal;
	SYSTAT_INT HighFree;
	SYSTAT_INT LowTotal;
	SYSTAT_INT LowFree;
	SYSTAT_INT SwapTotal;
	SYSTAT_INT SwapFree;
	SYSTAT_INT Dirty;
	SYSTAT_INT Writeback;
	SYSTAT_INT AnonPages;
	SYSTAT_INT Mapped;
	SYSTAT_INT Shmem;
	SYSTAT_INT Slab;
	SYSTAT_INT SReclaimable;
	SYSTAT_INT SUnreclaim;
	SYSTAT_INT KernelStack;
	SYSTAT_INT PageTables;
	SYSTAT_INT NFS_Unstable;
	SYSTAT_INT Bounce;
	SYSTAT_INT WritebackTmp;
	SYSTAT_INT CommitLimit;
	SYSTAT_INT Committed_AS;
	SYSTAT_INT VmallocTotal;
	SYSTAT_INT VmallocUsed;
	SYSTAT_INT VmallocChunk;
	SYSTAT_INT AnonHugePages;
	SYSTAT_INT CmaTotal;
	SYSTAT_INT CmaFree;
	SYSTAT_INT HugePages_Total;
	SYSTAT_INT HugePages_Free;
	SYSTAT_INT HugePages_Rsvd;
	SYSTAT_INT HugePages_Surp;
	SYSTAT_INT Hugepagesize;
	SYSTAT_INT DirectMap4k;
	SYSTAT_INT DirectMap2M;
};

struct SYSTAT_SYSTEM{

	struct SYSTAT_CPUINFO CPUINFO;
	struct SYSTAT_MEMINFO MEMINFO;
	struct SYSTAT_PROCESSINFO PROCESSINFO;


};

extern pthread_t SYSTAT_LOOP(struct SYSTAT_SYSTEM * sys);

extern struct SYSTAT_SYSTEM * SYSTAT_INI ();

extern void SYSTAT_UPDATE(struct SYSTAT_SYSTEM * sys);
