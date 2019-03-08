//Ronuel Diaz 
//TASK 1 
//9/21/18
//Operating Systems
//3
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

int main(int argc,char ** argv){
	if(argc != 3){

		printf("Usage: replace source_filename destination_filename\n");
		return 0;

	}
	//Opens source file in read only mode
	int file_d1 = open(argv[1],O_RDONLY);
	
	//Error message for failed opening
	if(-1 == file_d1){
		printf("\n opening source file failed: %s \n",strerror(errno));
		return -1;
	}
	//Message if open was successful
	else{
		printf("\n[%s] Opened Successful\n",argv[1]);
	}

	int file_d2;
	//check to see if destination file exists
	if(access(argv[2],F_OK)){
		//Creation message if it doesnt exist 
		if(errno==ENOENT){
			printf("\n%s: [%s]\n",strerror(errno),argv[2]);
			printf("\nCreating file [%s]\n",argv[2]);
			file_d2 = creat(argv[2], S_IRUSR | S_IWUSR );// destination file descriptor
		}

	}else{
		//Check write permission on destination file
		access(argv[2],W_OK);
		//Error message if write permission not granted for destination file
		if(errno== EACCES){
			 printf("Access Error on [%s]: %s\n",argv[2],strerror(errno));
			 close(file_d1);
			 return -1;	
		}
		//Delete file to overwrite it with source file contents
		unlink(argv[2]);
		file_d2 = creat(argv[2], S_IRUSR | S_IWUSR );//recreate destination file
	}


	char buffer[100]; //character buffer
	//Loop for procedure (3.c) from assignment 
	while(1){
		//save the size returned when reading from source file
		int size = read(file_d1,buffer,sizeof(buffer));
		//End of File condition
		if(size==0){
			break;		
		}
		//Replacement loop (3.a) from assignment
		for(int i =0 ; i < size;i++){
			if(buffer[i]=='1'){
				buffer[i]='A';
			}
		}
		//write altered line into destination file 
		write(file_d2,buffer,size);
		//Write XYZ after altered line into destination file (3.b) from assignment
		write(file_d2,"XYZ",3);

	}
	//Notify user when complete
	printf("\nCopy Complete [%s]>>[%s]\n",argv[1],argv[2]);
	//Close files
	close(file_d1);
	close(file_d2);


	return 0;
}
