/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #4
** Filename: keygen.c
**********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]) {
	int randNum;
	int randChar;

	// seed rand num generator
	srand(time(NULL));

	// validate number of args
	if (argc < 2) {
		printf("Usage: keygen <key length>");
        exit(1);
	}

	// get key length
	int keyLen = atoi(argv[1]);

	// create key
	int i;
	for (i = 0; i < keyLen; i++) {
		randNum = rand() % 27;

		// determine letter
		if(randNum < 26) {
			randChar = 65 + randNum;
			printf("%c", randChar);
		}
		
		// or print space
		else {
			printf(" ");
		}
	}

	// add new line char at the end
	printf("\n");

	return 0;
}