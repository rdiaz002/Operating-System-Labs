#include <iostream>
#include <stdio.h>
#include <string>

float average_10(int * mem){
	int sum =0;
	for(int i = 0 ; i< 10 ; i++){

		sum+=mem[i];

	}
	return sum/10.0;
}

int smallest_10(int * mem){

	int min= mem[0];
	for (int i = 0; i<10 ; i++){

		if(min > mem[i]){

			min = mem[i];

		}

	}
	return min;
}

int largest_10(int * mem){
	int max = mem[0];
	for( int i = 0; i < 10 ; i++){

		if(max < mem[i]){
			max = mem[i];
		}
	}
	return max;
}
void mode_10( int * mem){
	int max_count= 0;
	int mode;
	for(int i = 0; i<10 ;i++){
		int count =0; 
		for(int j =0; j<10 ;j++){
			if(mem[i]==mem[j]){
				count++;
			}
		}
		if (count > max_count){
			max_count = count;
			mode = mem[i];
		}
	}
	printf("Mode: %d Count: %d\n",mode,max_count);
	

}
int main(int argc, char** argv){

std::cout<<"Please input 10 values"<<std::endl;

int * mem = new int[10];

for(int i = 0;i < 10 ; i++){
std::cout<<i+1<<":";
std::cin >> mem[i];

}

std::cout << "Smallest: "<< smallest_10(mem)<<std::endl;
std::cout << "Largest: "<< largest_10(mem) <<std::endl;
std::cout << "Average: "<< average_10(mem) <<std::endl;
mode_10(mem);


}
