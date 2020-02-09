#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		argv[1] = "binfile.txt"; //i dont want to type binfile.txt every time
		//printf("Nothing provided\n");
		//exit(1);

	}else{
		//strcat(argv[1], ".txt");
	}

	int i=0, j=0;
	int binToDec=0;
	int parityCounter=0;
	int fd, sz;
	char *buffer = (char *) calloc(100, sizeof(char));

	printf("Original ASCII    Decimal  Parity\n");
	printf("-------- -------- -------- --------\n");

	fd = open(argv[1], O_RDONLY);
	if (fd<0) {			//in case the file doesnt exist
		perror("r1");
		exit(1);
	}

	for(i = 0; i<5; i++){
		for(j = 7; j>=0; j--){//doing this in eights for the binay
			sz = read(fd, buffer, 1);//read the file bi by bit
			buffer[sz] = '\0';	//put a null at the end of the array
								//to let the string know when it
								//is done

			if(buffer[0] == '\0'){
				buffer[0] = '0';
			}

			//binary to decimal conversion
			//counts down from 2^7 to 2^0
			//there was a problem where 2^0 adds a 1, so
			//I skip that and just add the last bit
			if(j!=0){
				binToDec = pow((atoi(buffer)*2), j) + binToDec;
			}else{
				binToDec = binToDec + atoi(buffer);
			}

			//counts the number of ones for parity
			parityCounter = parityCounter + atoi(buffer);

			printf("%s", buffer);
		}
		read(fd, buffer, 1);//skip the space between binaries

		//print out data in a neat way
		printf(" %8c %8d", (char) binToDec, binToDec);
		if(parityCounter%2 == 1){
			printf(" Odd     \n");
		}else{
			printf(" Even    \n");
		}

		//reset the decimal counter and the parity counter for next loop
		binToDec = 0;
		parityCounter = 0;
	}

	return 0;
}
