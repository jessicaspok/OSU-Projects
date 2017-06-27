/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #4
** Filename: otp_enc_d.c
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
		fprintf(stderr, "Usage: otp_enc_d <port number>\n");
		exit(1);
	}
	
	// get port from args
	else {
		listenPort = atoi(argv[1]);
	}

	// SERVER
	// create socket
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
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
		
		// child
		else if (pid == 0) {
			// send connection confimation num(1)
			int toSend = htonl(1);

			if (send(client_socket, &toSend, sizeof(toSend), 0) == -1){
				fprintf(stderr, "ERROR: client send failed\n");
				exit(1);
			}

			// get size of plaintext
			int pNum;
			
			if (recv(client_socket, &pNum, sizeof(pNum), 0) == -1) {
				fprintf(stderr, "ERROR: receive plaintext\n");
			}
		   
			// plaintext size is 0
			else if (pNum == 0) {
				fprintf(stderr, "ERROR: receive plaintext\n");
			}
			
			// length of plaintext file
			int pLength = ntohl(pNum);
		   
			// get size of key
			int kNum;
			if (recv(client_socket, &kNum, sizeof(kNum), 0) == -1) {
				fprintf(stderr, "ERROR: receive key\n");
			}
		  
			// key size is 0
			else if(kNum == 0) {
				fprintf(stderr, "ERROR: receive key\n");
			}

			// length of key file
			int kLength = ntohl(kNum);//convert

			// allocate memory for plain text
			char *plainText = malloc(sizeof(char) * pLength); 
			char buffer[1024];

			// clear plaintext
			memset(plainText, '\0', pLength);

			// receive plaintext
			int length = 0;
			int r;
			
			// while there is text left to be received
			while (length <= pLength) {
				// clear buffer
				memset((char *)buffer, '\0', sizeof(buffer));

				// receive
				r = recv(client_socket, &buffer, 1024, 0);

				if (r == -1) {
					fprintf(stderr, "ERROR: receive plaintext\n");
					break;
				}
			  
				// end of data
				else if (r == 0) {
					// not enough received
					if (length < pLength) {
						break;
					}
				}
				
				// concat string
				else {
					strncat(plainText,buffer,(r - 1));
				} 
				
				// increment
				length += (r-1);
			}

			// add null terminator
			plainText[pLength - 1] = '\0'; 

			// allocate memory for key
			char *keyText = malloc(sizeof(char) * kLength); 
			
			// clear buffer and key
			memset((char *)buffer, '\0', sizeof(buffer));
			memset(keyText, '\0', kLength);

			// receive key
			length = 0;

			// while there is still text to be received
			while (length <= kLength) {
				// clear buffer 
				memset((char *)buffer, '\0', sizeof(buffer)); 

				//receive
				r = recv(client_socket, &buffer, 1024, 0);

				if (r == -1) {
					fprintf(stderr, "ERROR: receive key\n");
					break;
				}
			
				//end of data
				else if (r == 0) {
					break;
				}
			  
				// concat string
				else {
					strncat(keyText,buffer,(r - 1));
				}
			   
				// increment
				length += (r - 1);
			}

			// add null terminator
			keyText[kLength - 1] = '\0';

			int plainNum;
			int keyNum;
			int encNum;
			
			// encrypt plaintext using key
			int i;
			for (i = 0; i < pLength - 1; i++) {
				// convert plaintext chars to ints 0-26
				// space
				if (plainText[i] == ' ') {
					plainNum = 26;
				}
				
				// letter
				else {
					plainNum = plainText[i] - 65;
				}

				// change key chars to ints 0-26
				// space
				if (keyText[i] == ' ') {
					keyNum = 26;
				}
				
				// letter
				else {
					keyNum = keyText[i] - 65;
				}

				// get encrypted char
				encNum = plainNum + keyNum;
				
				// if >= 27 subtract 27
				if (encNum >= 27) {
					encNum -= 27;
				}

				// replace plaintext char with encrypted char
				// space
				if (encNum == 26) { 
					plainText[i] = ' ';
				}
				
				// letter
				else {
					plainText[i] = 'A' + (char)encNum;
				}
			}

			// send back encrypted file
			length = 0;

			// while there is still text left to send
			while (length <= pLength) { 
				char cipherSend[1024];
		
				// copy portion of string to send	
				strncpy(cipherSend, &plainText[length], 1023);

				// add null terminator
				cipherSend[1024] = '\0'; 

				if (send(client_socket, &cipherSend, 1024, 0) == -1) {
					fprintf(stderr, "ERROR: send encryption text\n");
				}

				// increment
				length += 1023; 
			}

			// free memory
			free(plainText);
			free(keyText);
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