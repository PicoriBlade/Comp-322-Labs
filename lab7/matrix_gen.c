#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	argc = argc;
	int mSize = atoi(argv[1]);	//matrix size
	srand(time(NULL));

	for(int i = 0; i < mSize; i++){
		for(int j = 0; j < mSize; j++)
			fprintf(stdout, "%4d", ((rand() % 201) - 100));
	}
	
	return 0;
}
