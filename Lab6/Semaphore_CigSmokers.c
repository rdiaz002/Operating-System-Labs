/*
   Ronuel Diaz
   Operating Systems
   Task 6 Cigarette Smoker Problem with Semaphores
   11/30/18
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//SEMAPHORES
sem_t* table[3];
sem_t* agent;
char* sem_names[3]={"sem1","sem2","sem3"};

int status;

//PID's
pid_t agentPid;
pid_t childPid[3];

//Creates a smoker with a unique id that indicates what material the smoker has.
void create_smoker(int id){
								//Reference the shared table semaphores
								for( int i =0; i < 3; i++) {
																table[i]=sem_open(sem_names[i],O_CREAT,0644,0);
								}
								//Reference the shares agent semaphore;
								agent =  sem_open("agent",O_CREAT,0644,1);
								while(true) {
																sem_wait(table[id]); //wait until smokers resource is needed to create a cigarette
																if(id==0) {
																								printf("Smoker 0 has the match and will light a cigarette\n");
																}else
																if(id==1) {
																								printf("Smoker 1 has the paper and will light a cigarette\n");
																}else
																if(id==2) {
																								printf("Smoker 2 has the Tabacco and will light a cigarette\n");
																}
																//increment the agent semaphore to tell the agent to continue generating resources.
																sem_post(agent);
								}
}

//Creates an agent
void create_agent(){
								//Reference the shared table semaphores
								for( int i =0; i < 3; i++) {
																table[i]=sem_open(sem_names[i],O_CREAT,0644,0);
								}
								//Reference the shares agent semaphore;
								agent =  sem_open("agent",O_CREAT,0644,1);

								int item;
								for( int i =0; i < 10; i++) {
																sem_wait(agent); //wait until cigarette is created by smokers;
																item = rand() % 3; //if item is 1 then the paper is not generated and instead only the match and the tabacco are generated and so on...
																if(item ==0) {
																								printf("Paper and Tabacco placed on the table\n");
																}else if(item ==1) {
																								printf("Match and Tabacco placed on the table\n");
																}else if(item==2) {
																								printf("Paper and Match placed on the table\n");
																}
																//increment table semaphore that matches with missing resource to allow that smoker to create a cigarette
																sem_post(table[item]);
								}
								//close agent semaphore
								sem_close(agent);
								exit(0);
}

//Main
int main(){
								srand(time(NULL));
								//initializes the table semaphores
								for( int i =0; i < 3; i++) {
																table[i]=sem_open(sem_names[i],O_CREAT,0644,0);
								}
								//initializes the agent semaphore;
								agent =  sem_open("agent",O_CREAT,0644,1);

								agentPid = fork();
								if(agentPid == 0) {
																create_agent();
								}

								for(int i =0; i < 3; i++) {
																childPid[i] = fork();
																if(childPid[i]==0) {
																								create_smoker(i);
																}
								}
								//wait until agent runs out of materials
								while(waitpid(agentPid,&status,0)>0) ;
								//close agent semaphore
								sem_close(agent);
								//kill smokers since no more resources are being generated
								for(int i =0; i < 3; i++) {
																sem_close(table[i]);
																kill(childPid[i],SIGINT);
								}
								return 0;

}
