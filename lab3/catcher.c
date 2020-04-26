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
#include <signal.h>

char* sigs[] = {"0", "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE", "9", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "19", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};


void sighandler(int sigNum){
	static int termCt = 0;
	static int sigTotal = 0;
	sigTotal++;
	fprintf(stderr, "%d caught at %ld\n", sigNum, time(NULL));
	if (sigNum == 15){
		termCt++;
	}else{
		termCt = 0;
	}
	if (termCt == 3){
		fprintf(stderr, "Total signals count = %d\n\n", sigTotal);
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char* argv[]){
	
	for (int i = 1; i < argc; i++){
		for (int j = 1; j < 29; j++){
			if (strcmp(argv[i], sigs[j]) == 0)
				signal(j, sighandler);
		}
	}

	fprintf(stderr, "%d\n", getpid());
	
	while(1){
		sleep(1);
	}

	return 0;
}
