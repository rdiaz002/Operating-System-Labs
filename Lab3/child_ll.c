/*
Ronuel Diaz
CSC 332 Operating Systems Lab
TASK 3: Process Management System Calls
PART2
10/05/18
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc , char** argv){
	
	int pid=0,status = 0;
	printf("Parent PID: %d\n",getpid()); // Parent PID 

	pid=fork(); // child fork

	if(pid==0){ 
		argv[0] = "ls"; // cmd
		argv[1] = "-la"; // options for show all files and hidden
		argv[2] = NULL; // null termination character
		printf("\nChild has successfully forked with PID: %d\n",getpid()); //successful fork message
		execvp(*argv,argv); // execute cmd
		exit(0);
	}

	while(wait(&status)>0); // wait until child returns
	printf("Child is done\n");

	return 0;

}
