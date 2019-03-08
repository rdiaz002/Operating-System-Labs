//Ronuel Diaz 
//TASK 1 
//9/21/18
//Operating Systems
//0.a
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
extern int errno; // error number

int main(int argc, char* argv[]){

	char * filepath= argv[1]; // variable for file name
	int returnval; 
	
	returnval=access(filepath,F_OK); // check for the existence of the file
	if(returnval==0){
		printf("\n%s exists\n",filepath); // print message if file exists
	}else{
		if(errno==ENOENT){ // error message if it does not 
			printf("%s does not exist \n ",filepath);
		}else if(errno==EACCES){ // error message if no access
			printf("%s is not accessible \n",filepath);
		}else{
			printf("Error %s",strerror(errno)); // error message for all other cases
		}
		return 0;
	}

	returnval=access(filepath,R_OK); // checks for read permission
	if(returnval==0){
		printf("\n%s has read access\n",filepath); // message if read permission granted
	}else{
		printf("\n%s does not have read access\n",filepath); // error message 
	}
	
	
	returnval=access(filepath,W_OK); // checks for write permission
	if(returnval==0){
		printf("\n%s has write access\n",filepath); // messages for write permission granted
	}else{
		printf("\n%s does not have write access\n",filepath); // error message
	}
	return 0;
}
