#include<stdio.h>
#include<stdlib.h>
int main(){
	char input_str[];
	int input_int[];
	int sum_of_evens = 0;
	scanf("%s",input_str);
	for(int i = 0;i<strlen(input_str);i++){
		input_int[i] = input_str[i]-'0';
		if(input_int[i] % 2 == 0){
			sum_of_evens += input_int[i];
		}
	}
	printf(sum_of_evens);
	return 0;
}
