#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
	bool errorCase=false;
	bool bytesInArgs=true;
	bool bytesInFile=false;
	int i=0, j=0;

	int binToDec=0;
	int charToBin=0;
	int parityCounter=0;
	bool done = false;

	int fd, sz;
	char *buffer = (char *) calloc(100, sizeof(char));

	char* asciiTableException[34];
	asciiTableException[0] = "NUL";
	asciiTableException[1] = "SOH";
	asciiTableException[2] = "STX";
	asciiTableException[3] = "ETX";
	asciiTableException[4] = "EOT";
	asciiTableException[5] = "ENQ";
	asciiTableException[6] = "ACK";
	asciiTableException[7] = "BEL";
	asciiTableException[8] = "BS";
	asciiTableException[9] = "HT";
	asciiTableException[10] = "LF";
	asciiTableException[11] = "VT";
	asciiTableException[12] = "FF";
	asciiTableException[13] = "CR";
	asciiTableException[14] = "SO";
	asciiTableException[15] = "SI";
	asciiTableException[16] = "DLE";
	asciiTableException[17] = "DC1";
	asciiTableException[18] = "DC2";
	asciiTableException[19] = "DC3";
	asciiTableException[20] = "DC4";
	asciiTableException[21] = "NAK";
	asciiTableException[22] = "SYN";
	asciiTableException[23] = "ETB";
	asciiTableException[24] = "CAN";
	asciiTableException[25] = "EM";
	asciiTableException[26] = "SUB";
	asciiTableException[27] = "ESC";
	asciiTableException[28] = "FS";
	asciiTableException[29] = "GS";
	asciiTableException[30] = "RS";
	asciiTableException[31] = "US";
	asciiTableException[32] = "SPACE";
	asciiTableException[33] = "DEL";

	if(argc < 2){
		errorCase=true;

	}else if(argc == 2){

		done = false;
		for(i = 0; argv[1][i] != '\0' && !done; i++){
			if(argv[1][i] != '0' && argv[1][i] != '1'){
				bytesInArgs = false;
				bytesInFile = true;
				//printf("%c\n", argv[1][i]);
				done = true;	//just finish, job done, byte error was found
			}					//still possible that its a file name instead
		}

		if(bytesInFile){
			fd = open(argv[1], O_RDONLY);
			if (fd<0) {	//in case the file doesnt exist
				errorCase = true;
				bytesInFile = false;
			}
		}

		if(bytesInFile){

			sz = read(fd, buffer, 1);
			buffer[sz] = '\0';

			if(buffer[0] == '\0'){
				errorCase = true;
				bytesInFile = false;	//if it just opened an empty file then its error
			}

			while(buffer[0] != '\0'){	//read the file bit by bit, checking for errors
				sz = read(fd, buffer, 1);
				buffer[sz] = '\0';
				if(buffer[0] != '0' && buffer[0] != '1' && buffer[0] != ' ' && buffer[0] != '\0'){
					errorCase = true;
					bytesInFile = false;
					//printf("%c,\n", buffer[0]);
					buffer[0]='\0'; //just finish, job done, error was found
				}
			}
			close(fd);
		}

	}else if(argc>2){
		for(i = 1; i < argc; i++){

			if(i == 1 && argv[1][0] == '-' && argv[1][1] == '\0'){
				i++;	//this accounts for the lab0 - 1010 case
			}

			for(j = 0; argv[i][j] != '\0'; j++){//I literally dont know why it wont use any value
												//that is set inside this loop.  code works fine 
												//but ignores my booleans which is ok?? but not really
				if(argv[i][j] != '0' && argv[i][j] != '1' && argv[i][j] != '\0'){
					errorCase = true;
					bytesInArgs = false;
					//printf("%c, %d.%d\n", argv[i][j], i, j);

					argv[i][j+1] = '\0';
					i = argc;	//just finish, job done, error was found
				}
			}
		}
	}

	///  checking done!  ///

	if(errorCase){
		printf("there was an error\n");
	}else if(bytesInFile){
		fd = open(argv[1], O_RDONLY);		//reopen the file
		printf("Original ASCII    Decimal  Parity\n");
		printf("-------- -------- -------- --------\n");

						//I know its set earlier to false
		done=false; 	//but this is cleaner in my opinion
		while(!done){
			for(j = 7; j>=0; j--){	//doing this in eights for the binary
				sz = read(fd, buffer, 1);//read the file bit by bit
				buffer[sz] = '\0';	//put a null at the end of the array
									//to let the string know when it
									//is done

				if(buffer[0] == '\0' || buffer[0] == ' '){	 
					while(j >= 0){		//if the character found is a null or space
						printf("0");	//and its not 8 bits yet, then pad
						j--;			//with 0s
					}	
				}else{
					printf("%s", buffer);
					parityCounter = parityCounter + atoi(buffer);

					if(j == 7){//ignore MSB
					}else if(j != 0){
						binToDec = pow((atoi(buffer)*2), j) + binToDec;
					}else{
						binToDec = binToDec + atoi(buffer);
					}
				}
				
			}
			if(buffer[0] != ' '){	//if the last read read a space, then 
									//dont read into the next byte
									//but if it did, then
				read(fd, buffer, 1);//skip the space between binaries
			}
			if(buffer[0] == '\0'){	//if the last byte loop read in a
				done = true;		//null, then the code must be done
			}

			if(binToDec == 127){
				printf(" %8s", asciiTableException[33]);
			}else if(binToDec <= 32 && binToDec >= 0){
				printf(" %8s", asciiTableException[binToDec]);
			}else{
				printf(" %8c", (char)binToDec);
			}

			printf(" %8d", binToDec);

			if(parityCounter%2 == 1){
				printf(" Odd     \n");
			}else{
				printf(" Even    \n");
			}

			binToDec = 0;
			parityCounter = 0;
		}
		close(fd);

	}else if(bytesInArgs){
		printf("Original ASCII    Decimal  Parity\n");
		printf("-------- -------- -------- --------\n");

		for(i = 1; i < argc; i++){
			if(i == 1 && argv[1][0] == '-' && argv[1][1] == '\0'){
				i++;	//this accounts for the lab0 - 1010 case
			}

			for(j = 0; j < 8; j++){
				if(argv[i][j] == '\0'){
					while(j < 8){		//if the character found is a null
						printf("0");	//and its not 8 bits yet, then pad
						j++;			//with 0s
					}
				}else{
					printf("%c", argv[i][j]);

					charToBin = argv[i][j] - '0';
					parityCounter = parityCounter + charToBin;


					if(j == 0){//ignore MSB
					}else if(j != 7){
						binToDec = pow((charToBin*2), (7 - j)) +binToDec;
					}else{
						binToDec = binToDec + charToBin;
					}
				}
			}

			if(binToDec == 127){
				printf(" %8s", asciiTableException[33]);
			}else if(binToDec <= 32 && binToDec >= 0){
				printf(" %8s", asciiTableException[binToDec]);
			}else{
				printf(" %8c", (char)binToDec);
			}

			printf(" %8d", binToDec);

			if(parityCounter%2 == 1){
				printf(" Odd     \n");
			}else{
				printf(" Even    \n");
			}

			binToDec = 0;
			parityCounter = 0;
		}
	}

	return 0;
}