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

int main(int argc, char* argv[]){
	argc = argc;
	unsigned int adress = atoi(argv[1]);
	unsigned int pageNum = adress/ 4096;
	unsigned int offset = adress % 4096;


	fprintf(stderr, "The address %d contains:\n", adress);
	fprintf(stderr, "page number = %d\n", pageNum);
	fprintf(stderr, "offset = %d\n", offset);
	
	return 0;
}
