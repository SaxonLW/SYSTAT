#include <stdlib.h>
#include <stdio.h>
#include "SYSTAT.h"

static void cat(FILE *fp)
{
    char   buffer[4096];
    size_t nbytes;
    while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), fp)) != 0)
         fwrite(buffer, sizeof(char), nbytes, stdout);
}

void processesUpdate(struct SYSTAT_SYSTEM * sys){
	FILE * PROCFOLDER;
	PROCFOLDER = popen("ls /proc", "r");
	//cat(PROCFOLDER);
}
