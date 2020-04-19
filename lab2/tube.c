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
	int p[2];
	pid_t childPid1, childPid2;
	int childNum;
	int commaSpot = 0;
	int cmd1Size = argc;
	int cmd2Size = argc;
	

//////////////////////////////////////
	if (pipe(p) <0)
		exit(1);
//////////////////////////////////////
	if ((childPid1 = fork())){
		if ((childPid2 = fork())){
			childNum = 0; //parent
		}else{
			childNum = 2;
		}
	}else{
		childNum = 1;
	}


///////////////////////////////////////    find the size of the cmd 1 and 2 arrays
	for (int i = 0; i < argc; i++){
		if (argv[i][0] == ',')
			commaSpot = i;
	}
	cmd1Size = commaSpot - 1;
	cmd2Size = (argc-commaSpot) - 1;
////////////////////////////////////////   fill cmd1 array
	char* cmd1[cmd1Size];
	for (int i = 0; i < cmd1Size; i++){
		cmd1[i] = argv[i + 1];
	}
////////////////////////////////////////   fill cmd2 array
	char* cmd2[cmd2Size];
	for (int i = 0; i < cmd2Size; i++){
		cmd2[i] = argv[i + 1 + commaSpot];
	}
////////////////////////////////////////

	if (childNum == 0){
		fprintf(stderr, "child1: %d\nchild2: %d\n", childPid1, childPid2);
		close(p[0]);
		close(p[1]);
	}

	if (childNum == 1){
                printf("1\n\n");
		dup2(p[1],1);
		dup2(p[0],0);
		execve(cmd1[0], cmd1+1, NULL);
		exit(0);
	}

	if (childNum == 2){
		printf("2\n\n");
		dup2(p[1],1);
		dup2(p[0],0);
		printf("%s\n\n", cmd2[0]);
		execve(cmd2[0], cmd2+1, NULL);
		exit(0);
	}
	
	return 0;
}
