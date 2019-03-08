/*
Ronuel Diaz
CSC 332 Operating Systems Lab
TASK 3: Process Management System Calls
PART3.1
10/05/18
*/ 
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>

int main(int argc, char ** argv){
	
	//File Descriptor 
	int file_desc, file_desc2;
	
	//check for existence then erase if so. 
	if(access("destination1.txt",F_OK)){
		unlink("destination1.txt");
	}//creates files
	file_desc = creat("destination1.txt",S_IRUSR|S_IWUSR|S_IXUSR);
		
	//If file creation failed		
	if(file_desc<0){
		printf("%s file not created [%s]\n","destination1.txt",strerror(errno));
		exit(0);
	}else{
		printf("%s file created\n","destination1.txt");
	}
	
	//check if file exists. erase if so.	
	if(access("destination1.txt",F_OK)){
		unlink("destination1.txt");
	}
	//creates file 	
	file_desc2 = creat("destination2.txt",S_IRUSR|S_IWUSR|S_IXUSR);
		
	//If file creation failed		
	if(file_desc2<0){
		printf("destination2.txt file not created [%s]\n",strerror(errno));
		exit(0);
	}else{
		printf("destination2.txt file created\n");
	}

	//close file
	close(file_desc);	
	close(file_desc2);
	return 0;
}
