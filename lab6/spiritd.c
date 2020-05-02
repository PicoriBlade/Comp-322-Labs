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
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/shm.h>
#include <pthread.h>
#include <syslog.h>
#include <sys/resource.h>


int sigNum = 0;

void sighandler(int signall){
	sigNum = signall;
}

int main(){
	pid_t cPid1 = 0;
	pid_t cPid2 = 0;
	struct rlimit lim;
	int fd0, fd1, fd2;
	bool done = false;
	char* args[2];
	char currentPath[FILENAME_MAX];

	args[1] = NULL;
	args[0] = "0";
//	execv("./mole", args);

	signal(SIGTERM, sighandler);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);

	umask(0);

	if(fork() != 0){
		exit(0);
	}

fprintf(stderr, "(%d)\n\n", getpid());

	setsid();
	
	getcwd(currentPath, sizeof(currentPath));
fprintf(stderr, "(%s)\n\n", currentPath);
	
	chdir("~/");

	getrlimit(RLIMIT_NOFILE, &lim);
	if(lim.rlim_max == RLIM_INFINITY)
		lim.rlim_max = 1024;
	for(unsigned int i = 0; i < lim.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	
	fd0=fd0;
	fd1=fd1;	//get rid of the unused warning...
	fd2=fd2;


	do{
		if(sigNum == 15){	//TERM
			done = true;

			if(cPid1 != 0)
				kill(cPid1, SIGTERM);
			if(cPid2 != 0)
				kill(cPid2, SIGTERM);
		}else if(sigNum == 10){	//USR1
			if(cPid1 != 0)
				kill(cPid1, SIGTERM);

			if((rand()%2) == 0){
				args[0] = "1";
			}else{
				args[0] = "2";
			}
					
			if((cPid1 = fork()) == 0){
				chdir(currentPath);	
				execv("./mole", args);
				
			}
			sigNum = 0;
		}else if(sigNum == 12){	//USR2
			if(cPid2 != 0)
				kill(cPid2, SIGTERM);
			
			if((rand()%2) == 0){
				args[0] = "1";
			}else{
				args[0] = "2";
			}
			
			if((cPid2 = fork()) == 0){
				chdir(currentPath);
				execv("./mole", args);
			}
			
			sigNum = 0;
		}
	}while(!done);

	return 0;
}
