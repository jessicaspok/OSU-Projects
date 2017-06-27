/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #4
** Filename: otp_dec.c
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
		fprintf(stderr, "Usage: otp_dec <ciphertext file> <key> <port number>\n");
		exit(1);
	}

	// get port number from args
	int portNum = atoi(argv[3]);

	// open ciphertext and key files
	int fdCipher = open(argv[1], O_RDONLY);
	int fdKey = open(argv[2], O_RDONLY);

	// error opening files
	if (fdCipher == -1 || fdKey == -1) {
		fprintf(stderr, "ERROR: opening files\n");
		exit(1);
	}

	// get file sizes
	int cLength = lseek(fdCipher, 0, SEEK_END);
	int kLength = lseek(fdKey, 0, SEEK_END);

	// key file must be larger than ciphertext
	if (kLength < cLength) {
		fprintf(stderr, "ERROR: key is too short\n");
		exit(1);
	}

	//string to hold ciphertext
	char *cipherText = malloc(sizeof(char) * cLength); 

	// point to begining of file
	lseek(fdCipher, 0, SEEK_SET);

	// read ciphertext into string
	if (read(fdCipher, cipherText, cLength) == -1) {
		fprintf(stderr, "ERROR: reading ciphetext\n");
		exit(1);
	}

	// add null terminator
	cipherText[cLength - 1] = '\0';

	// verify chars in ciphertext are valid
	int i;
	for (i = 0; i < cLength - 1; i++) {
		// valid chars, do nothing
		if (isalpha(cipherText[i]) || isspace(cipherText[i])) {
		}
		
		// invalid char, error
		else { 
			fprintf(stderr, "ERROR: Ciphertext contains invalid char\n");
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
	server.sin_port = htons(portNum);
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
	if (confirm != 0) {
		fprintf(stderr, "ERROR: could not contact otp_dec_d on port %d\n", portNum);
		exit(2);
	}

	// successful connection to otp_enc_d
	// convert ciphertext, key sizes
	int cLengthSend = htonl(cLength); 
	int kLengthSend = htonl(kLength); 

	// send ciphertext, key sizes
	if (send(socketfd, &cLengthSend, sizeof(cLengthSend), 0) == -1) {
		fprintf(stderr, "ERROR: sending ciphertext file\n");
		exit(1);
	}

	if (send(socketfd, &kLengthSend, sizeof(kLengthSend), 0) == -1) {
		fprintf(stderr, "ERROR: sending key file\n");
		exit(1);
	}

	// send ciphertext
	int length = 0;
	
	// while there is file left to send
	while (length <= cLength) {
		// portion of plaintext to send
		char cipherSend[1024];
		strncpy(cipherSend, &cipherText[length], 1023);

		// add null terminator
		cipherSend[1024] = '\0'; 

		// send
		if (send(socketfd, cipherSend, 1024, 0) == -1){
			printf("ERROR: sending ciphertext\n");
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

	// receive decrypted text
	// allocate memory for plaintext
	char *plainText = malloc(sizeof(char) * cLength);
	char buffer[1024];

	// clear plaintext 
	memset(plainText, '\0', cLength);

	// receive plaintext
	length = 0;
	r = 0;
	
	// while there is text left to receive
	while(length < cLength) {       
		// clear buffer 
		memset((char *)buffer, '\0', sizeof(buffer));

		// receive
		r = recv(socketfd, &buffer, 1024, 0);
	
		// error
		if (r == -1) {
			fprintf(stderr, "ERROR: receiving plaintext file\n");
			exit(1);
		}	

		// end of data
		else if (r == 0) {
			// not enough received
			if (length < cLength) {
				fprintf(stderr, "ERROR: receiving plaintext file\n");
				exit(1);
			}
		}
		
		// concat string
		else {
			strncat(plainText,buffer,(r-1));
		}	   
	
		// increment
		length += (r-1); 
	}

	// add null terminator
	plainText[cLength - 1] = '\0';

	// print plaintext
	printf("%s\n", plainText);

	// free memory
	free(plainText);
	free(keyText);
	free(cipherText);

	return 0;
}