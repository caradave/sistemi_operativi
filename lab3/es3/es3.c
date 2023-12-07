#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void left();
void right();

int main(void){
    printf("p1 %d\n", getpid());
    pid_t pid = fork();

    if (pid == 0){
        right();
        exit(0);
    }
    else{
        left();
    }

    wait((int *) 0);
    printf("p9 %d\n", getpid());

    return 0;
}


void left(){
    printf("p2 %d\n", getpid());

    pid_t pid = fork();

    if(pid!= 0){
        printf("p4 %d\n", getpid());
        
    }else{
        printf("p5 %d\n", getpid());
        exit(0);
    }

    while (wait ((int *) 0) != pid);
    printf("p7 %d\n", getpid());
}


void right(){
    printf("p3 %d\n", getpid());

    pid_t pid = fork();

    if(pid!= 0){
        
    }else{
        printf("p6 %d\n", getpid());
        exit(0);
    }

    while (wait ((int *) 0) != pid);
    printf("p8 %d\n", getpid());
}