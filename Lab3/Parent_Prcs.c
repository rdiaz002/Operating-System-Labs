/*
Ronuel Diaz
CSC 332 Operating Systems Lab
TASK 3: Process Management System Calls
PART3.3
10/05/18
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char ** argv){

	int pid=0,pid2=0,status = 0;
	printf("Parent PID: %d\n",getpid()); //Print parent PID

	pid=fork(); // First child fork;

	if(pid==0){ 
	
		printf("\nChild1 has successfully forked with PID: %d\n",getpid()); // Successful fork message	
		execv("Prcs_P1",argv); // Execution of first process(P1)
		exit(0);
	}

	while(wait(&status)>0); // wait until child 1 returns 
	printf("Child1 is done\n");
	
	pid2=fork(); // Second child fork

	if(pid2==0){ 
	
		printf("\nChild2 has successfully forked with PID: %d\n",getpid()); // Successful fork message
		sleep(0.5);	//delay
		execv("Prcs_P2",argv); // Execution of second process(P2)
		exit(0);
	}
	while(wait(&status)>0); // wait until child 2 returns
	printf("Child2 is done\n");
	
	return 0;

}
