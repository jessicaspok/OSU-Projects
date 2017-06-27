/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #4
** Filename: otp_dec_d.c
**********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<netinet/in.h>

int main(int argc, char ** argv) {
	int listenPort;
	int socketfd;
	int client_socket;
	int status;

	// validate number of args
	if (argc < 2) {
		fprintf(stderr, "Usage: otp_dec_d <port number>\n");
		exit(1);
	}
	
	// get port from args
	else {
		listenPort = atoi(argv[1]);
	}

	// SERVER
	// create socket
	if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {//Create
		fprintf(stderr, "ERROR: creating socket\n");
		exit(1);
	}

	// fill addr struct
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(listenPort);
	server.sin_addr.s_addr = INADDR_ANY;

	// bind socket to port
	if (bind(socketfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		fprintf(stderr, "ERROR: bind failed\n");
		exit(1);
	}

	// listen on port for up to 5 connections
	if (listen(socketfd, 5) == -1) {
		fprintf(stderr, "ERROR: listen failed\n");
		exit(1);
	}

	// loop and accept
	while (1) { 
		client_socket = accept(socketfd, NULL, NULL);
		if (client_socket == -1) {
			fprintf(stderr, "ERROR: accept failed\n");
			exit(1);
		}
	
		// fork
		int pid = fork();

		if (pid == -1) {
			fprintf(stderr, "ERROR: fork failed\n");
		}
		
		//child
		else if(pid == 0) {
			// send connection confimation num(1)
			int toSend = htonl(0);

			if(send(client_socket, &toSend, sizeof(toSend), 0) == -1){
				fprintf(stderr, "ERROR: client send failed\n");
			}

			// get size of ciphertext
			int cNum;
			
			if (recv(client_socket, &cNum, sizeof(cNum), 0) == -1) {
				fprintf(stderr, "ERROR: receive ciphertext\n");
			}
			
			// ciphertext size is 0
			else if (cNum == 0) {
				fprintf(stderr, "ERROR: receive ciphertext\n");
			}
			
			// length of cipher text file
			int cLength = ntohl(cNum);
		   
			// get size of key 
			int kNum;
			if (recv(client_socket, &kNum, sizeof(kNum), 0) == -1) {
				fprintf(stderr, "ERROR: receive key\n");
			}
			
			// key size is 0
			else if (kNum == 0) {
				fprintf(stderr, "ERROR: receive key\n");
			}

			// length of key file
			int kLength = ntohl(kNum);

			// allocate memory for ciphertext
			char *cipherText = malloc(sizeof(char) * cLength); 
			char buffer[1024];

			// clear ciphertext
			memset(cipherText, '\0', cLength);

			// receive ciphertext
			int length = 0;
			int r;
			
			// while there is text left to be received
			while (length <= cLength) {
				// clear buffer
				memset((char *)buffer, '\0', sizeof(buffer));
				
				// receive
				r = recv(client_socket, &buffer, 1024, 0);

				if (r == -1) {
					fprintf(stderr, "ERROR: receive ciphertext\n");
					break;
				}
				
				// end of data
				else if (r == 0) {
					// not enough received
					if (length < cLength) {
						break;
					}
				}
				
				// concat string
				else {
					strncat(cipherText,buffer,(r - 1));
				}

				// increment
				length += (r-1);
			}

			// add null terminator
			cipherText[cLength - 1] = '\0';
		
			// allocate memory for key 
			char *keyText = malloc(sizeof(char) * kLength); 
			
			// clear buffer and key
			memset((char *)&buffer, '\0', sizeof(buffer));
			memset(keyText, '\0', kLength);

			// receive key
			length = 0;

			// while there is still text to be received
			while (length <= kLength) {
				// clear buffer 
				memset((char *) buffer, '\0', sizeof(buffer));

				// receive
				r = recv(client_socket, &buffer, 1024, 0);

				if (r == -1) {
					fprintf(stderr, "ERROR: receive key \n");
					break;
				}
				
				// end of data
				else if (r == 0) {
					break;
				}
				
				// concat string
				else {
					strncat(keyText,buffer,(r - 1));
				}

				// increment
				length += (r-1);  
			}
	
			// add null terminator
			keyText[kLength - 1] = '\0';

			int cipherNum;
			int keyNum;
			int decNum;
			
			// decrypt ciphertext using key
			int i;
			for (i = 0; i < cLength - 1; i++) {
				// convert ciphertext chars to ints 0-26
				// space
				if (cipherText[i] == ' ') {
					cipherNum = 26;
				}
				
				// letter
				else {
					cipherNum = cipherText[i] - 65;
				}

				// convert key chars to ints 0-26
				// space
				if (keyText[i] == ' ') {
					keyNum = 26;
				}
				
				// letter
				else {
					keyNum = keyText[i] - 65;
				}

				// get decrypted char
				decNum = cipherNum - keyNum;
				
				// if <0 add 27
				if (decNum < 0) {
					decNum += 27;
				}

				// replace ciphertext char with decrypted char
				// space
				if (decNum == 26) { 
					cipherText[i] = ' ';
				}
				
				// letter
				else {
					cipherText[i] = 'A' + (char)decNum;
				}
			}

			// send back decrypted file
			length = 0;

			// while there is still text left to send
			while (length <= cLength) {
				char plainSend[1024];

				// copy portion of string to send	
				strncpy(plainSend, &cipherText[length], 1023);

				// add null terminator
				plainSend[1024] = '\0'; 

				if (send(client_socket, &plainSend, 1024, 0) == -1) {
					fprintf(stderr, "ERROR: send decryption text\n");
				}

				// increment
				length += 1023; 
			}

			// free memory
			free(cipherText);
			// free(keyText);
		}      
		
		// parent
		else {
			// close client connection
			close(client_socket);

			// children finished?
			do {
				waitpid(pid, &status, 0);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	
	// close socket
	close(socketfd);
	   
	return 0;
}