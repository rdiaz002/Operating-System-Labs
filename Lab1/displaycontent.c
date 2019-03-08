//Ronuel Diaz 
//TASK 1 
//9/21/18
//Operating Systems
//1
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include <unistd.h>


int main(int argc, char ** argv){
	//Usage Message 
	if(argc != 2){

		printf("Usage: displaycontent filename\n");
		return 0;

	}
	//File descriptor and opening file 
	int fd = open(argv[1],O_RDONLY);
	//Failure Opening file 
	if(-1 == fd){
		printf("\nopening %s failed: %s \n",argv[1],strerror(errno));
		return -1;
	}
	//character buffer 
	char buffer[1];
	//loop for reading through file 
	while(read(fd,buffer,sizeof(buffer))!=0){
		printf("%s",buffer); //print character that is read. 
	}
	printf("\n");
	//Close file
	close(fd);
	return 0;
}
