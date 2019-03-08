//Ronuel Diaz 
//TASK 1 
//9/21/18
//Operating Systems
//0.b
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>

int main(int argc, char ** argv){
	//Usage Message	
	if(argc != 2){
		printf("Usage: create_new_file filename\n");
		return 0;
	}
	
	//File Descriptor 
	int file_desc;
	//Check existence of file	
	file_desc = access(argv[1],F_OK);
	//Message If file already exists 
	if(file_desc==0){
		printf("\n%s already exists\n",argv[1]);
		exit(0);
	}else{
		//creates file 
		file_desc = creat(argv[1],S_IRUSR|S_IWUSR);
		
		//If file creation failed		
		if(file_desc<0){
			printf("%s file not created [%s]\n",argv[1],strerror(errno));
			exit(0);
		}else{
			printf("%s file created\n",argv[1]);
		}
	}
	//close file
	close(file_desc);	
	return 0;
}
