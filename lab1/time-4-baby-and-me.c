#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	struct tms timing;
	time_t startTime, stopTime;
	pid_t childPPid, childPid, parentPPid, parentPid, parentCPid;
	int stat;

	time(&startTime);
	printf("START: %ld\n", startTime);

	if ((childPid = fork()) == 0){	//in child
		childPid = getpid();
		childPPid = getppid();
		int i, j;
		for(i=0; i<209999999; i++){j+=i*i;}
		printf("PPID:%d, PID: %d\n", childPPid, childPid);

		exit(0);
	}

	parentCPid = waitpid(childPid, &stat, 0);
	parentPPid = getppid();
	parentPid = getpid();
	printf("PPID:%d, PID: %d, CPID: %d, RETVAL: %d\n", parentPPid, parentPid, parentCPid, WEXITSTATUS(stat));
	
	times(&timing);
	printf("USER: %ld, SYS:  %ld\n", timing.tms_utime, timing.tms_stime);
	printf("CUSER:%ld, CSYS: %ld\n", timing.tms_cutime, timing.tms_cstime);

	time(&stopTime);
	printf("STOP: %ld\n", stopTime);

	return 0;
}
