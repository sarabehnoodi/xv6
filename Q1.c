
// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  
    char fixed_str[] = "The sum of even digits in the input number:" ; 
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100]; 
  
        close(fd1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first 
        // pipe. 
        write(fd1[1], input_str, strlen(input_str)+1); 
        close(fd1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        close(fd2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close 
        // reading end. 
        read(fd2[0], concat_str, 100); 
        printf("%s\n", concat_str); 
        close(fd2[0]); 
    } 
  
    // child process 
    else
    { 
        close(fd1[1]);  // Close writing end of first pipe 
  

	// Read a string using first pipe 
        char concat_str[100]; 
        read(fd1[0], concat_str, 100); 
        
	// calculate sum of the even numbers
	int input_int[100];
	int sum_of_evens = 0;
	char sum_char[10];
	int s;
	int i = 0;
	while(concat_str[i] != '\0'){
		input_int[i] = concat_str[i]-'0';
		if(input_int[i] % 2 == 0){
			sum_of_evens += input_int[i];
		}
		i++;
	}
	s = sum_of_evens;
	
	tostring(sum_char,sum_of_evens);			
	//printf("\n%d\n",sum_of_evens);
  
        // Concatenate a fixed string with it 
        int k = strlen(concat_str); 
        //int i = 0; 
        for (int i=0; i<strlen(fixed_str); i++) 
            concat_str[k++] = fixed_str[i]; 
	concat_str[k] = '\0'; 
	int t =strlen(concat_str);
  	for (int i = 0; i<strlen(concat_str);i++)
		concat_str[t++] = sum_char[i];
          // string ends with '\0' 
  	concat_str[t] = '\0'; 
        // Close both reading ends 
        close(fd1[0]); 
        close(fd2[0]); 
  
        // Write concatenated string and close writing end 
        write(fd2[1], concat_str, strlen(concat_str)+1); 
        close(fd2[1]); 
  
        exit(0); 
    } 
}

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
} 

