/************************************
** Jessica Spokoyny
** CS 372
** Program 2 - ft server
** 11/26/2016
************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<dirent.h>
#include<netdb.h>


// startup function starts up control connection
int startup (int serverPort) {
	int controlSocket;

	// create socket for control connection
	if ((controlSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "ERROR: server socket creation failed\n");
		return -1;
	}

	// store addr info
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);
	server.sin_addr.s_addr = INADDR_ANY;

	// bind socket
	if (bind(controlSocket, (struct sockaddr *) &server, sizeof(server)) == -1) {
		fprintf(stderr, "ERROR: server bind failed\n");
		return -1;
	}

	// listen for connections
	if (listen(controlSocket, 5) == -1) {
		fprintf(stderr, "ERROR: server listen failed\n");
		return -1;
	}

	return controlSocket;
}

int handleRequest(int clientControlSocket) {
	char reqType[2];
	int requestType;
	char data[10];
	int dataPort;
	char clientHostName[255];
	struct hostent * clientHost;
	char filename[255];
	char *ACK = "ACK";
	char rcvACK[4];
	
	// receive request from client
	if ((recv(clientControlSocket, &reqType, sizeof(reqType), 0)) == -1) {
		fprintf(stderr, "ERROR: error receiving request type\n\n", reqType);
		return -1;
	}
	
	// acknowledge
	if ((send(clientControlSocket, ACK, sizeof(ACK), 0)) == -1){
		fprintf(stderr, "ERROR: error acking request type");
	}

	// convert request type to int
	requestType = atoi(reqType);

	// receive data port
	if ((recv(clientControlSocket, &data, sizeof(data), 0)) == -1) {
		fprintf(stderr, "ERROR: error receiving data port\n\n");
		return -1;
	}
	
	// acknowledge
	if ((send(clientControlSocket, ACK, sizeof(ACK), 0)) == -1){
		fprintf(stderr, "ERROR: error acking data port");
	}
	
	// convert data port
	dataPort = atoi(data);

	// receive hostname from client
	if ((recv(clientControlSocket, &clientHostName, sizeof(clientHostName), 0)) == -1) {
		fprintf(stderr, "ERROR: error receiving client host\n\n");
		return -1;
	}
	
	// acknowledge
	if ((send(clientControlSocket, ACK, sizeof(ACK), 0)) == -1){
		fprintf(stderr, "ERROR: error acking data port");
	}

	// get host from hostname
	clientHost = gethostbyname(clientHostName);
	
	// if command is get, find file name
	if (requestType == 1) { 
		if((recv(clientControlSocket, &filename, sizeof(filename), 0)) == -1) {
			fprintf(stderr, "ERROR: error receiving filename from client\n\n");
			return -1;
		}
		
		// acknowledge
		if ((send(clientControlSocket, ACK, sizeof(ACK), 0)) == -1){
			fprintf(stderr, "ERROR: error acking data port");
		}
	}
	
	// create socket for data connection
	int dataSocket;

	// create data socket
	if ((dataSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
		fprintf(stderr, "ERROR: error creating data socket\n\n");
		return -1;
	}

	// store address info
	struct sockaddr_in client;

	// clear contents 
	memset((char *)&client, 0, sizeof(client));

	client.sin_family = AF_INET;
	client.sin_port = htons(dataPort);
	memcpy(&client.sin_addr, clientHost->h_addr, clientHost->h_length);

	// connect
	if (connect(dataSocket, (struct sockaddr*) &client, sizeof(client)) == -1) {
		fprintf(stderr, "ERROR: error connecting data port\n\n");
		return -1;
	}

	// if command is get
	if (requestType == 1) {
			printf("File '%s' requested on port %d.\n", filename, dataPort);

		// send file
		int file;
		if ((file = open(filename, O_RDONLY)) == -1) {
			fprintf(stderr, "ERROR: file not found. Sending error message..\n");
			char error[3];
			strncpy(error, "-1", 3);
			send(dataSocket, &error, 2, 0);
			close(dataSocket);
			return -1;
		}

		// get size of file
		int fileLength = lseek(file, 0, SEEK_END);
		
		// convert length to string
		char lenStr[15];
		memset((char *)&lenStr, '\0', sizeof(lenStr));
		sprintf(lenStr, "%d", fileLength);

		// send file size
		if (send(dataSocket, &lenStr, sizeof(lenStr), 0) == -1) {
			fprintf(stderr, "ERROR: error sending file length\n\n");
			close(dataSocket);
			return -1;
		}

		// receive ACK
		recv(dataSocket, &rcvACK, sizeof(rcvACK), 0);

		// create string to hold file contents
		char *fileText = malloc(sizeof(char) * fileLength);

		// set file pointer to beginning of file
		lseek(file, 0, SEEK_SET);

		// read file text into string
		if(read(file, fileText, fileLength) == -1) {
			fprintf(stderr, "ERROR: error reading file\n\n");
			close(dataSocket);
			return -1;
		}

		// send file while there is still content to be sent
		int len = 0; 
		while (len < fileLength) { 
			char fileSend[1024]; 

			// copy subset of string to send
			strncpy(fileSend, &fileText[len], 1024);

			// send it
			if (send(dataSocket, fileSend, 1024, 0) == -1) {
				fprintf(stderr, "ERROR: error sending file\n\n");
				close(dataSocket);
				return -1;
			}

			// increment
			len += 1024; 
		}
	
		// receive ACK
		recv(dataSocket, &rcvACK, sizeof(rcvACK), 0);
		
		free(fileText);
	}
	
	// if request is list
	else if (requestType == 0) {
		printf("List directory requested on port %d\n", dataPort);

		// send directory
		DIR *dir;
		
		// open directory
		if ((dir = opendir(".")) == NULL) {
			fprintf(stderr, "ERROR: error opening directory\n\n");
			send(dataSocket, "-1", 2, 0);
			close(dataSocket);
			return -1;
		}

		// read from directory and send while there is still content
		struct dirent *d;
		while ((d = readdir(dir)) != NULL) { 
			char name[40];
			memset((char *)&name, '\0', sizeof(name));

			// copy file name to name var
			strncpy(name, d->d_name, strlen(d->d_name));

			// ignore invalid names
			if (strncmp(name, ".", sizeof(name)) == 0 || strncmp(name, "..", sizeof(name)) == 0){
			}
			// send directory name
			else { 
				if (send(dataSocket, name, sizeof(name), 0) == -1) {
					fprintf(stderr, "ERROR: error sending directory name\n\n");
					close(dataSocket);
					return -1;
				}

				// receive ACK
				recv(dataSocket, &rcvACK, sizeof(rcvACK), 0);
			}
		}
		
		printf("Sending directory contents..\n\n");

		// close directory
		closedir(dir);
	}

	close(dataSocket);
	return 0;
}

int main(int argc, char ** argv) {
	int serverPort;
	int controlSocket;
	int clientControlSocket;

	// if port number not specified
	if (argc != 2) {
		fprintf(stderr, "ERROR: usage: ./ftserver <port number>\n\n");
		exit(1);
	}
	
	// check port number is valid
	else if ((atoi(argv[1]) > 65535) || (atoi(argv[1]) < 1024)) {
		fprintf(stderr, "ERROR: port number must be an int between 1024-65530.\n");
		exit(1);
	}
	
	// if valid, set port 
	else {
		serverPort = atoi(argv[1]);
	}

	// start up
	
	// startup error
	if ((controlSocket = startup(serverPort)) == -1) {
		exit(1);
	}

	printf("Server open on %d\n", serverPort);

	// main accept loop
	while (1) {
		clientControlSocket = accept(controlSocket, NULL, NULL);
		
		// error
		if (clientControlSocket == -1) {
			fprintf(stderr, "ERROR: Accept call failed\n");
			exit(1);
		}
		
		int request;
		request = handleRequest(clientControlSocket);

		close(clientControlSocket);
	}

	close(controlSocket);

	return 0;
}