//Ronuel Diaz
// Operating Systems
// Task 4
// 10/13/18

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>
#define BUFFER_MAX 2048

void check_file(char* file_name);
void count_students(FILE * file,unsigned int * students);
void chapter_divider(int * current_chapter,int * num_of_hws,int * num_of_students,int * chapter_buffer);
void homework_averager(int * num_of_students,int * current_chapter,int * current_hw,int * single_chapter);

int main (int argc, char ** argv){

        if(argc < 4) {//Check proper usage

                printf("Usage : avg <Text file name> <chapters> [homework per chapter ...]\n");
                return 0;

        }else{
                if(atoi(argv[2])!=(argc-3)){ // number of arguments for hw per chapter must match number of chapters
                  printf("Number of chapter does not match with number of arguments\n");
                  return 0;
                }
                if(atoi(argv[2])<2) { // check for chapters less than 2
                        printf("Number of chapters has to be greater than one\n");
                        return 0;
                }
                for(int i =3; i < argc; i++ ) { // checks for hws per chapter less than 1
                        if(atoi(argv[i])<1) {
                                printf("Argument [%d] is less than one\nprogram terminated\n",i-1);
                                return 0;
                        }
                }
        }
        int num_of_hw_total = 0; // count the number of homeworks in total
        int num_of_students = 0; // count the number of students
        FILE * fd;

        check_file(argv[1]); // make sure file exists and readable

        for(int i= 3; i < argc; i++ ) {// home work counter
                num_of_hw_total+=(int)(*argv[i])-'0';
        }
        int num_of_chapters = (int)(*argv[2])-'0';

        fd= fopen(argv[1],"r"); // open text file

        count_students(fd,&num_of_students); // count number of students
        int workload[num_of_hw_total][num_of_students]; //2d array for grades
        char lb[BUFFER_MAX]; // line buffer
        char * str_buffer; // string buffer
        for(int i=0; i < num_of_students; i++) { // loads array with grades from file
                str_buffer=fgets(lb,BUFFER_MAX,fd);
                workload[0][i] = atoi(strtok(str_buffer," "));
                for(int j= 1; j< num_of_hw_total; j++) {
                        workload[j][i] = atoi(strtok(NULL," "));
                }
        }

        int chapter_index=0;
        int PID=0,status=0;
        for( int i =0; i < num_of_chapters; i++) {// splits chapter array into a single chapter and creates a manager
                int * chapter_buffer= &workload[chapter_index];// splitting the chapters into single chapters
                int num_of_hws= atoi(argv[3+i]);
                PID = fork(); // manager creation
                if(PID == 0) {
                        chapter_divider(&i,&num_of_hws,&num_of_students,chapter_buffer); //divides a single chapter into homeworks
                }
                chapter_index+=atoi(argv[3+i]);

        }
        while(wait(&status)>0) ; // wait for managers to report back
        printf("Director Finished, Homeworks have been graded\n");
        fclose(fd);
        return 0;

}

void check_file(char* file_name){ // check file permission and existence

        if(access(file_name,F_OK)==0) {
                printf("File exists\n");
        }else{
                printf("Error with file [%s]\n",strerror(errno));
                exit(0);
        }
        if(access(file_name,R_OK)==0) {
                printf("Read Access Granted\n");
        }else{
                printf("Error with file read permission [%s]\n\n",strerror(errno));
                exit(0);
        }



}

void count_students(FILE * file,unsigned int * students){ // count number of students
        char lb[BUFFER_MAX];
        while(fgets(lb,BUFFER_MAX,file)!=NULL) {
                (*students)++;
        }
        fseek(file,0,SEEK_SET);
}

void chapter_divider(int * current_chapter,int * num_of_hw,int * num_of_students,int * chapter_buffer){ // divide chapter into homeworks
        int child_PID= 0,child_status=0;
        for(int j= 0; j < *num_of_hw; j++) {
                int * single_chapter = &chapter_buffer[j*(*num_of_students)];
                child_PID = fork();
                if(child_PID==0) {
                        homework_averager(num_of_students,current_chapter,&j,single_chapter);
                }
        }
        while(wait(&child_status)>0) ;
        printf("Manager:%d Chapter:%d Finished\n", getpid(),*current_chapter+1);
        exit(0);

}

void homework_averager(int * num_of_students,int * current_chapter,int * current_hw,int * single_chapter){// average homework
        float average =0;

        for(int l =0; l < *num_of_students; l++) {
                average+= single_chapter[l];
        }

        average/=*num_of_students;
        printf("Worker:%d Chapter:%d HW%d Average: %f\n",getpid(), *current_chapter+1,*current_hw+1,average);
        exit(0);

}
