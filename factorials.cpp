#include <iostream>



int factorials( int n){

if(n==0){
return 1;
}
else if(n>0){
return factorials(n-1) * n;
}
else{
return 0;
}

}

int main(){

int input;
std::cout<<"Input a value to evaluate: ";

std::cin>>input; 

std::cout<< input<< "! = "<<factorials(input)<<std::endl;



}
