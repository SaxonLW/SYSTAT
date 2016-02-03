#include "stringTree.h"
#include "SYSTAT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SYSTAT_CPUINFO_FUNC_LIST.h"
#include <pthread.h>

char buffer [SYSTAT_BUFFER];

void cpuInfoInitialise(){
	int i;
	stringPack keys[29];

	newStringPack(&keys[0],"processor",update_processor       ,9        );
	newStringPack(&keys[1],"vendor_id",update_vendor_id       ,9        );
	newStringPack(&keys[2],"cpu family",update_cpu_family      ,10      );
	newStringPack(&keys[3],"model",update_model           ,5            );
	newStringPack(&keys[4],"model name",update_model_name      ,10      );
	newStringPack(&keys[5],"stepping",update_stepping        ,8         );
	newStringPack(&keys[6],"microcode",update_microcode       ,9        );
	newStringPack(&keys[7],"cpu MHz",update_cpu_MHz         ,7          );
	newStringPack(&keys[8],"cache size",update_cache_size      ,10      );
	newStringPack(&keys[9],"physical id",update_physical_id     ,11     );
	newStringPack(&keys[10],"siblings",update_siblings        ,8         );
	newStringPack(&keys[11],"core id",update_core_id         ,7          );
	newStringPack(&keys[12],"cpu cores",update_cpu_cores       ,9        );
	newStringPack(&keys[13],"apicid",update_apicid          ,6           );
	newStringPack(&keys[14],"initial apicid",update_initial_apicid  ,14  );
	newStringPack(&keys[15],"fdiv_bug",update_fdiv_bug        ,8         );
	newStringPack(&keys[16],"f00f_bug",update_f00f_bug        ,8         );
	newStringPack(&keys[17],"coma_bug",update_coma_bug        ,8         );
	newStringPack(&keys[18],"fpu",update_fpu             ,3              );
	newStringPack(&keys[19],"fpu_exception",update_fpu_exception   ,13   );
	newStringPack(&keys[20],"cpuid level",update_cpuid_level     ,11     );
	newStringPack(&keys[21],"wp",update_wp              ,2               );
	newStringPack(&keys[22],"flags",update_flags,5);
	newStringPack(&keys[23],"bugs",update_bugs,4);
	newStringPack(&keys[24],"bogomips",update_bogomips,8         );
	newStringPack(&keys[25],"clflush size",update_clflush_size,12    );
	newStringPack(&keys[26],"cache_alignment",update_cache_alignment,15 );
	newStringPack(&keys[27],"address sizes",update_address_sizes,13);
	newStringPack(&keys[28],"power management",update_power_management,16);

	for (i = 0; i < 29; i++){
		addString(keys[i]);
	}
}

void determineValueCPU (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	int i = 0;
	sNode * p = getHead();
	void (*func)(int * index, struct SYSTAT_CPUINFO * sys, char * string);

	while (i < SYSTAT_BUFFER){
		if (string[i] == '\t' || string[i] == ':'){
			break;
		}
		if (p->links[string[i]] == NULL){
			return;
		}
		p = p->links[string[i]];
		i++;
	}

	func = p->func;

	func(index,sys, string);

	return;
}

void cpuInfoUpdate(struct SYSTAT_CPUINFO * sys){

	FILE * CPUINFO;

	CPUINFO = fopen("/proc/cpuinfo", "r");

	char * buffer = calloc(SYSTAT_BUFFER,sizeof(char));
	int * index = malloc(sizeof(int));
	*index = -1;

	while (fgets(buffer,SYSTAT_BUFFER,CPUINFO) != NULL){
		determineValueCPU(index,sys,buffer);
	}

	free(index);
	free(buffer);
	fclose(CPUINFO);
	return;
}

void cpuInfoUpdateThread(struct SYSTAT_CPUINFO * sys){
	cpuInfoUpdate(sys);
	pthread_exit(NULL);
}

void increaseProcessors(struct SYSTAT_CPUINFO * sys){
	if (sys->PROCESSOR_COUNT%8 == 0){
		sys->PROCESSORS = realloc(sys->PROCESSORS, (sys->PROCESSOR_COUNT +8) * sizeof(struct SYSTAT_PROCESSOR));
	}
	sys->PROCESSOR_COUNT++;
}

unsigned long long getULL (char * string, int hasSpace){
	unsigned long long val;

	if(hasSpace){
		sscanf(string,"%s %s %s %llu", buffer, buffer,buffer, &val);
	}
	else{
		sscanf(string,"%s %s %llu", buffer, buffer, &val);
	}
	return val;
}

void getString (char * string, char * target, int hasSpace){



	if(hasSpace){
		sscanf(string,"%s %s %s %s",buffer,buffer,buffer,target);
	}
	else{
		sscanf(string,"%s %s %s",buffer,buffer,target);
	}

	return;
}

/*
 * Only real interesting one
 * This allows for an bit of dynamic memory allocation
 * Only increase if the index increases over the previous amount of processor count
 * Increase memory by 8  each time (seemed the best number given how many cores most physical cores
 * processors have.
 * Only increase at the 8 mark via mod check.
 */

void update_processor       (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	*index+=1;
	if (sys->PROCESSOR_COUNT == *index){
		if (sys->PROCESSOR_COUNT == 0){
			sys->PROCESSORS = calloc(8, sizeof(struct SYSTAT_PROCESSOR));
			sys->PROCESSOR_COUNT = 1;
		}
		else{
			increaseProcessors(sys);
		}
	}

	sys->PROCESSORS[*index].processor = getULL(string,0);

	return;
}
void update_vendor_id       (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	getString(string,sys->PROCESSORS[*index].vendor_id,0);
	return;
}
void update_cpu_family      (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].cpu_family = getULL(string, 1);

	return;
}
void update_model           (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	return;
}
void update_model_name      (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	int i = 0;
	while (string[i] != ':'){
		i++;
	}
	i+=2;

	strcpy(sys->PROCESSORS[*index].model_name, &string[i]);

	return;
}
void update_stepping        (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].stepping = getULL(string,0);

	return;
}
void update_microcode       (int * index, struct SYSTAT_CPUINFO * sys, char * string){


	char hexVal [16];

	sscanf(string, "%s %s %s", buffer, buffer, hexVal);

	sys->PROCESSORS[*index].microcode = strtoull(hexVal,NULL,0);

	return;
}
void update_cpu_MHz         (int * index, struct SYSTAT_CPUINFO * sys, char * string){



	sscanf(string,"%s %s %s %Lf",buffer,buffer,buffer,&sys->PROCESSORS[*index].cpu_MHz);

	return;
}
void update_cache_size      (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].cache_size = getULL(string, 1);

	return;
}
void update_physical_id     (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].physical_id = getULL(string,1);
	return;
}
void update_siblings        (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	sys->PROCESSORS[*index].siblings = getULL(string,0);
	return;
}
void update_core_id         (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].core_id = getULL(string,1);
	return;
}
void update_cpu_cores       (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].cpu_cores = getULL(string,1);

	return;
}
void update_apicid          (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].apicid = getULL(string,0);

	return;
}
void update_initial_apicid  (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].initial_apicid = getULL(string,1);

	return;
}
void update_fdiv_bug        (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	char buffer [5];
	getString(string,buffer,0);
	sys->PROCESSORS[*index].fdiv_bug = (buffer[0] == 'y');
	return;
}
void update_f00f_bug        (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	char buffer [5];
	getString(string,buffer,0);
	sys->PROCESSORS[*index].f00f_bug = (buffer[0] == 'y');

	return;
}
void update_coma_bug        (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	char buffer [5];
		getString(string,buffer,0);
		sys->PROCESSORS[*index].coma_bug = (buffer[0] == 'y');

	return;
}
void update_fpu             (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	char buffer [5];
			getString(string,buffer,0);
			sys->PROCESSORS[*index].fpu = (buffer[0] == 'y');

	return;
}
void update_fpu_exception   (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	char buffer [5];
			getString(string,buffer,0);
			sys->PROCESSORS[*index].fpu_exception = (buffer[0] == 'y');

	return;
}
void update_cpuid_level     (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	return;
}
void update_wp              (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	char buffer [5];
				getString(string,buffer,0);
				sys->PROCESSORS[*index].wp = (buffer[0] == 'y');

	return;
}
void update_flags           (int * index, struct SYSTAT_CPUINFO * sys, char * string){
	int i = 0;
	int flagIndex = 0;
	while (string[i] != ':' && string[i] != '\0'){
		i++;
	}
	i+=2;
	while (i < SYSTAT_BUFFER && string[i] != '\0'){
		if(string[i] != ' ' || string[i] != '\0'){
			sscanf(&string[i],"%s ",sys->PROCESSORS[*index].flags[flagIndex]);
			if (sys->PROCESSORS[*index].flagCount == flagIndex){
				sys->PROCESSORS[*index].flagCount++;
			}
			flagIndex++;
		}
		while (i < SYSTAT_BUFFER && (string[i] != ' ') && string[i]!='\0'){
			i++;
		}
		i++;
	}

	return;
}
void update_bugs            (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	strcpy(sys->PROCESSORS[*index].bugs,"None");
	getString(string,sys->PROCESSORS[*index].bugs,0);

	return;
}
void update_bogomips        (int * index, struct SYSTAT_CPUINFO * sys, char * string){


	sscanf(string,"%s %s %Lf",buffer,buffer,&sys->PROCESSORS[*index].bogomips);
	return;
}
void update_clflush_size    (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].clflush_size = getULL(string, 1);

	return;
}
void update_cache_alignment (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	sys->PROCESSORS[*index].cache_alignment = getULL(string, 1);

	return;
}
void update_address_sizes   (int * index, struct SYSTAT_CPUINFO * sys, char * string){

	char buffer[20];

	sscanf(string, "%s %s %s %llu %s %s %llu", buffer, buffer, buffer, &sys->PROCESSORS[*index].address_size_physical, buffer, buffer, &sys->PROCESSORS[*index].address_size_virtual);
	return;
}
void update_power_management(int * index, struct SYSTAT_CPUINFO * sys, char * string){

	strcpy(sys->PROCESSORS[*index].bugs,"None");
	getString(string,sys->PROCESSORS[*index].power_management,0);

	return;

	return;
}
