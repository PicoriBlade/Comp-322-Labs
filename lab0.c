#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

int main(int argc, char* argv[]){
	int i=0, j=0;
	int binToDec=0;
	int parityCounter=0;

	if(argc < 2){
		argv[1] = "binfile.txt"; //i dont want to type binfile.txt every time
	}else{
		//strcat(argv[1], ".txt");
	}
	
	int fd, sz;
	char *buffer = (char *) calloc(100, sizeof(char));

	fd = open(argv[1], O_RDONLY);
	//printf("%d", fd);
	if (fd<0) {
		perror("r1");
		exit(1);
	}

	for(i = 0; i<5; i++){
		for(j = 7; j>=0; j--){
			sz = read(fd, buffer, 1);
			buffer[sz] = '\0';

			if(buffer[0] == '\0'){
				buffer[0] = '0';
			}

			if(j!=0){
				binToDec = pow((atoi(buffer)*2), j) + binToDec;
			}else{
				binToDec = binToDec + atoi(buffer);
			}
			parityCounter = parityCounter + atoi(buffer);

			printf("%s", buffer);
		}
		read(fd, buffer, 1);
		printf(" %d, %c, %d, ", binToDec, (char) binToDec, parityCounter);
		if(parityCounter%2 == 1){
			printf("Odd\n");
		}else{
			printf("Even\n");
		}
		binToDec = 0;
		parityCounter = 0;
	}

	return 0;
}