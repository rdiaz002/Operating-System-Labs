//Ronuel Diaz
// Operating Systems
// Task 4
// 10/13/18

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char ** argv){

	if(argc < 2 ){
		printf(" Usage : comm_inter <Command> [Options...]\n");
		exit(0);
	}

	int PID=0,status=0;

	char ** cmds= (char **)malloc(sizeof(char*)*1000); // Initialize Cmd string Array
	char input[1000]; // String Array for input from user

	//Handle Initial commands passed in.
	for(int i= 0; i< argc ; i++){
		cmds[i]=argv[i+1];
	}

	while(strcmp(cmds[0],"quit")!=0){ // Interpreter Loop
		PID = fork(); // New Child process to handle the commands
		if(PID==0){
			execvp(cmds[0],cmds); // Command Execution
			printf("Error executing commands[%s]\n",strerror(errno));
			exit(0);
		}
		PID=0; // Reset PID for next child

		while(wait(&status)>0); // Wait until Child finishes execution
		printf("\n");
		gets(argv[1]); // Get Users next Command

		int i=0;
		char * tokens = strtok(argv[1]," "); //Split command into parts
		while(tokens!=NULL){
			cmds[i++]=tokens;
			tokens = strtok(NULL," ");
		}
		cmds[i] = NULL; // Add in null character for termination

	}
	free(cmds);
	return 0;
}
