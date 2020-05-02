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

int main(int argc, char* argv[]){
	argc = argc;
	FILE* f;
	
	fprintf(stderr, "m.(%d)\n\n", getpid());

	f = fopen("lab6.log", "a+");
	fprintf(f, "Pop mole%s\n", argv[0]);

	

	return 0;
}
