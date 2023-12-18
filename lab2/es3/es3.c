#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void left();
void right();

int main(void){
    printf("P1\n");

    pid_t pid = fork();

    // padre
    if(pid != 0){
        
        left();
        
    }else{
       
        right();
        
        exit(0);
    }


    wait((int *) pid);
    printf("P9\n");

    return 0;
}

void left(){
    printf("P2\n");
    pid_t pid = fork();
    if(pid != 0){
        printf("P4\n");
    }else{
        printf("P5\n");
        exit(0);
    }
    wait((int *) pid);
    printf("P7\n");
}


void right(){
    printf("P3\n");
    pid_t pid = fork();

    if(pid != 0){
        
    }else{
        printf("P6\n");
        exit(0);
    }
    wait((int *) pid);
    printf("P8\n");
}