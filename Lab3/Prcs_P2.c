/*
Ronuel Diaz
CSC 332 Operating Systems Lab
TASK 3: Process Management System Calls
PART3.2
10/05/18
*/ 
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

int main(int argc,char ** argv){
	
	//Opens source file in read only mode
	int file_d1 = open("source.txt",O_RDONLY);
	
	//Error message for failed opening
	if(-1 == file_d1){
		printf("\n opening source file failed: %s \n",strerror(errno));
		return -1;
	}
	//Message if open was successful
	else{
		printf("\nsource.txt Opened Successful\n");
	}

	int file_d2;
	file_d2 = open("destination1.txt",O_RDWR); // Open files
	int file_d3;
	file_d3 = open("destination2.txt",O_RDWR);

	char buffer[100]; //character buffer
	char buffer2[50]; //character buffer for second file
	//Loop for procedure (3.3) from assignment 
	while(1){
		//save the size returned when reading from source file
		int size = read(file_d1,buffer,sizeof(buffer));
		//End of File condition
		if(size==0){
			break;		
		}
		//Replacement loop (3.1) from assignment
		for(int i =0 ; i < size;i++){
			if(buffer[i]=='1'){
				buffer[i]='A';
			}
		}
		//write altered line into destination file 
		write(file_d2,buffer,size);	
		size = read(file_d1,buffer2,sizeof(buffer2));
		//End of File condition
		if(size==0){
			break;		
		}
		//Replacement loop (3.2) from assignment
		for(int i =0 ; i < size;i++){
			if(buffer2[i]=='2'){
				buffer2[i]='B';
			}
		}
		//write altered line into destination file 
		write(file_d3,buffer2,size);

	}
	//Notify user when complete
	printf("\nCopy Complete\n");
	//Close files
	close(file_d1);
	close(file_d2);
	close(file_d3);


	return 0;
}
