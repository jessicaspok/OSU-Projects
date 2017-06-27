/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #2
** Filename: spokoynj.adventure.c
**********************************/

#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <unistd.h> 
#include <sys/stat.h> 
#include <string.h>

struct room {
	char name[20];
	char type[20];
	int connections[6];
	int numConnections;
};

// initialize array of 7 rooms
struct room rooms[7];  

int current, end;

void swapStringArr(char *arr[], int A, int B);
void swapIntArr(int arr[], int A, int B);
char* randName(char *names[], int n);
void createDir(int pid);
void createRoomFile(struct room r, int roomNum);
int getRoomNum(char* name);
void readRoomNameType(int roomNum, struct room* r);
void readRoomConnections(int roomNum, struct room* r);


int main(void){
	// seed random number generator
	srand(time(NULL));

	// store room names
	char *roomNames[] = {"Singapore", "phuket", "TOKYO", "ShaNGhai", "maniLa", "HoChiMinh", "BALI", "maLaCCa", "JakartA", "OSAKA"};
	
	// store path taken to end room
	int path[50];
	
	// array to store available room numbers
	int availRoomNums[7];
		
	// store name of room user wants to travel to
	char destination[50];
	char *newline;
	
	// temp array used to assign room categories
	struct room temp;

	int i, j, k, l;
	
	// choose 7 rooms at random, assign names, assign type MID_ROOM
	for (i = 0; i < 7; i++){
		strcpy(rooms[i].name, randName(roomNames, 10 - i));
		strcpy(rooms[i].type, "MID_ROOM");
	}
		
	// choose 1 room at random (of 7 MID_ROOMs), assign type START_ROOM
	int random = rand() % 7;
	strcpy(rooms[random].type, "START_ROOM");
	
	// move START_ROOM to end of rooms array
	temp = rooms[random];
	rooms[random] = rooms[6];
	rooms[6] = temp;
	
	// choose 1 room at random (of 6 MID_ROOMs), assign type END_ROOM
	random = rand() % 6;
	strcpy(rooms[random].type, "END_ROOM");
	
	int availRooms;
	int numConnections;
	
	// initialize each room's connections
	// loop through each room
	for (i = 0; i < 7; i++){
		// count of available rooms
		availRooms = 0;
		
		// fill availRoomNums with 0-6 excluding current room i
		for (j = 0; j < 7; j++){
            if (j != i){
                availRoomNums[availRooms] = j;
                availRooms++;
            }
        }
		
		// select random number between 3-6 to be that room's number of connections
		numConnections = (rand() % 4) + 3;
		
		// array to store which rooms MUST be connections before randomly assigning
		int preselectedConnections[6] = {0};
		// count of preselected rooms
		int preselected = 0;
		
		// loop through each previously assigned rooms
		for (j = 0; j < i; j++){
			// loop through connections of previously assigned room
			for (k = 0; k < rooms[j].numConnections; k++){
				// if a previously assigned room has the current room i as a connection, 
				// add that room j to the preselectedConnections array
				// and remove it from the availRoomNums array
				if (rooms[j].connections[k] == i){
					preselectedConnections[preselected] = j;
					preselected++;
						
					for (l = 0; l < availRooms; l++){
						if (availRoomNums[l] == j){
							swapIntArr(availRoomNums, l, availRooms - 1);
							availRooms--;
						}
					}	
				}
			}
		}
		
		// store how many of the current room i's connections have been filled
		int connsFilled = 0;
		
		// assign those connections that were preselected
		for (j = 0; j < preselected; j++){
			rooms[i].connections[j] = preselectedConnections[connsFilled];
			connsFilled++;
		}
		
		// while connsFilled is less than the randomly assigned numConnections
		// generate random numbers and assign connections from availRoomNums array	
		while (numConnections > connsFilled){
			random = rand() % availRooms;
			rooms[i].connections[connsFilled] = availRoomNums[random];
			swapIntArr(availRoomNums, random, availRooms - 1);
			availRooms--;	
			connsFilled++;
		}
		
		// in some cases the number of preselected connections will be greater than the randomly assigned numConnections
		// so when assigning the current room i's numConnections we must use the conns filled
		rooms[i].numConnections = connsFilled;
	}
	
	// variable to access connecting room
	int connRoom;
	// variable to check whether connection is complete
	int check;
	
	// check that all connections are 2-sided
	// loop through each room
	for (i = 6; i > -1; i--){
		// loop through each connection of that room
		for (j = 0; j < rooms[i].numConnections; j++){
			
			check = 0;
			connRoom = rooms[i].connections[j];
			
			// loop through connRoom's connections
			for (k = 0; k < rooms[connRoom].numConnections; k++){
				// check that the current room i is one of them
				if (rooms[connRoom].connections[k] == i){
					check = 1;				
				}
			}
			
			// if the current room is not one of connRoom's connections 
			if (check == 0){
				// add it if there is space
				if (rooms[connRoom].numConnections < 6){
					rooms[connRoom].connections[rooms[connRoom].numConnections] = i;
					rooms[connRoom].numConnections++;
					check = 1;
				}
			} 
		}
	} 
	
	// write rooms to files
	// create the directory
	int pid = getpid();	
	createDir(pid);
	
	// create room files
	for (i = 0; i < 7; i++){
		createRoomFile(rooms[i], i + 1);
	}
	
	// read rooms from files, assign START_ROOM and END_ROOM
	for (i = 0; i < 7; i++){
		readRoomNameType(i + 1, &rooms[i]);
		
		if (strcmp(rooms[i].type, "START_ROOM") == 0){
			current = i; 
		}
		
		if (strcmp(rooms[i].type, "END_ROOM") == 0){
			end = i; 
		}
		
		readRoomConnections(i + 1, &rooms[i]);
	}
	
	// play the game
	// variable to count number of steps taken
	int numSteps = 0;
	
	// variable to store location of next room
	int next;
	
	printf("\n");
	
	while (1){
		// display current room and connecting rooms
		printf("CURRENT LOCATION: %s\n", rooms[current].name);
		printf("POSSIBLE CONNECTIONS: ");
		
		// print connections separating with commas, ending line with period
		for (i = 0; i < rooms[current].numConnections; i++){
			printf("%s", rooms[rooms[current].connections[i]].name);
			if (i == rooms[current].numConnections - 1){
				printf(".\n");
			}
			else{
				printf(", ");
			}
		}
		
		// prompt for next room
		printf("WHERE TO? >");
		fflush(stdout);
		if(fgets(destination, 50, stdin) == NULL){
			printf("\n");
			exit (0);
		}
		
		// replace newline with null char
		newline = strchr(destination, '\n');
		*newline = '\0'; 
		printf("\n");
		
		// validate connection
		// loop through all connections of current room
		for (i = 0; i < 7; i++){
			// if destination doesn't match connection name, next will lead to error
			if(strcmp(rooms[rooms[current].connections[i]].name, destination)){
				next = -1;
			}
			// if destination does match connection name, find index of destination room
			else{
				next = getRoomNum(destination);
				break;
			}
		}
		
		// connection not found
		if(next == -1){
			printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
		}
		
		// connection found
		else{
			current = next;
			
			// record current position in path
			path[numSteps] = current;
			numSteps++;
			
			// display end message, number of steps taken, path
			if(current == end){
				printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
				printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numSteps);
				
				// print path
				for(i = 0; i < numSteps; i++){
					printf("%s\n", rooms[path[i]].name);
					
				}	
				
				exit(0);			
			}
		}	
	}	
}

// swap string elements
void swapStringArr(char *arr[], int A, int B){
	// temp variable to hold char* at A
	char *temp;
	temp = arr[A];
	arr[A] = arr[B];
	arr[B] = temp;
	return;
}

// swap int elements
void swapIntArr(int arr[], int A, int B){
	// temp variable to hold value at A
	int temp;
	temp = arr[A];
	arr[A] = arr[B];
	arr[B] = temp;
	return;
}

// choose a random name from the names array
char* randName(char *names[], int n){
	int random = rand() % n;
	
	// swap the name at position random with the name at position n - 1
	swapStringArr(names, random, n - 1);
	
	return names[n - 1];
}

// create a new directory called spokoynj.rooms.<process id>
void createDir(int pid){
	char dirName[50];
	
	// build full path name 
	sprintf(dirName, "spokoynj.rooms.%d", pid);
	
	// error creating directory
	if (mkdir(dirName, 0755) == -1){ 
		perror("Could not create directory");
		exit(1);
	}
	
	// change to the newly created directory
	chdir(dirName);
	return;
}

// create a new room file
void createRoomFile(struct room room, int roomNum){
	FILE *fpr;
	int i;
	char roomName[2];
	sprintf(roomName, "%d", roomNum);
	fpr = fopen(roomName, "w");
	
	// error opening file
	if (fpr == NULL){
		perror("Could not open file");
		exit(1);
	}
	
	// add room info to file (name, connections, type)
	fprintf(fpr, "ROOM NAME: %s\n", room.name);
	
	for (i = 0; i < room.numConnections; i++){
		fprintf(fpr, "CONNECTION %d: ", i + 1);
		if (rooms[room.connections[i]].name == NULL)
			continue;
		fprintf(fpr, "%s\n", rooms[room.connections[i]].name);
	}
	
	fprintf(fpr, "ROOM TYPE: %s\n", room.type);
	fclose(fpr);
	return;
}

// given the name of a room, return index of that room from rooms array
int getRoomNum(char* name){
	int i;
	
	// loop through all rooms until names match
	for (i = 0; i < 7; i++){
		if (strcmp(name, rooms[i].name) == 0){
			return i;		
		}
	}
	
	// no match found
	return -1;	
}

// read in room's name and type from file named roomNum and stores them in room
void readRoomNameType(int roomNum, struct room* room){
	FILE *fpr;
	int i;
	char roomName[2];
	char buffer[50];
	char* newline;
	
	// open room's file
	sprintf(roomName, "%d", roomNum);
	fpr = fopen(roomName, "room");
	
	// error opening file
	if (fpr == NULL){
		perror("Could not open file");
		exit(1);
	}
	
	while (fgets(buffer, 50, fpr) != NULL){
		// read room name
		if (strncmp(buffer, "ROOM NAME", 9) == 0){
			// skip first 11 chars (ROOM_NAME: )
			strcpy(room->name, buffer + 11); 
			
			// replace newline with null char
			newline = strchr(room->name, '\n');
			*newline = '\0'; 
		}
		
		// read room type
		else if (strncmp(buffer,"ROOM TYPE", 9) == 0){
			// skip first 11 chars (ROOM_TYPE: )
			strcpy(room->type, buffer + 11); 
			
			// replace newline with null char
			newline = strchr(room->type, '\n');
			*newline = '\0';
		}
	}
	
	fclose(fpr);
}

// read in connections from file named roomNum and stores them in room
void readRoomConnections(int roomNum, struct room* room){
	FILE *fpr;
	int i;
	char roomName[2];
	char buffer[50];
	char *newline;
	int conn = 0;
	
	// open room's file
	sprintf(roomName, "%d", roomNum);
	fpr = fopen(roomName, "room");
	
	// error opening file
	if (fpr == NULL){
		perror("Could not open file");
		exit(1);
	}
	
	// read connections
	while (fgets(buffer, 50, fpr) != NULL){
		if (strncmp(buffer, "CONNECTION", 9) == 0){
			char connectionName[50];
			
			// skip first 14 chars (CONNECTION #:)
			strcpy(connectionName, buffer + 14); 
			
			// replace newline with null char
			newline = strchr(connectionName, '\n');
			*newline = '\0';
			
			// fill connection array with corresponding room numbers
			room->connections[conn] = getRoomNum(connectionName);
			conn++;
		}
	}
	
	fclose(fpr);
}