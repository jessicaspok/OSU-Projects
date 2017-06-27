/************************************
** Jessica Spokoyny
** CS 372
** Program 1 - chat server
** 10/29/2016
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define HANDLE "Server"
#define BACKLOG 10

// variable to determine when to send message to client SIGINT
int fdHolder;

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(int argc, char *argv[]) {

	fdHolder = -1;

	// store user-defined port
	char *PORT;

	// file descriptor - listen
	int sock_fd;

	// file descriptor - new connection
	int new_fd;
	
	// store address info for sockets
	struct addrinfo hints, *servinfo, *p;

	// store connector's address information
	struct sockaddr_storage their_addr;

	// store size of client socket
	socklen_t sin_size;

	// store info to process SIGINT
	struct sigaction sa;

	// send 1 as address
	int yes = 1;

	// store the client IP address
	char s[INET6_ADDRSTRLEN];

	// track get_in_addr function
	int rv;

	// clear data in hints
	memset(&hints, 0, sizeof hints);

	// either IPv4 or IPv6
	hints.ai_family = AF_UNSPEC;

	// TCP socket
	hints.ai_socktype = SOCK_STREAM;

	// lets IP address fill in - localhost for testing
	hints.ai_flags = AI_PASSIVE;

	// check that command line args were entered correctly
	if(argc != 2) {
		fprintf(stderr, "Usage: server <port number> \n");
		return 1;
	}
	
	// if correct, set port 
	else {
		PORT = argv[1];
	}

	// servinfo points to a linked list of addrinfo structs, NULL used for localhost
	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through resulting linked list
	for(p = servinfo; p != NULL; p = p->ai_next) {

		// attempt to create a socket, if not successful try the next one
		if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		
		if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }


		// assign socket address
		if(bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sock_fd);
			perror("server: bind");
			continue;
		}

		break;
	}

	// free the linked list
	freeaddrinfo(servinfo);
	
	// if bind fails
	if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

	// listen on port for connections
	if(listen(sock_fd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	
	// reap all dead processes
	sa.sa_handler = sigchld_handler; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	
	// if SIGINT signal is raised
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
	
	printf("\nServer waiting for connections on port %s...\n", PORT);
	
	// main accept() loop waiting for new connection
	while(1) {
		sin_size = sizeof their_addr;
		// accept incoming connection
		new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);

		if(new_fd == -1) {
			perror("accept");
			continue;
		}

		pid_t spawnpid;
		spawnpid = fork();

		if(spawnpid == 0) {

			fdHolder = new_fd;

			// set s to appropriate IP addr
			inet_ntop(AF_INET, &(((struct sockaddr_in*)(struct sockadrr *)&their_addr)->sin_addr), s, sizeof s);
			
			printf("\nServer connected to client at %s\n", s);
			printf("Wait for client message and then respond.\n");
			printf("The server and client must alternate in their communication.\n\n");

			// store incoming message from client
			char * message = (char *)malloc(sizeof(char) * 512);
			
			int received;

			// continue receiving messages 
			while((received = recv(new_fd, message, 512, 0))) {

				// if client message is \quit
				if(strncmp(message, "\\quit", 3) == 0) {
					printf("\nClient closing connection...\n");
					printf("Server closing connection...\n");

					// close connection
					if(close(new_fd) == 0) {
						printf("Server waiting for connections on port %s...\n", PORT);
						exit(0);
					} 
					
					// close failure
					else {
						perror("server close failure");
					}

					break;
				}

				// display client's message
				printf("%s\n", message);

				// clear message contents
				message = (char *)malloc(sizeof(char) * 512);

				// store outgoing message to client
				char *inputString = (char *)malloc(sizeof(char *) * 508);
				char *tempString = (char *)malloc(sizeof(char *) * 512);
				
				// display server handle each time
				printf("%s> ", HANDLE);

				// if server enters message
				if(fgets(inputString, 508, stdin)) {

					// if server message is \quit
					if(strncmp(inputString, "\\quit", 5) == 0) {

						// notify client of closing connection
						int close_message = send(new_fd, inputString, 1000, 0);	

						printf("\nServer closing connection...\n");
						printf("Client closing connection...\n");

						// close connection
						if(close(new_fd) == 0) {
							printf("Server waiting on port %s...\n", PORT);
							exit(0);
						} 
						
						// close failure
						else {
							perror("close");	
						}
						
						break;
					}

					// prepend all outgoing messages with server handle
					strcpy(tempString, HANDLE);
					strcat(tempString, "> ");
					strcat(tempString, inputString);

					// send message to client	
					int newmessage = send(new_fd, tempString, 512, 0); 
				}
			}
		} 
		
		else if(spawnpid > 0) {
			continue;
		} 
		
		else {
			printf("fork failed.\n");
		}
	}

	return 0;
}