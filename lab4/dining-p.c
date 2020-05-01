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




bool done = false;

void eat(int philNum){	
	fprintf(stdout, "Philosopher #%d is eating\n", philNum);
	usleep((rand() % 2000000) + 500000);
	
}

void think(int philNum){
	fprintf(stdout, "Philosopher #%d is thinking\n", philNum);
	usleep((rand() % 5000000) + 50000);  
	
}

void Signal_Handler(){
	done = true;
}

int main(int argc, char* argv[]){
	argc = argc;
	int total = 0;
	int seats = atoi(argv[1]);
	int position = atoi(argv[2]);
	int nextPosition = (position+1);
	if(nextPosition > seats){nextPosition = 1;}
	
	setpgid((getpid() - position), 0);

	if(position == 1)
		fprintf(stderr, "pgid(%d)\n\n", getpid());

	sem_t * sem1;
	sem_t * sem2;
	char sem1Name[10];
	char sem2Name[10];
	sprintf(sem1Name, "/%d", position);
	sprintf(sem2Name, "/%d", nextPosition);
	sem1 = sem_open(sem1Name, O_CREAT, 0666, 1);
	sem2 = sem_open(sem2Name, O_CREAT, 0666, 1);
	
	signal(SIGTERM, Signal_Handler);
	
	do{
		if((position%2) == 0){
			if(sem_trywait(sem1)==0){
				sem_wait(sem2);
				eat(position);

				sem_post(sem1);
				sem_post(sem2);
				think(position);
				
				total++;
			}
		}else{
			if(sem_trywait(sem2)==0){
				sem_wait(sem1);
				eat(position);
				
				sem_post(sem2);
				sem_post(sem1);
				think(position);
				
				total++;
			}
		}
	}while(!done);
	
	fprintf(stdout, "Philosopher #%d completed %d cycles\n\n", position, total);

	sem_close(sem1);
	sem_close(sem2);
	sem_unlink(sem2Name);
	sem_unlink(sem2Name);

	if(position == 1){
		for (int i = 0; i<seats; i++){
			kill(getpid()+i+1, SIGTERM);
		}
	}

	return 0;
}
