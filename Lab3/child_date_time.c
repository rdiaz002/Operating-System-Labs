/*
Ronuel Diaz
CSC 332 Operating Systems Lab
TASK 3: Process Management System Calls
PART1
10/05/18
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char ** argv){

	int pid=0,status = 0;
	printf("Parent PID: %d\n",getpid()); // Parent PID message

	pid=fork(); // child fork

	if(pid==0){ 
	
		printf("\nChild has successfully forked with PID: %d\n",getpid()); // successful fork message	
		execl("/bin/date",argv[0],(char*)NULL); // execute date cmd
		exit(0);
	}

	while(wait(&status)>0); // wait for child to return
	printf("Child is done\n");

	return 0;

}
