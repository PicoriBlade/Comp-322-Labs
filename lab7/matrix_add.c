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
#include <errno.h>
#include <sys/shm.h>
#include <pthread.h>
#include <syslog.h>
#include <sys/resource.h>
#include <aio.h>


void matrix_add(char* block, int bSize, int scalar){
	char buff[12];	//i wanted to do 4 but the code would keep warning about oh no what if 12 digits long but it wont be whatever.
	int num = 0;

	for(int i = 0; i < bSize; i = i+4){
		strncpy(buff, block, 4);
		num = atoi(buff);
		num += scalar;
		sprintf(buff, "%4d", num);
		for(int j = 0; j < 4; j++)
			block[i+j] = buff[j];

	}
}

int main(int argc, char* argv[]){
	argc = argc;
	time_t startTime, endTime;
	time(&startTime);

	int scalar = rand() % 100;
	int size = atoi(argv[1]);
	int blocks = atoi(argv[2]);
	int bSize = (size / blocks) * (size / blocks) * 4;	//max lenght being the -100
	int offset = 0;
	int f = open("matrix_file.size", O_RDONLY);
	int f2= open(argv[4], O_WRONLY|O_CREAT);
	

	char* last = (char *)malloc(sizeof(char)*bSize);
	char* current = (char *)malloc(sizeof(char)*bSize);
	char* next = (char *)malloc(sizeof(char)*bSize);

	struct aiocb aioBlock[3];

	for(int i = 0; i < 3; i++){
		aioBlock[i].aio_fildes = f;
		aioBlock[i].aio_nbytes = bSize; 
		aioBlock[i].aio_sigevent.sigev_notify = SIGEV_NONE;
	}

	aioBlock[0].aio_fildes = f2;

	aioBlock[0].aio_buf = last;
	aioBlock[1].aio_buf = current;
	aioBlock[2].aio_buf = next;

	aioBlock[1].aio_offset = offset;
	offset += bSize;

	aio_read(&aioBlock[1]);
	aio_return(&aioBlock[1]);
	

	for(int i = 0; i < ((blocks * blocks) - 2); i++){
		aioBlock[2].aio_offset = offset;
		offset += bSize;

		aio_read(&aioBlock[2]);
		
		matrix_add(current, bSize, scalar);
		
		aio_write(&aioBlock[0]);
		aio_return(&aioBlock[0]);
		memcpy(last, current, bSize);

		aio_return(&aioBlock[2]);
		memcpy(current, next, bSize);
	}
	
	matrix_add(current, bSize, scalar);
	aio_write(&aioBlock[0]);
	aio_return(&aioBlock[0]);

	time(&endTime);
	printf("%ld\n\n", (endTime-startTime));

	return 0;
}
