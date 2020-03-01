#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <time.h> 
#include sys/times.h
#include sys/types.h
#include unistd.h

int main(){
	time_t startTime, userTime, sysTime, cUserTime, cSysTime, stopTime;
	pid_t childPPid, childPid, parentPPid, parentPid, parentCPid;
	int stat;

	time(&startTime);
	printf("START: %ld\n", startTime);



	if ((childPid = fork()) == 0){	//in child
		childPPid = getppid();
		sleep(1);
		printf("PPID:%d, PID: %d\n", childPPid, childPid);

		exit(0);
	}

	parentCPid = waitpid(childPid, &stat, 0);
	parentPPid = getppid();
	parentPid = getpid();
	printf("PPID:%d, PID: %d, CPID: %d\n", parentPPid, parentPid, parentCPid, WEXITSTATUS(stat));



	return 0;
}