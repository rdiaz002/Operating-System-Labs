/*
Ronuel Diaz
CSC 332 Operating Systems Lab
TASK: Process Management System Calls
9/27/18
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc , char ** argv){
	pid_t pid1=0,pid2=0,wpid=0; //Initialization of variables
	int status =0;

	printf("I am the parents and my PID is : %d\n",getpid()); // print statement for parent
	pid1= fork(); //first child process created.

	if(pid1==0){ // only executed in first child.
		printf("I am child one my PID is: %d\n",getpid());
		sleep(1.5); // keep the child alive to show that both children are active
		printf("I am child one, I am dying\n");
		exit(0);
	}

	pid2 = fork(); // second child from parent. 

 	if(pid2 ==0){ // only executed in child 2. 
		printf("I am child two my PID is: %d\n",getpid());
		sleep(1);// keep the child alive to show that both children are active
		printf("I am child two, I am dying\n");
		exit(0);
	}

	printf("As the Parent, I shall wait for my kids to die\n"); // parent waits
	while((wpid = wait(&status))>0); // wait until end of child execution
		

	printf("I am Dying, I am the parent \n"); 
	return 0;
}




