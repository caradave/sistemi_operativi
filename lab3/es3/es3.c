#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int left();
int right();

int main(){
    printf("p1\n");

    pid_t pid = fork();
    
    // padre
    if(pid != 0){
        if(left() == 0)
            printf("p7\n");
        return 0;
    }

    // figlio
    else{
        if(right() == 0)
            printf("p8\n");  
    }
    printf("p9\n");
    return 0;
}

int left(){
    printf("p2\n");

    int pid = fork();
    

    // padre
    if(pid != 0){
        printf("p4\n");
    }
    // figlio
    if(pid == 0){
        printf("p5\n");
    }


    return pid;
}

int right(){
    printf("p3\n");
    int pid = fork();

    // padre
    if(pid != 0){}

    // figlio
    if(pid == 0){
        printf("p6\n");
    }


    return pid;
}