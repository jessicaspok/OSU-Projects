/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #4
** Filename: otp_enc.c
**********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char **argv) {
	// validate number of args
	if (argc < 4) {
		fprintf(stderr, "Usage: otp_enc <plaintext file> <key> <port number>\n");
		exit(1);
	}

	// get port number from args
	int portNumber = atoi(argv[3]);

	// open plaintext and key files 
	int fdPlain = open(argv[1], O_RDONLY);
	int fdKey = open(argv[2], O_RDONLY);

	// error opening files
	if (fdPlain == -1 || fdKey == -1) {
		fprintf(stderr, "ERROR: opening files\n");
		exit(1);
	}

	// get file sizes
	int pLength = lseek(fdPlain, 0, SEEK_END);
	int kLength = lseek(fdKey, 0, SEEK_END);

	// key file must be larger than plaintext
	if (kLength < pLength) { 
		fprintf(stderr, "ERROR: key is too short\n");
		exit(1);
	}

	// string to hold plaintext
	char *plainText = malloc(sizeof(char) * pLength); 

	// point to begining of file
	lseek(fdPlain, 0, SEEK_SET);

	// read plaintext into string
	if (read(fdPlain, plainText, pLength) == -1) {
		fprintf(stderr, "ERROR: reading plaintext\n");
		exit(1);
	}

	// add null terminator
	plainText[pLength - 1] = '\0';
   
	// verify chars in plaintext are valid
	int i;
	for (i = 0; i < pLength - 1; i++) {
		// valid chars, do nothing
		if (isalpha(plainText[i]) || isspace(plainText[i])) {
		}
		
		// invalid char, error
		else { 
			fprintf(stderr, "ERROR: Plaintext contains invalid char\n");
			exit(1);
		}
	}

	// string to hold key
	char *keyText = malloc(sizeof(char) * kLength); 

	// point to begining of file
	lseek(fdKey, 0, SEEK_SET);

	// read key into string
	if (read(fdKey, keyText, kLength) == -1) {
		fprintf(stderr, "ERROR: reading key\n");
		exit(1);
	}

	// add null terminator
	keyText[kLength - 1] = '\0';
 
	// verify chars in key are valid
	for (i = 0; i < kLength - 1; i++) {
		// valid chars, do nothing
		if (isalpha(keyText[i]) || isspace(keyText[i])) {
		}
		
		// invalid char, error
		else { 
			fprintf(stderr, "ERROR: key contains invalid char\n");
			exit(1);
		}
	}

	// CLIENT
	// create socket
	int socketfd;

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "ERROR: socket\n");
		exit(1);
	}

	// set up address
	struct hostent * server_ip_address;
	server_ip_address = gethostbyname("localhost");

	if (server_ip_address == NULL) {
		fprintf(stderr, "ERROR: could not resolve host name\n");
		exit(1);
	}
 
	struct sockaddr_in server;

	// clear socket structure
	memset((char *)&server, 0, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(portNumber);
	memcpy(&server.sin_addr, server_ip_address->h_addr, server_ip_address->h_length);

	// connect socket
	if (connect(socketfd, (struct sockaddr*) &server, sizeof(server)) == -1) {
		fprintf(stderr, "ERROR: connect\n");
		exit(2);
	}

	// confirm connection
	int r;
	int confNum;
	
	// receive confirmation number
	if ((r = recv(socketfd, &confNum, sizeof(confNum), 0)) == -1) {
		fprintf(stderr, "ERROR: receive\n");
		exit(1);
	} 
   
	else if (r == 0) {
		fprintf(stderr, "ERROR: receive\n");
		exit(1);
	}

	// check confirmation number
	int confirm = ntohl(confNum);

	// incorrect
	if (confirm != 1) {
		fprintf(stderr, "ERROR: could not contact otp_enc_d on port %d\n", portNumber);
		exit(2);
	}

	// successful connection to otp_enc_d
	// convert plaintext, key sizes
	int pLengthSend = htonl(pLength); 
	int kLengthSend = htonl(kLength);

	// send plaintext, key sizes
	if (send(socketfd, &pLengthSend, sizeof(pLengthSend), 0) == -1) {
		fprintf(stderr, "ERROR: sending plaintext file\n");
		exit(1);
	}

	if (send(socketfd, &kLengthSend, sizeof(kLengthSend), 0) == -1) {
		fprintf(stderr, "ERROR: sending key file\n");
		exit(1);
	}

	// send plaintext
	int length = 0;
	
	// while there is file left to send
	while (length <= pLength) {
		// portion of plaintext to send
		char plainSend[1024];
		strncpy(plainSend, &plainText[length], 1023);

		// add null terminator
		plainSend[1024] = '\0';
		
		// send 
		if (send(socketfd, &plainSend, 1024, 0) == -1){
			fprintf(stderr, "ERROR: sending plaintext\n");
			exit(1);
		}

		// increment
		length += 1023;
	}

	// send key
	length = 0;
	
	// while there is text left to send
	while (length <= kLength) {
		// portion of key to send
		char keySend[1024];
		strncpy(keySend, &keyText[length], 1023);

		// add null terminator
		keySend[1024] = '\0';

		// send
		if (send(socketfd, &keySend, 1024, 0) == -1){
			fprintf(stderr, "ERROR: sending key\n");
			exit(1);
		}

		// increment
		length += 1023;
	}

	// receive encrypted text
	// allocate memory for ciphertext
	char *cipherText = malloc(sizeof(char) * pLength);
	char buffer[1042];

	// clear ciphertext 
	memset(cipherText, '\0', pLength);

	// receive cipher
	length = 0;
	r = 0;
	
	// while there is text left to receive
	while (length < pLength) { 
		// clear buffer
		memset((char *)buffer, '\0', sizeof(buffer));

		// receive
		r = recv(socketfd, buffer, 1024, 0);//receive

		// error
		if (r == -1) {
		    fprintf(stderr, "ERROR: receiving ciphertext file\n");
			exit(1);
		}	

		// end of data		
		else if (r == 0) {
			// not enough received
		    if (length < pLength) {
				fprintf(stderr, "ERROR: receiving ciphertext file\n");
				exit(1);
			}
		}
		
		// concat string
		else {
			strncat(cipherText,buffer,(r-1));
		}	   

		// increment
		length += (r-1); 
	}

	// add null terminator
	cipherText[pLength - 1] = '\0';

	// print ciphertext
	printf("%s\n", cipherText);

	// free memory
	free(plainText);
	free(keyText);
	free(cipherText);

	return 0;
}