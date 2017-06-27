/********************************** 
** Author: Jessica Spokoyny
** Course: CS344 - Program #3
** Filename: smallsh.c
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

#define MAX_ARGS 513 
#define MAX_COMMAND_LENGTH 2048 
#define MAX_ERR_MSG_LENGTH 80 

void runShell();
int fgCommand(char *userCommand, char *errMsg);
int bgCommand(char *userCommand);
void parseInput(char *userCommand, char **returnArr);
void initArray(char **argv);
int searchString(char *seachIn, char *searchFor);
void getFileName(char *userCommand, char *returnValue);
static void sigchld_handler (int sig);

int main() {
	// set up signal handler 
	struct sigaction act;
	act.sa_handler = sigchld_handler;
	sigaction(SIGCHLD, &act, NULL);

	// run the shell 
	runShell();

	return 0;
}

// run the shell loop
void runShell() {
	int exitShell = 0;
	int status = 0;
	char userInput[MAX_COMMAND_LENGTH] = "";

	char errMsg[MAX_ERR_MSG_LENGTH] = "";

	while (exitShell == 0) {
		// clear stdin
		tcflush(0, TCIFLUSH);

		// clear user input variable
		strncpy(userInput, "", MAX_COMMAND_LENGTH - 1);

		fflush(stdout);
    	
		// get user input
		printf(": ");
		fgets(userInput, 79, stdin);
		fflush(stdout);
		
		// remove new line char, add end of line char
		size_t ln = strlen(userInput) - 1;
		if (userInput[ln] == '\n') {
			userInput[ln] = '\0';
		}

		// reach end of file
		if (feof(stdin)) {
			exit(0);
		}

		// user enters nothing
		if (strcmp(userInput, "") == 0) {
			continue;
		}

		// user enters comment
		if (userInput[0] == '#') {
			continue;
		}

		// user enters 'exit'
		if (strcmp(userInput, "exit") == 0) {
			exitShell = 1;
			exit(0);
		}

		// user enters 'cd'
		if (strcmp(userInput, "cd") == 0) {
			// find home path
			char* homePath;
			homePath = getenv("HOME");

			// change current directory to home
			chdir(homePath);
			continue;
		}

		// user enters 'cd' and specifies directory
		if ((userInput[0] == 'c') && (userInput[1] == 'd') && (userInput[2] == ' ')) {
			char *args[MAX_ARGS];
			initArray(args);

			// get directory name
			parseInput(userInput, args);

			// change current directory
			chdir(args[1]);
			continue;
		}

		// user enters 'status'
		if (strcmp(userInput, "status") == 0) {
			// regular status message
			if (strncmp(errMsg, "", MAX_ERR_MSG_LENGTH) == 0) {
				printf("exit value %d\n", status);
			}
			
			// error message
			else {
				printf("%s\n", errMsg);
			}

			// clear status
			strncpy(errMsg, "", MAX_ERR_MSG_LENGTH);
			status = 0;
			continue;
		}
		
		// clear status anyway
		else {
			strncpy(errMsg, "", MAX_ERR_MSG_LENGTH);
			status = 0;
		}

		// user enters '&' : background command
		if (searchString(userInput, "&")) {
			bgCommand(userInput);
			continue;
		}
		
		// foreground command
		status = fgCommand(userInput, errMsg);
	}
}

// run foreground command
int fgCommand(char *userCommand, char *errMsg) {	
	int childExitMethod = 0;
	int exitStatus = 0;
	pid_t spawnPid = -5;
	int fd = -1;
	struct sigaction act;
	char fileName[MAX_COMMAND_LENGTH] = "";

	// check for redirects
	int outputRedirect = searchString(userCommand, ">");
	int inputRedirect = searchString(userCommand, "<");

	char *argv[MAX_ARGS];
	initArray(argv);

	// get file descriptor for output redirect
	if (outputRedirect == 1) {
		getFileName(userCommand, fileName);
		fd = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0644);
	}

	// get file descriptor for input redirect 
	if (inputRedirect == 1) {
		getFileName(userCommand, fileName);
		fd = open(fileName, O_RDONLY, 0644);
	}

	// get args from user command
	parseInput(userCommand, argv);

	// start child process 	
	spawnPid = fork();

	switch (spawnPid) {
		// error
		case -1:
			exit(1);
			break;
			
		// run in child process
		case 0:
			// establish std output redirect
			if ((outputRedirect) && (dup2(fd, 1) < 0)) { 
				exit(1);
			}

			// establish std input redirect
			if ((inputRedirect) && (dup2(fd, 0) < 0)) { 
				printf("smallsh: cannot open %s for input\n", fileName);
				exit(1);
			}

			// set up sig handler for child process
			act.sa_handler = SIG_DFL;
			sigaction(SIGINT, &act, NULL);

 	 		close(fd);

			// execute user command
			execvp(argv[0], argv);
			printf("%s: no such file or directory\n", argv[0]);
			exit(1);
			break;
		
		// run in parent process
		default:
			close(fd);
			
			// set up sig handler for parent process
			act.sa_handler = SIG_DFL;
			act.sa_handler = SIG_IGN;
			sigaction(SIGINT, &act, NULL);

			// wait until child process terminates	
			waitpid(spawnPid, &childExitMethod, 0);

			exitStatus = WEXITSTATUS(childExitMethod);

			// save signal error message
			if (WIFSIGNALED(childExitMethod)) {
				int termSignal = WTERMSIG(childExitMethod);
				char terminateMsg[MAX_ERR_MSG_LENGTH]; 
				char signalString[10];
   				snprintf(signalString, sizeof(signalString), "%d", termSignal);

				// display error message and save it
				strncpy(terminateMsg, "terminated by signal ", MAX_ERR_MSG_LENGTH);
				strcat(terminateMsg, signalString);
				printf("%s\n", terminateMsg);
				strncpy(errMsg, terminateMsg, MAX_ERR_MSG_LENGTH);
			}
			break;
	}
	return exitStatus;
}

// run background command
int bgCommand(char *userCommand) {	
	int exitStatus = 0;
	pid_t spawnPid = -5;
	char pidString[10];
	int fd = -1;
	char fileName[MAX_COMMAND_LENGTH] = "";

	// check for redirects
	int outputRedirect = searchString(userCommand, ">");
	int inputRedirect = searchString(userCommand, "<");

	char *argv[MAX_ARGS];
	initArray(argv);

	// get file descriptor for output redirect
	if (outputRedirect == 1) {
		getFileName(userCommand, fileName);
		fd = open(fileName, O_WRONLY|O_TRUNC|O_CREAT, 0644);
	}

	// get file descriptor for input redirect
	if (inputRedirect == 1) {
		getFileName(userCommand, fileName);
		fd = open(fileName, O_RDONLY, 0644);
	}
	
	// no input redirect: redirect stdin to dev/null
	else {
		fd = open("/dev/null", O_RDONLY);
	}

	// parse args from user input
	parseInput(userCommand, argv);

	// start child process	
	spawnPid = fork();

	switch (spawnPid) {
		// error forking
		case -1:
			exit(1);
			break;
			
		// child process will execute	
		case 0:
			// establish std output redirect
			if ((outputRedirect) && (dup2(fd, 1) < 0)) { 
				exit(1);
			}
			
			// establish std input redirect
			else if ((dup2(fd, 0) < 0)) { 
				printf("smallsh: cannot open %s for input\n", fileName);
				exit(1);
			}

   	 		close(fd);

   	 		// execute user command
	  		execvp(argv[0], argv);
	  		printf("%s: no such file or directory\n", argv[0]);
	  		exit(1);
			break;
			
		// parent process will execute	
		default:
			close(fd);

			// display background pid
			snprintf(pidString, sizeof(pidString), "%d", spawnPid);
			printf("background pid is %s\n", pidString);
			break;
	}
	return exitStatus;
}

// break up user input string into an array of individual strings 
void parseInput(char *userCommand, char **returnArr) {
	char *token;
	int tokenNum = 0;

	// find redirect symbols
	int outputRedirect = searchString(userCommand, ">");
	int inputRedirect = searchString(userCommand, "<");

	// break up each word of user input
	token = strtok(userCommand, " ");
	while (token != NULL) {
		// output redirect 
		if ((outputRedirect == 1) && (strcmp(token, ">") == 0)) {
			break;
		}

		// input redirect
		if ((inputRedirect == 1) && (strcmp(token, "<") == 0)) {
			break;
		}

		// background process 
		if (strcmp(token, "&") == 0) {
			break;
		}

		// add command arg
		returnArr[tokenNum] = token;
		token = strtok (NULL, " ");
		tokenNum++;

		// array limit reached
		if (tokenNum == (MAX_ARGS - 1)) {
			returnArr[MAX_ARGS - 1] = 0;
			break;
		}
	}

	// null terminator 
	returnArr[tokenNum] = 0;
}

// initialize array to NULL
void initArray(char **argv) {
	int i; 
	for(i = 0; i < MAX_ARGS; i++) {
		argv[i] = 0;
	}
}

// search string to match contents
int searchString(char *seachIn, char *searchFor) {
	char *found;

	// search
	found = strstr(seachIn, searchFor); 

	// string not found
	if (found == 0) {
		return 0; 
	}
  
	// string found
	else {
		return 1; 
	}
}

// get file name when needed for redirect
void getFileName(char *userCommand, char *returnValue) {
	// no redirects
	if ((searchString(userCommand, "<") == 0) && (searchString(userCommand, ">") == 0)) {
		return;
	}

	char *tempArray[MAX_ARGS];
	char *token;
	int tokenNum = 0;
	int redirectPos = 0;

	// find next arg after redirect symbol and store it
	initArray(tempArray);
	token = strtok(userCommand, " ");
	
	while (token != NULL) {
		// save position of redirect symbol
		if ((strcmp(token, "<") == 0) || (strcmp(token, ">") == 0)) {
			redirectPos = tokenNum;
		}

		// add command arg
		tempArray[tokenNum] = token;
		token = strtok (NULL, " ");
		tokenNum++;

		// array limit reached
		if (tokenNum == (MAX_ARGS - 1)) {
			tempArray[MAX_ARGS - 1] = 0;
			break;
		}
	}

	// get file name and save it in return variable
	if (tempArray[redirectPos + 1] != 0) {
		strncpy(returnValue, tempArray[redirectPos + 1], MAX_COMMAND_LENGTH);
	}
}

// signal handler for child signals
static void sigchld_handler (int sig) {
	int childExitMethod;
	pid_t childPid;

	// close zombie child processes 
	while ((childPid = waitpid(-1, &childExitMethod, WNOHANG)) > 0) {
		// convert child pid to string
		char pidString[10];
		snprintf(pidString, sizeof(pidString), "%d", childPid);

		// child terminate message
		char childExitString[MAX_ERR_MSG_LENGTH]; 
		strncpy(childExitString, "\nbackground pid ", MAX_ERR_MSG_LENGTH);
		strcat(childExitString, pidString);
		strcat(childExitString, " is done: ");
	
		// if child terminated by signal	
		if (WIFSIGNALED(childExitMethod)) {
				int termSignal = WTERMSIG(childExitMethod);
				
				// convert term signal to string
				char signalString[10];
				snprintf(signalString, sizeof(signalString), "%d", termSignal); 

				// error message
				strcat(childExitString, "terminated by signal ");
				strcat(childExitString, signalString);
				strcat(childExitString, "\n");
				write(1, childExitString, sizeof(childExitString));
		}
		
		// exit child normally
		else {
			char statusString[5];
			strcat(childExitString, "exit value ");
			
			// convert status to string
			snprintf(statusString, sizeof(statusString), "%d", WEXITSTATUS(childExitMethod)); 
			
			// display message
			strcat(childExitString, statusString);
			strcat(childExitString, "\n");
			write(1, childExitString, sizeof(childExitString));
		}
		continue;
	}
}



