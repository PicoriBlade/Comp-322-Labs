  
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

int main(int argc, char* argv[]){
	pid_t childPid;
	
	argc = argc;

	if((childPid = fork()) != 0){
		fprintf( stderr, "%d\n", childPid);
	}else{
		execve(argv[1], argv+1, NULL);
		exit(0);
	}

	

	return 0;
}
